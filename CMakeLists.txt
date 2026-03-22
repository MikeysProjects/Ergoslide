target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_sources_ifdef(CONFIG_ZMK_HID_INDICATORS app PRIVATE src/caps_lock_led.c)
