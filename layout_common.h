int fn_decay = 0;

void activate_fn() {
  fn_decay = 20;
};

int layer_to_jump = 0;

// jump to this layer when fn is released
void layer_jump() {
  layer_to_jump = 2;
};

void (*layer_functions[])(void) = {reset, activate_fn, layer_jump};

void per_cycle() {
  if(fn_decay > 1) {
    current_layer = layers[1];
    fn_decay--;
  } else if(fn_decay == 1) {
    current_layer_number = layer_to_jump;
    fn_decay--;
  } else {
    layer_to_jump = 0;
    fn_decay = 0;
  }
};
