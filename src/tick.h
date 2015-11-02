#pragma once
#include <pebble.h>
#include "common.h"
#include "panel.h"
#include "hand.h"
#include "weather.h"
#include "text.h"

void pass_config_to_tick(struct CONFIG_TYPE *app_config);

void update_hand_show_second(struct CONFIG_TYPE config_msg);
void update_color_scheme(const char color_scheme[], bool b_write);

void hand_tick_handler(struct tm *tick_time, TimeUnits changed);


