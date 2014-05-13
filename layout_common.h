int fn_decay = 0;

void activate_fn() {
  fn_decay = 15;
};

void (*layer_functions[])(void) = {reset, activate_fn};

int pressed_while_fn = 0;

void per_cycle() {
  if(fn_decay > 1) {
    current_layer = layers[1];
    fn_decay--;
    if(pressed_count > 1) pressed_while_fn = 1;
  } else if(fn_decay == 1 && !pressed_while_fn) {
    current_layer_number = current_layer_number ? 0 : 2;
    fn_decay--;
  } else {
    fn_decay = 0;
    pressed_while_fn = 0;
  }
};
