# How C Files Update UI Labels (Temperature and Time)

## Overview

This document explains the mechanism by which C application code updates UI labels such as temperature and timer displays. The system uses the [LVGL](https://lvgl.io/) graphics library, where UI widgets (labels, panels, buttons) are represented as C objects (`lv_obj_t *` pointers) and updated through LVGL API calls.

## Key Files

| File | Role |
|------|------|
| `proj_cm55/ui/screens/ui_TEMP.c` | Creates the UI screen and its LVGL widgets (labels, panels, buttons). Declares global `lv_obj_t *` pointers for each widget. Registers event callbacks for user interactions. |
| `proj_cm55/ui/screens/ui_TEMP.h` | Exports the widget pointers as `extern` so other C files can access them. |
| `proj_cm55/room_scheduler.c` | Contains the application logic (timer countdown, temperature adjustment) and the `room_scheduler_update_display()` function that writes new text into the UI labels. |
| `proj_cm55/room_scheduler.h` | Declares the public API and state variables for the room scheduler. |

## Step-by-Step Flow

### 1. Screen Initialization — Creating the Labels

When the user navigates to the room control screen, `ui_TEMP_screen_init()` in `ui_TEMP.c` runs. It creates every widget using LVGL functions and stores the result in a global pointer:

```c
/* ui_TEMP.c — inside ui_TEMP_screen_init() */

// Create the temperature label on the TEMP screen
ui_Label10 = lv_label_create(ui_TEMP);
lv_label_set_text(ui_Label10, "26°C");          // initial text

// Create the timer label inside a panel
ui_Label24 = lv_label_create(ui_Panel1);
lv_label_set_text(ui_Label24, "4 min 20 sec");  // initial text
```

These global pointers (`ui_Label10`, `ui_Label24`) are declared in `ui_TEMP.h`:

```c
/* ui_TEMP.h */
extern lv_obj_t * ui_Label10;   // temperature label
extern lv_obj_t * ui_Label24;   // timer label
```

Because they are `extern`, any C file that includes `ui_TEMP.h` can read or write to these label objects.

### 2. User Interaction — Event Callbacks

Buttons and images on the screen have event callbacks registered at the end of `ui_TEMP_screen_init()`:

```c
/* ui_TEMP.c */
lv_obj_add_event_cb(ui_Image1, ui_event_Image1, LV_EVENT_ALL, NULL);  // "+" button
lv_obj_add_event_cb(ui_Image2, ui_event_Image2, LV_EVENT_ALL, NULL);  // "-" button
lv_obj_add_event_cb(ui_Panel4, ui_event_Panel4, LV_EVENT_ALL, NULL);  // "Extend" button
```

When the user taps the "+" image, LVGL fires `ui_event_Image1`, which calls into the room scheduler:

```c
/* ui_TEMP.c */
void ui_event_Image1(lv_event_t * e)
{
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        room_scheduler_increase_temperature();   // <-- calls into room_scheduler.c
    }
}
```

### 3. Application Logic — Updating State

`room_scheduler.c` maintains the current state in simple global variables:

```c
/* room_scheduler.c */
int32_t room_timer_seconds = INITIAL_TIMER_SECONDS;   // e.g. 30
int32_t room_temperature   = INITIAL_TEMPERATURE;      // e.g. 26
```

When `room_scheduler_increase_temperature()` is called, it modifies the state and then pushes the new value to the UI:

```c
/* room_scheduler.c */
void room_scheduler_increase_temperature(void)
{
    if (room_temperature < MAX_TEMPERATURE) {
        room_temperature++;                    // update the data
        room_scheduler_update_display();       // push to UI
    }
}
```

### 4. Writing to the UI — `room_scheduler_update_display()`

This is the central function that bridges C data to LVGL labels. It formats a string and calls `lv_label_set_text()` on the global label pointers:

```c
/* room_scheduler.c */
void room_scheduler_update_display(void)
{
    char temp_str[16];
    char timer_str[32];

    /* Update temperature label */
    if (ui_Label10 != NULL) {
        snprintf(temp_str, sizeof(temp_str), "%d°C", room_temperature);
        lv_label_set_text(ui_Label10, temp_str);
    }

    /* Update timer label */
    if (ui_Label24 != NULL) {
        int32_t minutes = room_timer_seconds / 60;
        int32_t seconds = room_timer_seconds % 60;
        snprintf(timer_str, sizeof(timer_str), "%d min %d sec", minutes, seconds);
        lv_label_set_text(ui_Label24, timer_str);
    }
}
```

**Key points:**

- **`lv_label_set_text()`** is the LVGL API that changes the text shown by a label widget. LVGL internally copies the string, so using a stack-allocated buffer is safe.
- **NULL checks** (`if (ui_Label10 != NULL)`) guard against updating a label when the screen has been destroyed (the `ui_TEMP_screen_destroy()` function sets all widget pointers to `NULL`).
- **`snprintf()`** formats the integer state into a human-readable string before passing it to LVGL.

### 5. Automatic Timer Updates — LVGL Timer Callback

The countdown timer updates every second without user interaction. This is driven by an **LVGL timer** created during initialization:

```c
/* room_scheduler.c — room_scheduler_init() */
scheduler_timer = lv_timer_create(room_scheduler_update_timer, 1000, NULL);
```

Every 1000 ms, LVGL calls `room_scheduler_update_timer()`:

```c
/* room_scheduler.c */
void room_scheduler_update_timer(lv_timer_t * timer)
{
    if (timer_active && room_timer_seconds > 0) {
        room_timer_seconds--;              // decrement countdown
        room_scheduler_update_display();   // refresh both labels on screen
    }
}
```

This creates a repeating cycle: **LVGL timer fires → state decremented → `lv_label_set_text()` called → screen refreshes**.

## Data Flow Diagram

```
┌──────────────────────────────────────────────────────────────┐
│                     User Interaction                         │
│  (tap "+" button, tap "Extend", or automatic timer tick)     │
└──────────────────────┬───────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────┐
│              Event Callback (ui_TEMP.c)                      │
│  ui_event_Image1() → room_scheduler_increase_temperature()   │
│  ui_event_Image2() → room_scheduler_decrease_temperature()   │
│  ui_event_Panel4() → room_scheduler_extend()                 │
│                                                              │
│  LVGL Timer  → room_scheduler_update_timer()   (every 1 sec) │
└──────────────────────┬───────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────┐
│            Application Logic (room_scheduler.c)              │
│  1. Update state: room_temperature++ or room_timer_seconds-- │
│  2. Call room_scheduler_update_display()                      │
└──────────────────────┬───────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────┐
│         room_scheduler_update_display()                       │
│  1. snprintf(temp_str, ..., "%d°C", room_temperature)        │
│  2. lv_label_set_text(ui_Label10, temp_str)   ← temperature  │
│  3. snprintf(timer_str, ..., "%d min %d sec", min, sec)      │
│  4. lv_label_set_text(ui_Label24, timer_str)  ← timer        │
└──────────────────────┬───────────────────────────────────────┘
                       │
                       ▼
┌──────────────────────────────────────────────────────────────┐
│                LVGL Rendering Engine                          │
│  Detects that label text changed → redraws the label on the  │
│  next display refresh cycle                                  │
└──────────────────────────────────────────────────────────────┘
```

## Screen Lifecycle and NULL Safety

When the user navigates away from the TEMP screen (e.g., presses "END MEETING"), `ui_TEMP_screen_destroy()` deletes all widgets and sets every pointer to `NULL`:

```c
/* ui_TEMP.c */
void ui_TEMP_screen_destroy(void)
{
    if (ui_TEMP) lv_obj_del(ui_TEMP);
    ui_TEMP    = NULL;
    ui_Label10 = NULL;   // temperature label
    ui_Label24 = NULL;   // timer label
    // ... other widgets ...
}
```

Because the LVGL timer in `room_scheduler.c` may still fire while the screen is destroyed, the NULL checks in `room_scheduler_update_display()` prevent writing to a deleted widget.

## Summary

| Concept | How It Works |
|---------|-------------|
| **Label creation** | `lv_label_create()` in `ui_TEMP_screen_init()` stores the label in a global `lv_obj_t *` pointer |
| **Label text update** | `lv_label_set_text(ui_LabelXX, "new text")` in `room_scheduler_update_display()` |
| **Temperature update** | User taps +/- → event callback → `room_scheduler_increase/decrease_temperature()` → `room_scheduler_update_display()` |
| **Timer update** | LVGL timer fires every 1 s → `room_scheduler_update_timer()` decrements counter → `room_scheduler_update_display()` |
| **NULL safety** | `ui_TEMP_screen_destroy()` sets pointers to `NULL`; `room_scheduler_update_display()` checks for `NULL` before writing |
