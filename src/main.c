#include <pebble.h>

static Window *s_main_window;
static TextLayer *cSpeed_layer;
char cSpeed[4];
int speed = 45;

void process_tuple(Tuple *t)
{
  //Get key
  int key = t->key;
 
  //Get integer value, if present
  int value = t->value->int32;
 
 
  //Decide what to do
  switch(key) {
    case speed:
      //speed received
      snprintf(cSpeed, sizeof(cSpeed), "%d", value);
      text_layer_set_text(cSpeed_layer, (char*) &cSpeed);
      break;
  }
}

static void in_received_handler(DictionaryIterator *iter, void *context)
{
    (void) context;
     
    //Get data
    Tuple *t = dict_read_first(iter);
    while(t != NULL)
    {
        process_tuple(t);
         
        //Get next
        t = dict_read_next(iter);
    }
}


/*
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  speed = speed+5;
  snprintf(cSpeed, sizeof(cSpeed), "%d", speed);
  text_layer_set_text(cSpeed_layer, cSpeed);
}
*/
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(cSpeed_layer, cSpeed);
}
/*
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  speed = speed-5;
  snprintf(cSpeed, sizeof(cSpeed), "%d", speed);
  text_layer_set_text(cSpeed_layer, cSpeed);
}
*/
static void click_config_provider(void *context) {
  // Register the ClickHandlers
//  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
//  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create output TextLayer
  cSpeed_layer = text_layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  text_layer_set_background_color(cSpeed_layer, GColorBlack);
  text_layer_set_text_color(cSpeed_layer, GColorClear);
  //snprintf(cSpeed, sizeof(cSpeed), "%d", speed);
  text_layer_set_text(cSpeed_layer, "N/A");
  text_layer_set_font(cSpeed_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(cSpeed_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(cSpeed_layer));
  

}



static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  text_layer_destroy(cSpeed_layer);
}

static void init() {
  // Create main Window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
    window_set_click_config_provider(s_main_window, click_config_provider);
    //Register AppMessage events
     app_message_register_inbox_received(in_received_handler);
     app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());    //Largest possible input and output buffer sizes
    window_stack_push(s_main_window, true);
}

static void deinit() {
  // Destroy main Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}