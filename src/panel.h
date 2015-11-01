#pragma once
#include <pebble.h>
#include "common.h"

Layer * init_panel_layer(Window *window);
void pass_config_to_panel(struct CONFIG_TYPE *app_config);
void set_show_hour_digits(bool show_hour_digits);

static void update_panel_proc(Layer *layer, GContext *ctx);
void release_panel_layer();
