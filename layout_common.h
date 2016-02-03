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
    current_layer = layers[1];

    // This hack checks each pressed key to see if it is the left
    // shift key. If the left shift is pressed (in combination with
    // the fn key) we switch to layer 2 instead of 1, and remove the
    // left shift from the list of pressed keys.
    for(int i = 0; i < pressed_count; i++) {
      unsigned int keycode = current_layer[presses[i]];
      if(keycode == KEYBOARD_LEFT_SHIFT) {
        presses[i] = 0;
        current_layer = layers[2];
      }
    }

    fn_decay--;
  } else if(fn_decay == 1) {
    current_layer_number = layer_to_jump;
    fn_decay--;
  } else {
    layer_to_jump = 0;
    fn_decay = 0;
  }
};
