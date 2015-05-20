#include <pebble.h>
#include "watchface.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_icon;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_textlayer_1;
static GColor *palette;
char *time_text;

#define MAX_SIZE 6

void update_time(struct tm* tick_time){
  strftime(time_text, MAX_SIZE, "%H:%M", tick_time);
  text_layer_set_text(s_textlayer_1, time_text);
}

void change_logo_color(){
  palette[0] = GColorFromRGB(rand()/255,rand()/255,rand()/255);
}

static void initialise_ui(void) {
  s_window = window_create();
//   window_set_fullscreen(s_window, true);
  
  time_text = malloc(MAX_SIZE);
  
  s_res_icon = gbitmap_create_with_resource(RESOURCE_ID_ICON);
  palette = gbitmap_get_palette(s_res_icon);
  palette[0] = GColorMalachite;
  palette[1] = /*GColorBulgarianRose;*/ GColorPictonBlue;
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 12, 144, 144));
  bitmap_layer_set_bitmap(s_bitmaplayer_1, s_res_icon);
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(0, 75, 144, 19));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text_color(s_textlayer_1, GColorBlack);
  text_layer_set_text(s_textlayer_1, "Time");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
}

static void destroy_ui(void) {
  free(time_text);
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_textlayer_1);
  gbitmap_destroy(s_res_icon);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_watchface(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_watchface(void) {
  window_stack_remove(s_window, true);
}
