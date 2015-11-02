#include "tick.h"

static struct CONFIG_TYPE *config;
  
void pass_config_to_tick(struct CONFIG_TYPE *app_config) {
  config = app_config;
}

void update_hand_show_second(struct CONFIG_TYPE config_msg) {
  config->SHOW_SECOND = config_msg.SHOW_SECOND;
  persist_write_bool(SHOW_SECOND, config->SHOW_SECOND);
  
  // handle tick now
  time_t t = time(NULL);
  struct tm *time_now = localtime(&t);
  hand_tick_handler(time_now, 0);
  
  tick_timer_service_unsubscribe();
  if (config->SHOW_SECOND) {
    tick_timer_service_subscribe(SECOND_UNIT, hand_tick_handler);
  } else {
    tick_timer_service_subscribe(MINUTE_UNIT, hand_tick_handler);
  }
}

void update_color_scheme(const char color_scheme[], bool b_write) {  
  // persist write 's max length is 256
  int count = 0;
  bool pending_write = false;
  static char sub_scheme[256];
  const char *scheme = color_scheme;
  
  // update color
  char delimiter = ',';
  static char str_key[32], str_val[32];
  
  const char *p0, *p1;
  p0 = color_scheme;
  p1 = strchr(color_scheme, delimiter);
  while (p1 != NULL) {
    // find color key
    strncpy(str_key, p0, p1 - p0);
    str_key[p1 - p0] = '\0';
    p0 = p1 + 1;
    p1 = strchr(p0, delimiter);
    
    if (p1 == NULL)
      break;
    if (!pending_write) {
      pending_write = true;
    }
    
    // find color value
    strncpy(str_val, p0, p1 - p0);
    str_val[p1 - p0] = '\0';
    p0 = p1 + 1;
    p1 = strchr(p0, delimiter);
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s : %s", str_key, str_val);    

    // set to config
    set_config_color_value(config, str_key, HexStringToGColor(str_val));
    
    // cut string to write if length close to 256
    if (b_write && p1 != NULL && p1 - scheme > 200) {
      count++;
      strncpy(sub_scheme, scheme, p1 - scheme + 1);
      sub_scheme[p1 - scheme + 1] = '\0';
      APP_LOG(APP_LOG_LEVEL_DEBUG, "writing(%d): %s", p1 - scheme + 1, sub_scheme);
      persist_write_string(COLOR_SCHEME_TYPE_COUNT + count, sub_scheme);
      scheme = p0;
      pending_write = false;
    }
  }
  
  if (b_write) {
    if (pending_write) {
      count++;
      strncpy(sub_scheme, scheme, p0 - scheme);
      sub_scheme[p0 - scheme] = '\0';
      APP_LOG(APP_LOG_LEVEL_DEBUG, "writing(%d): %s", p0 - scheme, sub_scheme);
      persist_write_string(COLOR_SCHEME_TYPE_COUNT + count, sub_scheme);
    }
    persist_write_int(COLOR_SCHEME_TYPE_COUNT, count);
  }
}

void hand_tick_handler(struct tm *tick_time, TimeUnits changed) {
  // update hand
  set_hand_cur_time(tick_time, config->SHOW_SECOND);
  
  // update date
  set_date_layer_cur_time(tick_time);
  
  // update weather
  if (tick_time->tm_min % 30 == 0)
    update_weather_with_app_msg();
}


