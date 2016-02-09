int fn_decay = 0;

void activate_fn() {
  fn_decay = 20;
};

int layer_to_momentary = 1;

void layer_momentary() {
  layer_to_momentary = 3;
};

int layer_to_jump = 0;

// jump to this layer when fn is released
void layer_jump() {
  layer_to_jump = 2;
};

void (*layer_functions[])(void) = {reset, activate_fn, layer_jump, layer_momentary};

// When we are sending key combinations that include modifiers, the OS
// can do some level of error-correction to prevent this scenario:

// - shift down
// - a key down
// - A inserted
// - shift up
// - a inserted

// However, fn is unlike other modifiers since the OS knows nothing
// about it; from the OS's perspective the keycodes it gets before and
// after the release of fn are unrelated. Because of this, we must let
// fn apply a little after it's been released; this is what fn_decay
// does.

void per_cycle() {
  if(fn_decay > 1) {
    current_layer = layers[layer_to_momentary];
    fn_decay--;
  } else if(fn_decay == 1) {
    current_layer_number = layer_to_jump;
    fn_decay--;
  } else {
    layer_to_momentary = 1;
    layer_to_jump = 0;
    fn_decay = 0;
  }
};
