#include <pebble.h>
#include "watchface.h"

  
void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time(tick_time);
  if( tick_time->tm_sec % 5 == 0)
    change_logo_color();
}
  
void init(){
  show_watchface();
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}
  
void deinit(){
  hide_watchface();
  tick_timer_service_unsubscribe();
}

int main(void){
  init();
  app_event_loop();
  deinit();
}