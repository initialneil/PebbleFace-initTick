#pragma once
#include <pebble.h>
#include "panel.h"
#include "hand.h"
#include "weather.h"
#include "text.h"

void update_hand_show_second(struct CONFIG_TYPE config_msg);
void hand_tick_handler(struct tm *tick_time, TimeUnits changed);


