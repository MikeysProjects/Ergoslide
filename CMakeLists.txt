zephyr_library()
zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)
zephyr_library_sources_ifdef(CONFIG_ZMK_HID_INDICATORS src/caps_lock_led.c)
