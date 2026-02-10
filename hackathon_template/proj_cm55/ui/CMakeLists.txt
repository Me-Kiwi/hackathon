SET(SOURCES screens/ui_Info.c
    screens/ui_Graphics.c
    screens/ui_Voice.c
    screens/ui_Sensors.c
    screens/ui_Audio.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_icn_home_png.c
    images/ui_img_icn_back1_png.c
    images/ui_img_icn_back_png.c
    images/ui_img_mic_png.c
    images/ui_img_soundd_png.c
    images/ui_img_music_png.c
    images/ui_img_play_png.c
    images/ui_img_ppause_png.c
    fonts/ui_font_SS3.c
    fonts/ui_font_SS48.c
    fonts/ui_font_SS52.c)

add_library(ui ${SOURCES})
