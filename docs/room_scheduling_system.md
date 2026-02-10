# Room Scheduling System

## Overview

This application has been modified from a music player template to a room scheduling system for conference room management. The system allows users to reserve rooms with a timer-based scheduling mechanism and control room environment settings.

## Features

### 1. Lock Screen
- Initial screen displayed on startup
- Shows team member names
- Touch to wake and navigate to floor selection

### 2. Floor Selection
- Displays available floors (Floor 1, 2, 3, 4)
- Click any floor button to proceed to room selection

### 3. Room Selection
- Shows available rooms on the selected floor (Room 113, Room 203, Room 301, Room 400)
- Rooms are color-coded:
  - Green: Available
  - Yellow/Orange: Reserved
  - Red: Occupied
- Click an available room to start a meeting

### 4. Room Control Screen
When a room is selected, the following features are available:

#### Timer Management
- **Initial Timer**: 30 seconds countdown when room is first selected
- **Timer Display**: Shows remaining time in "X min Y sec" format
- **Extend Button**: Adds 30 seconds to the current timer
- **Timer Expiration**: Timer stops at zero (user must click End Meeting to navigate back)
- **End Meeting Button**: Manually end the meeting and return to room selection

#### Temperature Control
- **Current Temperature**: Displays current room temperature (starts at 26°C)
- **Increase (+) Button**: Raises temperature by 1°C (maximum 30°C)
- **Decrease (-) Button**: Lowers temperature by 1°C (minimum 16°C)
- **Real-time Display**: Temperature updates immediately on screen

#### Environmental Monitoring (Dummy Values)
- **CO2 Level**: 450 ppm
- **SpO2 (Oxygen Saturation)**: 98% (Excellent)
- **Humidity**: 45%

#### Additional Controls
- **Open/Close Blinds**: Toggle button for window blinds

## Implementation Details

### Architecture
```
proj_cm55/
├── room_scheduler.h        # Header for scheduling logic
├── room_scheduler.c        # Core scheduling implementation
└── ui/
    └── screens/
        ├── ui_Lockscreen.c   # Lock screen implementation
        ├── ui_FloorScreen.c  # Floor selection screen
        ├── ui_Room_1.c       # Room selection screen
        └── ui_TEMP.c         # Room control screen
```

### Timer Logic
- Uses LVGL timer mechanism for countdown
- Timer updates every second (1000ms interval)
- Timer state persists when navigating away from screen
- Only resets when starting a new meeting

### State Management
The room scheduler maintains the following state:
- `room_timer_seconds`: Current countdown time
- `room_temperature`: Current temperature setting
- `timer_active`: Whether timer is currently running
- `new_meeting_flag`: Indicates when a new meeting starts

### Thread Safety
- All UI updates occur in LVGL task context
- Static variables use documented single-threaded access patterns
- String buffers are stack-allocated to avoid race conditions

## Usage Instructions

1. **Starting a Meeting**:
   - Touch the lock screen
   - Select a floor
   - Click an available room (green)
   - Timer automatically starts at 30 seconds

2. **During Meeting**:
   - Adjust temperature using +/- buttons
   - Extend meeting time using "Extend" button
   - Monitor environmental conditions
   - Toggle blinds as needed

3. **Ending a Meeting**:
   - Click "END MEETING" button to manually end and return to room selection
   - When timer reaches zero, timer stops but user must click END MEETING to exit
   - System returns to room selection screen after clicking END MEETING

## Configuration

Key constants in `room_scheduler.h`:
```c
#define INITIAL_TIMER_SECONDS       30    // Initial timer duration
#define EXTEND_TIMER_SECONDS        30    // Time added by extend button
#define INITIAL_TEMPERATURE         26    // Starting temperature
#define MIN_TEMPERATURE             16    // Minimum allowed temperature
#define MAX_TEMPERATURE             30    // Maximum allowed temperature
```

## Future Enhancements

Possible improvements:
1. Connect to real sensors for CO2, SpO2, and humidity readings
2. Integrate with HVAC system for actual temperature control
3. Add database backend for room reservation management
4. Implement user authentication
5. Add meeting scheduling with start/end times
6. Include room occupancy detection
7. Add calendar integration
8. Implement notification system for meeting reminders
