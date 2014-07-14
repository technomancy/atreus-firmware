#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>

void usb_init(void);            // initialize everything
uint8_t usb_configured(void);       // is the USB port configured

int8_t usb_keyboard_press(uint8_t key, uint8_t modifier);
int8_t usb_keyboard_send(void);
extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern volatile uint8_t keyboard_leds;

// This file does not include the HID debug functions, so these empty
// macros replace them with nothing, so users can compile code that
// has calls to these functions.
#define usb_debug_putchar(c)
#define usb_debug_flush_output()


#define KEY_CTRL    0x01
#define KEY_SHIFT   0x02
#define KEY_ALT     0x04
#define KEY_GUI     0x08
#define KEY_LEFT_CTRL   0x01
#define KEY_LEFT_SHIFT  0x02
#define KEY_LEFT_ALT    0x04
#define KEY_LEFT_GUI    0x08
#define KEY_RIGHT_CTRL  0x10
#define KEY_RIGHT_SHIFT 0x20
#define KEY_RIGHT_ALT   0x40
#define KEY_RIGHT_GUI   0x80

#define KEY_A                            4
#define KEY_B                            5
#define KEY_C                            6
#define KEY_D                            7
#define KEY_E                            8
#define KEY_F                            9
#define KEY_G                           10
#define KEY_H                           11
#define KEY_I                           12
#define KEY_J                           13
#define KEY_K                           14
#define KEY_L                           15
#define KEY_M                           16
#define KEY_N                           17
#define KEY_O                           18
#define KEY_P                           19
#define KEY_Q                           20
#define KEY_R                           21
#define KEY_S                           22
#define KEY_T                           23
#define KEY_U                           24
#define KEY_V                           25
#define KEY_W                           26
#define KEY_X                           27
#define KEY_Y                           28
#define KEY_Z                           29
#define KEY_1                           30
#define KEY_2                           31
#define KEY_3                           32
#define KEY_4                           33
#define KEY_5                           34
#define KEY_6                           35
#define KEY_7                           36
#define KEY_8                           37
#define KEY_9                           38
#define KEY_0                           39
#define KEY_ENTER                       40
#define KEY_ESC                         41
#define KEY_BACKSPACE                   42
#define KEY_TAB                         43
#define KEY_SPACE                       44
#define KEY_MINUS                       45
#define KEY_EQUAL                       46
#define KEY_LEFT_BRACE                  47
#define KEY_RIGHT_BRACE                 48
#define KEY_BACKSLASH                   49
#define KEY_NUMBER                      50
#define KEY_SEMICOLON                   51
#define KEY_QUOTE                       52
#define KEY_TILDE                       53
#define KEY_COMMA                       54
#define KEY_PERIOD                      55
#define KEY_SLASH                       56
#define KEY_CAPS_LOCK                   57
#define KEY_F1                          58
#define KEY_F2                          59
#define KEY_F3                          60
#define KEY_F4                          61
#define KEY_F5                          62
#define KEY_F6                          63
#define KEY_F7                          64
#define KEY_F8                          65
#define KEY_F9                          66
#define KEY_F10                         67
#define KEY_F11                         68
#define KEY_F12                         69
#define KEY_PRINTSCREEN                 70
#define KEY_SCROLL_LOCK                 71
#define KEY_PAUSE                       72
#define KEY_INSERT                      73
#define KEY_HOME                        74
#define KEY_PAGE_UP                     75
#define KEY_DELETE                      76
#define KEY_END                         77
#define KEY_PAGE_DOWN                   78
#define KEY_RIGHT                       79
#define KEY_LEFT                        80
#define KEY_DOWN                        81
#define KEY_UP                          82
#define KEY_NUM_LOCK                    83
#define KEYPAD_SLASH                    84
#define KEYPAD_ASTERIX                  85
#define KEYPAD_MINUS                    86
#define KEYPAD_PLUS                     87
#define KEYPAD_ENTER                    88
#define KEYPAD_1                        89
#define KEYPAD_2                        90
#define KEYPAD_3                        91
#define KEYPAD_4                        92
#define KEYPAD_5                        93
#define KEYPAD_6                        94
#define KEYPAD_7                        95
#define KEYPAD_8                        96
#define KEYPAD_9                        97
#define KEYPAD_0                        98
#define KEYPAD_PERIOD                   99
#define KEYBOARD_NON_US_SLASH_PIPE     100
#define KEYBOARD_APPLICATION           101
#define KEYBOARD_POWER                 102
#define KEYPAD_EQUAL                   103
#define KEYBOARD_F13                   104
#define KEYBOARD_F14                   105
#define KEYBOARD_F15                   106
#define KEYBOARD_F16                   107
#define KEYBOARD_F17                   108
#define KEYBOARD_F18                   109
#define KEYBOARD_F19                   110
#define KEYBOARD_F20                   111
#define KEYBOARD_F21                   112
#define KEYBOARD_F22                   113
#define KEYBOARD_F23                   114
#define KEYBOARD_F24                   115
#define KEYBOARD_EXECUTE               116
#define KEYBOARD_HELP                  117
#define KEYBOARD_MENU                  118
#define KEYBOARD_SELECT                119
#define KEYBOARD_STOP                  120
#define KEYBOARD_AGAIN                 121
#define KEYBOARD_UNDO                  122
#define KEYBOARD_CUT                   123
#define KEYBOARD_COPY                  124
#define KEYBOARD_PASTE                 125
#define KEYBOARD_FIND                  126
#define KEYBOARD_MUTE                  127
#define KEYBOARD_VOLUME_UP             128
#define KEYBOARD_VOLUME_DOWN           129
#define KEYBOARD_LOCKING_CAPS_LOCK     130
#define KEYBOARD_LOCKING_NUM_LOCK      131
#define KEYBOARD_LOCKING_SCROLL_LOCK   132
#define KEYPAD_COMMA                   133
#define KEYPAD_EQUAL_SIGN              134
#define KEYBOARD_INTERNATIONAL1        135
#define KEYBOARD_INTERNATIONAL2        136
#define KEYBOARD_INTERNATIONAL3        137
#define KEYBOARD_INTERNATIONAL4        138
#define KEYBOARD_INTERNATIONAL5        139
#define KEYBOARD_INTERNATIONAL6        140
#define KEYBOARD_INTERNATIONAL7        141
#define KEYBOARD_INTERNATIONAL8        142
#define KEYBOARD_INTERNATIONAL9        143
#define KEYBOARD_LANG1ONAL9            144
#define KEYBOARD_LANG2                 145
#define KEYBOARD_LANG3                 146
#define KEYBOARD_LANG4                 147
#define KEYBOARD_LANG5                 148
#define KEYBOARD_LANG6                 149
#define KEYBOARD_LANG7                 150
#define KEYBOARD_LANG8                 151
#define KEYBOARD_LANG9                 152
#define KEYBOARD_ALTERNATE_ERASE       153
#define KEYBOARD_SYSREQ_ATTENTION      154
#define KEYBOARD_CANCEL                155
#define KEYBOARD_CLEAR                 156
#define KEYBOARD_PRIOR                 157
#define KEYBOARD_RETURN                158
#define KEYBOARD_SEPARATOR             159
#define KEYBOARD_OUT                   160
#define KEYBOARD_OPER                  161
#define KEYBOARD_CLEAR_AGAIN           162
#define KEYBOARD_CRSEL_PROPS           163
#define KEYBOARD_EXSEL                 164

#define KEYPAD_00                      176
#define KEYPAD_000                     177
#define THOUSANDS_SEPARATOR            178
#define DECIMAL_SEPARATOR              179
#define CURRENCY_UNIT                  180
#define CURRENCY_SUBUNIT               181
#define KEYPAD_LEFT_PAREN              182
#define KEYPAD_RIGHT_PAREN             183
#define KEYPAD_LEFT_BRACE              184
#define KEYPAD_RIGHT_BRACE             185
#define KEYPAD_TAB                     186
#define KEYPAD_BACKSPACE               187
#define KEYPAD_A                       188
#define KEYPAD_B                       189
#define KEYPAD_C                       190
#define KEYPAD_D                       191
#define KEYPAD_E                       192
#define KEYPAD_F                       193
#define KEYPAD_XOR                     194
#define KEYPAD_CARET                   195
#define KEYPAD_PERCENT                 196
#define KEYPAD_LESS_THAN               197
#define KEYPAD_GREATER_THAN            198
#define KEYPAD_AMPERSAND               199
#define KEYPAD_DOUBLE_AMPERSAND        200
#define KEYPAD_PIPE                    201
#define KEYPAD_DOUBLE_PIPE             202
#define KEYPAD_COLON                   203
#define KEYPAD_POUND                   204
#define KEYPAD_SPACE                   205
#define KEYPAD_AT                      206
#define KEYPAD_BANG                    207
#define KEYPAD_MEM_STORE               208
#define KEYPAD_MEM_RECALL              209
#define KEYPAD_MEM_CLEAR               210
#define KEYPAD_MEM_ADD                 211
#define KEYPAD_MEM_SUBTRACT            212
#define KEYPAD_MEM_MULTIPLY            213
#define KEYPAD_MEM_DIVIDE              214
#define KEYPAD_PLUS_MINUS              215
#define KEYPAD_CLEAR                   216
#define KEYPAD_CLEAR_ENTRY             217
#define KEYPAD_BINARY                  218
#define KEYPAD_OCTAL                   219
#define KEYPAD_DECIMAL                 220
#define KEYPAD_HEXADECIMAL             221

#define KEYBOARD_LEFT_CTRL             224
#define KEYBOARD_LEFT_SHIFT            225
#define KEYBOARD_LEFT_ALT              226
#define KEYBOARD_LEFT_GUI              227
#define KEYBOARD_RIGHT_CTRL            228
#define KEYBOARD_RIGHT_SHIFT           229
#define KEYBOARD_RIGHT_ALT             230
#define KEYBOARD_RIGHT_GUI             231

#define USB_MIN_MODIFIER KEYBOARD_LEFT_CTRL
#define USB_MAX_MODIFIER KEYBOARD_RIGHT_GUI

#define USB_MAX_KEY KEYBOARD_RIGHT_GUI

// Everything below this point is only intended for usb_serial.c
#ifdef USB_SERIAL_PRIVATE_INCLUDE
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define EP_TYPE_CONTROL         0x00
#define EP_TYPE_BULK_IN         0x81
#define EP_TYPE_BULK_OUT        0x80
#define EP_TYPE_INTERRUPT_IN        0xC1
#define EP_TYPE_INTERRUPT_OUT       0xC0
#define EP_TYPE_ISOCHRONOUS_IN      0x41
#define EP_TYPE_ISOCHRONOUS_OUT     0x40

#define EP_SINGLE_BUFFER        0x02
#define EP_DOUBLE_BUFFER        0x06

#define EP_SIZE(s)  ((s) == 64 ? 0x30 :         \
                     ((s) == 32 ? 0x20 :        \
                      ((s) == 16 ? 0x10 :       \
                       0x00)))

#define MAX_ENDPOINT        4

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

#if defined(__AVR_AT90USB162__)
#define HW_CONFIG()
#define PLL_CONFIG() (PLLCSR = ((1<<PLLE)|(1<<PLLP0)))
#define USB_CONFIG() (USBCON = (1<<USBE))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_ATmega32U4__)
#define HW_CONFIG() (UHWCON = 0x01)
#define PLL_CONFIG() (PLLCSR = 0x12)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_AT90USB646__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x1A)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#elif defined(__AVR_AT90USB1286__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x16)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#endif

// standard control endpoint request types
#define GET_STATUS          0
#define CLEAR_FEATURE           1
#define SET_FEATURE         3
#define SET_ADDRESS         5
#define GET_DESCRIPTOR          6
#define GET_CONFIGURATION       8
#define SET_CONFIGURATION       9
#define GET_INTERFACE           10
#define SET_INTERFACE           11
// HID (human interface device)
#define HID_GET_REPORT          1
#define HID_GET_IDLE            2
#define HID_GET_PROTOCOL        3
#define HID_SET_REPORT          9
#define HID_SET_IDLE            10
#define HID_SET_PROTOCOL        11
// CDC (communication class device)
#define CDC_SET_LINE_CODING     0x20
#define CDC_GET_LINE_CODING     0x21
#define CDC_SET_CONTROL_LINE_STATE  0x22
#endif
#endif
