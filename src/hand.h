#pragma once
#include <pebble.h>
#include "common.h"

Layer * init_hand_layer(Window *window);
void set_hand_cur_time(struct tm *tick_time, bool SHOW_SECOND);

