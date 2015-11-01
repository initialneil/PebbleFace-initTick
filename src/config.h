#include <pebble.h>

struct CONFIG_TYPE {
  bool SHOW_SECOND;
  bool WEATHER_CELSIUS;
  bool SHOW_HOUR_DIGITS;
  
  // panel color
  GColor MINUTE_DOTS_COLOR;
  GColor HOUR_DOTS_COLOR;
  GColor HOUR_ENPHASIS_COLOR;
  
  GColor PANEL_IN_COLOR;
  GColor PANEL_OUT_COLOR;
  
  // hand color
  GColor MINUTE_HAND_COLOR;
  GColor MINUTE_HAND_INSIDE_COLOR;
  
  GColor HOUR_HAND_COLOR;
  GColor HOUR_HAND_INSIDE_COLOR;
  
  GColor SECOND_HAND_COLOR;
  
  // center dot color
  GColor CENTER_DOT_COLOR;
  GColor CENTER_DOT_IN_COLOR;
  
  // month
  GColor MONTH_COLOR;
  GColor MONTH_BACKGROUND_COLOR;
  
  // date
  GColor DATE_COLOR;
  GColor DATE_BACKGROUND_COLOR;
  
  // weekday
  GColor WEEKDAY_COLOR;
  GColor WEEKDAY_BACKGROUND_COLOR;
  
  // weather
  GColor WEATHER_COLOR_STROKE;
  GColor WEATHER_COLOR_FILL;
  GColor TEMPERATURE_COLOR;
  
  // city
  GColor CITY_COLOR;
};

static void load_default_config(struct CONFIG_TYPE *config) {
  APP_LOG(APP_LOG_LEVEL_INFO, "load default config");
  config->SHOW_SECOND = false;
  config->WEATHER_CELSIUS = true;
  config->SHOW_HOUR_DIGITS = true;
  
  // panel color
  config->MINUTE_DOTS_COLOR = GColorDarkGray;
  config->HOUR_DOTS_COLOR = GColorGreen;
  config->HOUR_ENPHASIS_COLOR = GColorGreen;
  
  config->PANEL_IN_COLOR = GColorBlack;
  config->PANEL_OUT_COLOR = GColorBlack;
  
  // hand color
  config->MINUTE_HAND_COLOR = GColorWhite;
  config->MINUTE_HAND_INSIDE_COLOR = GColorBlack;
  
  config->HOUR_HAND_COLOR = GColorWhite;
  config->HOUR_HAND_INSIDE_COLOR = GColorBlack;
  
  config->SECOND_HAND_COLOR = GColorChromeYellow;
  
  // center dot color
  config->CENTER_DOT_COLOR = GColorWhite;
  config->CENTER_DOT_IN_COLOR = GColorBlack;
  
  // month
  config->MONTH_COLOR = GColorWhite;
  config->MONTH_BACKGROUND_COLOR = GColorClear;
  
  // date
  config->DATE_COLOR = GColorChromeYellow;
  config->DATE_BACKGROUND_COLOR = GColorClear;
  
  // weekday
  config->WEEKDAY_COLOR = GColorVividCerulean;
  config->WEEKDAY_BACKGROUND_COLOR = GColorClear;
  
  // weather
  config->WEATHER_COLOR_STROKE = GColorWhite;
  config->WEATHER_COLOR_FILL = GColorClear;
  config->TEMPERATURE_COLOR = GColorChromeYellow;
  
  // city
  config->CITY_COLOR = GColorWhite;
}

static void set_config_color_value(struct CONFIG_TYPE *config, const char str_key[], GColor clr) {
  if (strcmp(str_key, "color_minute_dot") == 0) {
    config->MINUTE_DOTS_COLOR = clr;
  } else if (strcmp(str_key, "color_hour_dot") == 0) {
    config->HOUR_DOTS_COLOR = clr;
  } else if (strcmp(str_key, "color_hour_dot_emphasis") == 0) {
    config->HOUR_ENPHASIS_COLOR = clr;
  } else if (strcmp(str_key, "color_panel_in") == 0) {
    config->PANEL_IN_COLOR = clr;
  } else if (strcmp(str_key, "color_panel_out") == 0) {
    config->PANEL_OUT_COLOR = clr;
  } else if (strcmp(str_key, "color_minute_hand_out") == 0) {
    config->MINUTE_HAND_COLOR = clr;
  } else if (strcmp(str_key, "color_minute_hand_in") == 0) {
    config->MINUTE_HAND_INSIDE_COLOR = clr;
  } else if (strcmp(str_key, "color_hour_hand_out") == 0) {
    config->HOUR_HAND_COLOR = clr;
  } else if (strcmp(str_key, "color_hour_hand_in") == 0) {
    config->HOUR_HAND_INSIDE_COLOR = clr;
  } else if (strcmp(str_key, "color_second_hand") == 0) {
    config->SECOND_HAND_COLOR = clr;
  } else if (strcmp(str_key, "color_center_dot_out") == 0) {
    config->CENTER_DOT_COLOR = clr;
  } else if (strcmp(str_key, "color_center_dot_in") == 0) {
    config->CENTER_DOT_IN_COLOR = clr;
  } else if (strcmp(str_key, "color_month") == 0) {
    config->MONTH_COLOR = clr;
  } else if (strcmp(str_key, "") == 0) {
    //config->MONTH_BACKGROUND_COLOR = clr;
  } else if (strcmp(str_key, "color_date") == 0) {
    config->DATE_COLOR = clr;
  } else if (strcmp(str_key, "") == 0) {
    //config->DATE_BACKGROUND_COLOR = clr;
  } else if (strcmp(str_key, "color_weekday") == 0) {
    config->WEEKDAY_COLOR = clr;
  } else if (strcmp(str_key, "") == 0) {
    //config->WEEKDAY_BACKGROUND_COLOR = clr;
  } else if (strcmp(str_key, "color_weather_icon_stroke") == 0) {
    config->WEATHER_COLOR_STROKE = clr;
  } else if (strcmp(str_key, "color_weather_icon_fill") == 0) {
    config->WEATHER_COLOR_FILL = clr;
  } else if (strcmp(str_key, "color_temperature") == 0) {
    config->TEMPERATURE_COLOR = clr;
  } else if (strcmp(str_key, "color_location") == 0) {
    config->CITY_COLOR = clr;
  }
}



