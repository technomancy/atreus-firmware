int fn_decay = 0;

void activate_fn() {
  fn_decay = 10;
};

void (*layer_functions[])(void) = {reset, activate_fn};

void per_cycle() {
  if(fn_decay) {
    current_layer = layers[1];
    fn_decay--;
  }
};
