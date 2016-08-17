//----------------------------------------------------------------------------------
//
// Project 19.1 from "Programming Pebble in C"
// 
// ishotjr, August 2016
// Mike Jipping, August 2016

#include <pebble.h>

// These declarations are necessary to run on the watch
static Window *s_window;
static Layer *s_layer;

// Points for animal path
// TODO: turn into husky!
static const GPathInfo animal_points = {
  .num_points = 43,
  .points = (GPoint []) {
    // head
    {0,72}, {58,72}, {42,88}, {12,72}, {52,14}, {54,29}, {72,9},
    // body
    {110,23}, {126,43}, {133,73}, 
    // tail to tip
    {115,118}, {92,124}, {74,108}, {84,80}, {105,88}, {111,102},
    {98,113}, {84, 104}, {91,96}, {100,101}, 
    // tip to foot
    {93,101}, {90,105}, {97,107}, {104,100},
    {92,91}, {79,108}, {96,116}, {113,104}, {110,80},
    // foot
    {104,74}, {93,71}, {100,68}, {96,58},
    // other foot
    {72,72}, {72,91}, {65,101}, {49,101}, {52,97}, {65,90}, 
    // the rest
    {58,45}, {58,72}, {51,14}, {58, 72}
  }
};


// draw animal path along prescribed points
static void prv_draw_animal(GContext *ctx) {

  GPath *animal_path = gpath_create(&animal_points);

  graphics_context_set_fill_color(ctx, GColorGreen);
  gpath_draw_filled(ctx, animal_path);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  gpath_draw_outline(ctx, animal_path);
}

// layer is never marked dirty again, so only called once
static void layer_update_callback(Layer *layer, GContext *ctx) {
  prv_draw_animal(ctx);
}


static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  GRect frame = layer_get_frame(window_layer);

  s_layer = layer_create(frame);
  layer_set_update_proc(s_layer, layer_update_callback);
  layer_add_child(window_layer, s_layer);
}

static void prv_window_unload(Window *window) {
  layer_destroy(s_layer);
}

static void prv_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });
  const bool animated = true;
  window_stack_push(s_window, animated);
}

static void prv_deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  prv_init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_window);

  app_event_loop();
  prv_deinit();
}
