#include "panel.h"

static Layer *s_panel_layer;
static GPoint s_center;
const int HOUR_BAR_MARGIN = 6;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;
static struct CONFIG_TYPE *config;
static GFont s_text_font;

Layer * init_panel_layer(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init panel layer");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_center = grect_center_point(&window_bounds);
  APP_LOG(APP_LOG_LEVEL_INFO, "window center: %d, %d", s_center.x, s_center.y);
  
  s_win_w = window_bounds.size.w;
  s_win_h = window_bounds.size.h;
  APP_LOG(APP_LOG_LEVEL_INFO, "window size: %d, %d", s_win_w, s_win_h);
  
  s_radius = s_win_w < s_win_h ? s_win_w : s_win_h;
  s_radius /= 2;
  s_radius -= 2;

  s_text_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIGITAL_16));
  
  s_panel_layer = layer_create(window_bounds);
  layer_set_update_proc(s_panel_layer, update_panel_proc);
  
  return s_panel_layer;
}

void pass_config_to_panel(struct CONFIG_TYPE *app_config) {
  config = app_config;
}

void set_show_hour_digits(bool show_hour_digits) {
  config->SHOW_HOUR_DIGITS = show_hour_digits;
  persist_write_bool(SHOW_HOUR_DIGITS, config->SHOW_HOUR_DIGITS);
}

static void update_panel_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update panel layer");
  
  // Color background
  GRect bounds = layer_get_bounds(layer);

  graphics_context_set_fill_color(ctx, config->PANEL_OUT_COLOR);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, config->PANEL_IN_COLOR);
  graphics_fill_circle(ctx, s_center, s_radius + 1);
  
  // Plot Dots
  graphics_context_set_antialiased(ctx, true);
  
  for (int i = 0; i < 60; i++) {
    // hour bar
    if (i % 5 == 0 && i / 5 != -1) {
      GPoint dot = (GPoint) {
        .x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius - HOUR_BAR_MARGIN) / TRIG_MAX_RATIO) + s_center.x,
        .y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius - HOUR_BAR_MARGIN) / TRIG_MAX_RATIO) + s_center.y,
      };
      
      graphics_context_set_stroke_color(ctx, config->HOUR_DOTS_COLOR);
      graphics_context_set_text_color(ctx, config->HOUR_DOTS_COLOR);
      if (i % 15 == 0) {
        // emphasis
        graphics_context_set_stroke_color(ctx, config->HOUR_ENPHASIS_COLOR);
        graphics_context_set_text_color(ctx, config->HOUR_ENPHASIS_COLOR);
      }
      
      if (!config->SHOW_HOUR_DIGITS) {
        // show hour bar
        GPoint dot_start = dot;
        dot_start.x += (s_center.x - dot.x) * 0.15;
        dot_start.y += (s_center.y - dot.y) * 0.15;        
          
        graphics_context_set_stroke_width(ctx, 2);
        graphics_draw_line(ctx, dot_start, dot);
      } else {
        // show hour digits
        GPoint dot_start = dot;
        dot_start.x += (s_center.x - dot.x) * 0.08;
        dot_start.y += (s_center.y - dot.y) * 0.08;
        dot_start.x -= 15;
        dot_start.y -= 10;
        GSize sz = (GSize) {
          .w = 30,
          .h = 20,
        };
        GRect rect = (GRect) {
          .origin = dot_start,
          .size = sz,
        };
        char str[3];
        snprintf(str, 3, "%d", i / 5 == 0 ? 12 : i / 5);
        graphics_draw_text(ctx, str, s_text_font, rect, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
      }
    }
    
    // minute dots
    if (i % 5 == 0) {
      graphics_context_set_stroke_color(ctx, config->HOUR_DOTS_COLOR);
      
      // emphasis
      if (i % 15 == 0)
        graphics_context_set_stroke_color(ctx, config->HOUR_ENPHASIS_COLOR);
    } else {
      graphics_context_set_stroke_color(ctx, config->MINUTE_DOTS_COLOR);
    }
    
    GPoint dot = (GPoint) {
      .x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.x,
      .y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.y,
    };

    GPoint dot_;
    for (int x = -1; x <= 1; x++) {
      for (int y = -1; y <= 1; y++) {
        dot_ = dot;
        dot_.x += x;
        dot_.y += y;
        graphics_draw_pixel(ctx, dot_);
      }
    }
  }
}

// Release
void release_panel_layer() {
  fonts_unload_custom_font(s_text_font);
}












