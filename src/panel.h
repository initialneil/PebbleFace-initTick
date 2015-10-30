#pragma once
#include <pebble.h>
#include "common.h"

Layer * init_panel_layer(Window *window);
void pass_config_to_panel(struct CONFIG_TYPE *app_config);

static void update_panel_proc(Layer *layer, GContext *ctx);

