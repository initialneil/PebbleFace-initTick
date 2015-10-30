#pragma once
#include <pebble.h>
#include "common.h"

Layer * init_hand_layer(Window *window);
void pass_config_to_hand(struct CONFIG_TYPE *app_config);

void set_hand_cur_time(struct tm *tick_time, bool SHOW_SECOND);

