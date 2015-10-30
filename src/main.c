#include <pebble.h>
#include "common.h"
#include "tick.h"
#include "panel.h"
#include "hand.h"
#include "text.h"
#include "weather.h"
#include "app_msg.h"

static Window *s_main_window;
static Layer *s_panel_layer, *s_hand_layer, *s_weather_layer;
static TextLayer *s_month_layer, *s_date_layer, *s_weekday_layer;
static TextLayer *s_temperature_layer, *s_city_layer;

static struct CONFIG_TYPE config;
static char s_conditions_buffer[32], s_temperature_buffer[32], s_city_buffer[32];
static bool s_show_weather = true, s_show_location = true;
static char s_default_location[32], s_location_opt[32];
static char color_scheme[1024];

/************************************ UI **************************************/
static void window_load(Window *window) {
  // init layers
  s_panel_layer = init_panel_layer(window);
  s_hand_layer = init_hand_layer(window);
  
  init_date_layer(window);
  s_month_layer = get_month_layer();
  s_date_layer = get_date_layer();
  s_weekday_layer = get_weekday_layer();
  
  init_weather_layer(window);
  s_weather_layer = get_weather_layer();
  s_temperature_layer = get_temperature_layer();
  s_city_layer = get_city_layer();
  
  // add to window layer
  Layer *window_layer = window_get_root_layer(window);
  layer_add_child(window_layer, s_panel_layer);

  layer_add_child(window_layer, text_layer_get_layer(s_month_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_weekday_layer));

  layer_add_child(window_layer, s_weather_layer);
  layer_add_child(window_layer, text_layer_get_layer(s_temperature_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_city_layer));
  
  layer_add_child(window_layer, s_hand_layer);
  
  // set initial config
  config_weather_layer(s_show_weather, s_show_location);
  config_location_setting(s_default_location, s_location_opt);
  config_weather_buffer(s_conditions_buffer, s_temperature_buffer, s_city_buffer);
  window_set_background_color(window, config.PANEL_OUT_COLOR);
}

static void window_unload(Window *window) {
  layer_destroy(s_panel_layer);
  layer_destroy(s_hand_layer);
  
  text_layer_destroy(s_month_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_weekday_layer);
  release_date_layer();
  
  layer_destroy(s_weather_layer);
  text_layer_destroy(s_temperature_layer);
  text_layer_destroy(s_city_layer);
  release_weather_layer();
}

static void init_config() {
  // load config from "config.h"
  load_default_config(&config);
  pass_config_to_tick(&config);
  pass_config_to_panel(&config);
  pass_config_to_hand(&config);
  pass_config_to_text(&config);
  pass_config_to_weather(&config);
  
  // display
  if (persist_exists(SHOW_SECOND))
    config.SHOW_SECOND = persist_read_bool(SHOW_SECOND);
  
  if (persist_exists(SHOW_WEATHER))
    s_show_weather = persist_read_bool(SHOW_WEATHER);
  
  if (persist_exists(SHOW_LOCATION))
    s_show_location = persist_read_bool(SHOW_LOCATION);
  
  // weather & location diaplay
  memset(s_conditions_buffer, 0, sizeof(s_conditions_buffer));
  if (persist_exists(WEATHER_ICON_KEY))
    persist_read_string(WEATHER_ICON_KEY, s_conditions_buffer, sizeof(s_conditions_buffer));
  
  memset(s_temperature_buffer, 0, sizeof(s_temperature_buffer));
  if (persist_exists(WEATHER_TEMPERATURE_KEY))
    persist_read_string(WEATHER_TEMPERATURE_KEY, s_temperature_buffer, sizeof(s_temperature_buffer));
  
  memset(s_city_buffer, 0, sizeof(s_city_buffer));
  if (persist_exists(WEATHER_CITY_KEY))
    persist_read_string(WEATHER_CITY_KEY, s_city_buffer, sizeof(s_city_buffer));
  
  // location setting
  memset(s_default_location, 0, sizeof(s_default_location));
  if (persist_exists(DEFAULT_LOCATION))
    persist_read_string(DEFAULT_LOCATION, s_default_location, sizeof(s_default_location));
  
  memset(s_location_opt, 0, sizeof(s_location_opt));
  if (persist_exists(LOCATION_OPT))
    persist_read_string(LOCATION_OPT, s_location_opt, sizeof(s_location_opt));
  
  // color scheme
  memset(color_scheme, 0, sizeof(color_scheme));
  if (persist_exists(COLOR_SCHEME)) {
    persist_read_string(COLOR_SCHEME, color_scheme, sizeof(color_scheme));
    APP_LOG(APP_LOG_LEVEL_DEBUG, "color scheme: %s", color_scheme);
    update_color_scheme(color_scheme);
  }
}

/*********************************** App **************************************/
static void init() {
  srand(time(NULL));
  
  // init configuration
  init_config();

  // init main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
  
  // init weather
  refresh_weather_display();
  
  // subscribe on time tick
  update_hand_show_second(config);
  
  // register app message callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // open AppMessage
  int inbox_size = 1024;
  APP_LOG(APP_LOG_LEVEL_INFO, "inbox: %d, outbox: %d", 
          (int)inbox_size, APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
  app_message_open(inbox_size, APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
