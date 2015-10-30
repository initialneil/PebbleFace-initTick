#pragma once
#include <pebble.h>
#include "common.h"

void init_date_layer(Window *window);
void pass_config_to_text(struct CONFIG_TYPE *app_config);
TextLayer * get_month_layer();
TextLayer * get_date_layer();
TextLayer * get_weekday_layer();
void refresh_text_config();

void set_date_layer_cur_time(struct tm *tick_time);

void release_date_layer();

