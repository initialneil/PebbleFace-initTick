#include "tick.h"

void update_hand_show_second(struct CONFIG_TYPE config_msg) {
  config.SHOW_SECOND = config_msg.SHOW_SECOND;
  persist_write_bool(SHOW_SECOND, config.SHOW_SECOND);
  
  // handle tick now
  time_t t = time(NULL);
  struct tm *time_now = localtime(&t);
  hand_tick_handler(time_now, 0);
  
  tick_timer_service_unsubscribe();
  if (config.SHOW_SECOND) {
    tick_timer_service_subscribe(SECOND_UNIT, hand_tick_handler);
  } else {
    tick_timer_service_subscribe(MINUTE_UNIT, hand_tick_handler);
  }
}

void hand_tick_handler(struct tm *tick_time, TimeUnits changed) {
  // update hand
  set_hand_cur_time(tick_time, config.SHOW_SECOND);
  
  // update date
  set_date_layer_cur_time(tick_time);
  
  // update weather
  if (tick_time->tm_min % 30 == 0)
    update_weather_with_app_msg();
}


