#include "app_msg.h"
#include "common.h"
#include "tick.h"
#include "hand.h"
#include "weather.h"

// Store incoming information
static struct CONFIG_TYPE config_msg;
static char temperature_buffer[8];
static char conditions_buffer[32];
static char city_buffer[32], default_location_buffer[32], location_opt_buffer[32];
static char color_scheme[1024];

static bool s_show_weather = true, s_show_location = true;

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Init current config
  get_weather_config(&s_show_weather, &s_show_location);
  
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "app msg key = %d", (int)t->key);
    
    // Which key was received?
    switch(t->key) {
      // PebbleKit JS Ready
      case PEBBLEKIT_JS_READY:
        set_pebblekit_js_ready((bool)t->value->int8);
        update_weather_with_app_msg();
        break;
      
      // Display Second
      case SHOW_SECOND:
        config_msg.SHOW_SECOND = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "show second = %d", config_msg.SHOW_SECOND);
        update_hand_show_second(config_msg);
        break;
      
      // Display Weather & Location
      case SHOW_WEATHER:
        s_show_weather = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "show weather = %d", s_show_weather);
        config_weather_layer(s_show_weather, s_show_location);
        break;
      
      case SHOW_LOCATION:
        s_show_location = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "show location = %d", s_show_location);
        config_weather_layer(s_show_weather, s_show_location);
        break;
      
      // Weather Info
      case WEATHER_ICON_KEY:
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "weather condition = %s", conditions_buffer);
        set_conditions_buffer(conditions_buffer);
        break;
        
      case WEATHER_TEMPERATURE_KEY:
        set_temperature_buffer((int)t->value->int32);
        break;
        
      case WEATHER_CITY_KEY:
        snprintf(city_buffer, sizeof(city_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "city = %s", city_buffer);
        set_city_buffer(city_buffer);
        break;
        
      // location setting      
      case DEFAULT_LOCATION:
        snprintf(default_location_buffer, sizeof(default_location_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "default location = %s", default_location_buffer);
        set_default_location(default_location_buffer);
        break;
      
      case LOCATION_OPT:
        snprintf(location_opt_buffer, sizeof(city_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "location opt = %s", location_opt_buffer);
        set_location_opt(location_opt_buffer);
        break;
      
      // color scheme
      case COLOR_SCHEME:
        snprintf(color_scheme, sizeof(color_scheme), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "color_scheme = %s", color_scheme);
        update_color_scheme(color_scheme);
        break;
      
      // temperature format
      case WEATHER_CELSIUS:
        config_msg.WEATHER_CELSIUS = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "weather format = %s", config_msg.WEATHER_CELSIUS ? "Celsius" : "Fahrenheit");
        set_temperature_format(config_msg.WEATHER_CELSIUS);
        set_temperature_buffer((int)t->value->int32);
        break;
      
      // show hour digits or hour bars
      case SHOW_HOUR_DIGITS:
        config_msg.SHOW_HOUR_DIGITS = t->value->int8;
        set_show_hour_digits(config_msg.SHOW_HOUR_DIGITS);
        APP_LOG(APP_LOG_LEVEL_INFO, "show hour digits = %d", config_msg.SHOW_HOUR_DIGITS);
        break;
      
      case APP_MSG_OUT_OF_MEMORY:
        APP_LOG(APP_LOG_LEVEL_ERROR, "Out of memory!");
        break;
        
      default:
        APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
        break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
  // Update weather layer
  refresh_text_config();
  refresh_weather_display();
}




