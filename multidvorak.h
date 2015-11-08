/* 
   This layout assumes that the OS will be translating keycodes into
   Dvorak for the first two layers, as well as an alternate pair of
   layouts for machines that aren't configured for Dvorak in the OS.

   The first layer has most of your keys in the expected positions,
   while the second layer (activated by the fn key) contains the
   digits in a numpad orientation as well as most of the punctuatiion.

   The third layer (activated by fn+esc) is just mostly function keys
   (on the right) and arrow/navcluster keys (on the left). Tapping the
   fn key by itself will go back to the first layer, and hitting the
   tab key will activate the "hardare dvorak" layers. Hitting Enter on
   this layer will reset the microcontroller in order to allow new
   firmware to be uploaded.
 */

int layer0[44] = {
    KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_0, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
    KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_0, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON,
    KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEYBOARD_LEFT_ALT, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH,
    KEY_ESC, KEY_TAB, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE, KEYBOARD_LEFT_CTRL, KEY_SPACE, PRE_FUNCTION(1), KEY_QUOTE, KEY_LEFT_BRACE, KEY_ENTER };

int layer1[44] = {
    SHIFT(KEY_1), SHIFT(KEY_2), SHIFT(KEY_MINUS), SHIFT(KEY_EQUAL), KEY_RIGHT, KEY_0, KEY_UP, KEY_7, KEY_8, KEY_9, SHIFT(KEY_8),
    SHIFT(KEY_3), SHIFT(KEY_4), SHIFT(KEY_9), SHIFT(KEY_0), KEY_LEFT, KEY_0, KEY_DOWN, KEY_4, KEY_5, KEY_6, SHIFT(KEY_RIGHT_BRACE),
    SHIFT(KEY_5), SHIFT(KEY_6), KEY_MINUS, KEY_EQUAL, KEY_TILDE, KEYBOARD_LEFT_ALT, SHIFT(KEY_7), KEY_1, KEY_2, KEY_3, KEY_BACKSLASH,
    FUNCTION(2), SHIFT(KEY_INSERT), KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_DELETE, KEYBOARD_LEFT_CTRL, KEY_SPACE, PRE_FUNCTION(1), KEY_E, KEY_0, KEY_RIGHT_BRACE };

int layer2[44] = {
    KEY_INSERT, KEY_HOME, KEY_UP, KEY_END, KEY_PAGE_UP, KEY_0, KEY_UP, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_DELETE, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_PAGE_DOWN, KEY_0, KEY_DOWN, KEY_F4, KEY_F5, KEY_F6, KEY_F11,
    0, 0, 0, 0, FUNCTION(0), KEYBOARD_LEFT_ALT, 0, KEY_F1, KEY_F2, KEY_F3, KEY_F12,
    0, FUNCTION(3), KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE, KEYBOARD_LEFT_CTRL, KEY_SPACE, PRE_FUNCTION(1), 0, 0, 0 };

int layer3[44] = {
    KEY_QUOTE, KEY_COMMA, KEY_PERIOD, KEY_P, KEY_Y, KEY_0, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L,
    KEY_A, KEY_O, KEY_E, KEY_U, KEY_I, KEY_0, KEY_D, KEY_H, KEY_T, KEY_N, KEY_S,
    KEY_SEMICOLON, KEY_Q, KEY_J, KEY_K, KEY_X, KEYBOARD_LEFT_ALT, KEY_B, KEY_M, KEY_W, KEY_V, KEY_Z,
    KEY_ESC, KEY_TAB, KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE, KEYBOARD_LEFT_CTRL, KEY_SPACE, PRE_FUNCTION(1), KEY_MINUS, KEY_SLASH, KEY_ENTER };

int layer4[44] = {
    SHIFT(KEY_1), SHIFT(KEY_2), SHIFT(KEY_LEFT_BRACE), SHIFT(KEY_RIGHT_BRACE), SHIFT(KEY_BACKSLASH), KEY_0, KEY_PAGE_UP, KEY_7, KEY_8, KEY_9, SHIFT(KEY_8),
    SHIFT(KEY_3), SHIFT(KEY_4), SHIFT(KEY_9), SHIFT(KEY_0), KEY_TILDE, KEY_0, KEY_PAGE_DOWN, KEY_4, KEY_5, KEY_6, SHIFT(KEY_EQUAL),
    SHIFT(KEY_5), SHIFT(KEY_6), KEY_LEFT_BRACE, KEY_RIGHT_BRACE, SHIFT(KEY_TILDE), KEYBOARD_LEFT_ALT, KEY_BACKSLASH, KEY_1, KEY_2, KEY_3, KEY_BACKSLASH,
    FUNCTION(2), SHIFT(KEY_INSERT), KEYBOARD_LEFT_GUI, KEYBOARD_LEFT_SHIFT, KEY_BACKSPACE, KEYBOARD_LEFT_CTRL, KEY_SPACE, PRE_FUNCTION(1), KEY_PERIOD, KEY_0, KEY_EQUAL };


int *layers[] = {layer0, layer1, layer2, layer3, layer4};

// stuff below is taken from layout_common.h but adapted to allow fn
// to function from more than one layer.

int fn_decay = 0;

void activate_fn() {
  fn_decay = 20;
};

int base_layer = 0;
int layer_to_jump = 0;

// jump to this layer when fn is released
void layer_jump() {
  layer_to_jump = 2;
};

void hwdvorak() {
  current_layer = layers[3];
  base_layer = 3;
};

void (*layer_functions[])(void) = {reset, activate_fn, layer_jump, hwdvorak};

void per_cycle() {
  if(fn_decay > 1) {
    current_layer = layers[current_layer_number + 1];
    fn_decay--;
  } else if(fn_decay == 1) {
    current_layer_number = layer_to_jump;
    fn_decay--;
  } else {
    layer_to_jump = base_layer;
    fn_decay = 0;
  }
};
