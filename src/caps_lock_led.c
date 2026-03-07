/*
 * Copyright (c) 2026
 *
 * SPDX-License-Identifier: MIT
 */

#error "caps_lock_led.c is compiling"

#include <errno.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include <zmk/events/hid_indicators_changed.h>
#include <zmk/event_manager.h>
#include <zmk/hid_indicators.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define CAPS_LOCK_LED_MASK BIT(1)

#if DT_NODE_EXISTS(DT_ALIAS(capslockled))

#define CAPS_LOCK_LED_NODE DT_ALIAS(capslockled)
#define CAPS_LOCK_LED_PARENT DT_PARENT(CAPS_LOCK_LED_NODE)
#define CAPS_LOCK_LED_INDEX DT_NODE_CHILD_IDX(CAPS_LOCK_LED_NODE)

static const struct device *const caps_lock_leds = DEVICE_DT_GET(CAPS_LOCK_LED_PARENT);

static int caps_lock_led_update(zmk_hid_indicators_t indicators) {
    if (!device_is_ready(caps_lock_leds)) {
        LOG_ERR("Caps Lock LED device \"%s\" is not ready", caps_lock_leds->name);
        return -ENODEV;
    }

    if ((indicators & CAPS_LOCK_LED_MASK) != 0U) {
        return led_on(caps_lock_leds, CAPS_LOCK_LED_INDEX);
    }

    return led_off(caps_lock_leds, CAPS_LOCK_LED_INDEX);
}

static int caps_lock_led_listener(const zmk_event_t *eh) {
    const struct zmk_hid_indicators_changed *event = as_zmk_hid_indicators_changed(eh);

    if (event == NULL) {
        return -ENOTSUP;
    }

    return caps_lock_led_update(event->indicators);
}

ZMK_LISTENER(caps_lock_led_listener, caps_lock_led_listener);
ZMK_SUBSCRIPTION(caps_lock_led_listener, zmk_hid_indicators_changed);

static int caps_lock_led_init(void) {
    if (!device_is_ready(caps_lock_leds)) {
        LOG_ERR("Caps Lock LED device \"%s\" is not ready", caps_lock_leds->name);
        return -ENODEV;
    }

    /* Temporary hardware validation: force the LED on at boot. */
    return led_on(caps_lock_leds, CAPS_LOCK_LED_INDEX);
}

SYS_INIT(caps_lock_led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

#else

static int caps_lock_led_init(void) { return 0; }

SYS_INIT(caps_lock_led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

#endif
