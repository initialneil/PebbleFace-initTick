#pragma once
#include <pebble.h>
#include "config.h"

//#define SHOW_SCREENSHOT

// common type and data
typedef struct {
  int hours;
  int minutes;
  int seconds;
} Time;

enum APP_MSG_TYPE {
  PEBBLEKIT_JS_READY = 0,
  SHOW_SECOND,
  WEATHER_ICON_KEY,
  WEATHER_TEMPERATURE_KEY,
  WEATHER_CITY_KEY,
  SHOW_WEATHER,
  SHOW_LOCATION,
  DEFAULT_LOCATION,
  LOCATION_OPT,
  COLOR_SCHEME,
};

static bool s_pebblekit_js_ready = false;
static void set_pebblekit_js_ready(bool ready) {
  s_pebblekit_js_ready = ready;
}

// convert color in string to UInt
static const char ASCII_0_VALU = 48;
static const char ASCII_9_VALU = 57;
static const char ASCII_A_VALU = 65;
static const char ASCII_F_VALU = 70;
static unsigned int HexStringToUInt(char const* hexstring) {
  unsigned int result = 0;
  char const *c = hexstring;
  char thisC;
  while( (thisC = *c) != 0 )
  {
    unsigned int add = 0;

    result <<= 4;
    if( thisC >= ASCII_0_VALU &&  thisC <= ASCII_9_VALU )
      add = thisC - ASCII_0_VALU;
    else if( thisC >= ASCII_A_VALU && thisC <= ASCII_F_VALU)
      add = thisC - ASCII_A_VALU + 10;
      else {
      add = 0;
      //printf("Unrecognised hex character \"%c\"\n", thisC);
      //return 0;
    }
    result += add;
    ++c;
  }
  return result;
}

static GColor HexStringToGColor(char const* hexstring) {
  return GColorFromHEX(HexStringToUInt(hexstring));
}

#define COLORS true
#define COLOR_PRESET -1

#if COLOR_PRESET == 0

// panel color
#define MINUTE_DOTS_COLOR GColorDarkGray
#define HOUR_DOTS_COLOR GColorLightGray
#define HOUR_ENPHASIS_COLOR GColorWhite

#define PANEL_IN_COLOR GColorBlack
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define MINUTE_HAND_COLOR GColorWhite
#define MINUTE_HAND_INSIDE_COLOR GColorBlack

#define HOUR_HAND_COLOR GColorWhite
#define HOUR_HAND_INSIDE_COLOR GColorBlack

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorWhite
#define CENTER_DOT_IN_COLOR GColorBlack

// month
#define MONTH_COLOR GColorWhite
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorChromeYellow
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

// weather
#define WEATHER_COLOR_STROKE GColorWhite
#define WEATHER_COLOR_FILL GColorClear
#define TEMPERATURE_COLOR GColorChromeYellow

// city
#define CITY_COLOR GColorWhite

#elif COLOR_PRESET == 1

// panel color
#define MINUTE_DOTS_COLOR GColorLightGray
#define HOUR_DOTS_COLOR GColorDarkGray
#define HOUR_ENPHASIS_COLOR GColorDarkGray

#define PANEL_IN_COLOR GColorWhite
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define MINUTE_HAND_COLOR GColorBlack
#define MINUTE_HAND_INSIDE_COLOR GColorWhite

#define HOUR_HAND_COLOR GColorBlack
#define HOUR_HAND_INSIDE_COLOR GColorWhite

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorBlack
#define CENTER_DOT_IN_COLOR GColorWhite

// month
#define MONTH_COLOR GColorWhite
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorChromeYellow
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

// weather
#define WEATHER_COLOR_STROKE GColorWhite
#define WEATHER_COLOR_FILL GColorClear
#define TEMPERATURE_COLOR GColorChromeYellow

// city
#define CITY_COLOR GColorBlack

#elif COLOR_PRESET == 2

// panel color
#define MINUTE_DOTS_COLOR GColorChromeYellow
#define HOUR_DOTS_COLOR GColorChromeYellow
#define HOUR_ENPHASIS_COLOR GColorBlack

#define PANEL_IN_COLOR GColorBlack
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define MINUTE_HAND_COLOR GColorWhite
#define MINUTE_HAND_INSIDE_COLOR GColorBlack

#define HOUR_HAND_COLOR GColorWhite
#define HOUR_HAND_INSIDE_COLOR GColorBlack

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorWhite
#define CENTER_DOT_IN_COLOR GColorBlack

// month
#define MONTH_COLOR GColorVividCerulean
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorVividCerulean
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

// weather
#define WEATHER_COLOR_STROKE GColorWhite
#define WEATHER_COLOR_FILL GColorClear
#define TEMPERATURE_COLOR GColorChromeYellow

// city
#define CITY_COLOR GColorBlack

#elif COLOR_PRESET == 3

// panel color
#define MINUTE_DOTS_COLOR GColorDarkGray
#define HOUR_DOTS_COLOR GColorGreen
#define HOUR_ENPHASIS_COLOR GColorGreen

#define PANEL_IN_COLOR GColorBlack
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define MINUTE_HAND_COLOR GColorWhite
#define MINUTE_HAND_INSIDE_COLOR GColorBlack

#define HOUR_HAND_COLOR GColorWhite
#define HOUR_HAND_INSIDE_COLOR GColorBlack

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorWhite
#define CENTER_DOT_IN_COLOR GColorBlack

// month
#define MONTH_COLOR GColorWhite
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorChromeYellow
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

// weather
#define WEATHER_COLOR_STROKE GColorWhite
#define WEATHER_COLOR_FILL GColorClear
#define TEMPERATURE_COLOR GColorChromeYellow

// city
#define CITY_COLOR GColorWhite

#endif



