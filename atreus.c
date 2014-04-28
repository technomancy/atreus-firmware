#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define ROW_COUNT 4
#define COL_COUNT 11

#define DEBOUNCE_PASSES 3

#define FN_PRESSED (~PINB & 8)

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

uint8_t debouncing_keys[6];
uint8_t debouncing_modifier_keys;

void reset(void);



// Outputs
// |------------+----+----+----+----|
// | row number |  0 |  1 |  2 |  3 |
// |------------+----+----+----+----|
// | pin number | D0 | D1 | D2 | D3 |
// |------------+----+----+----+----|

// Inputs
// |---------------+----+----+----+----+----+----+----+----+----+----+----|
// | column number |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
// |---------------+----+----+----+----+----+----+----+----+----+----+----|
// | pin number    | B0 | B1 | B2 | B3 | B4 | B5 | B6 | B7 | F4 | F5 | F6 |
// |---------------+----+----+----+----+----+----+----+----+----+----+----|



// TODO: create layout mapping tool

#include "layouts.h"

int *current_row;
int pressed_count = 0;



void press(int keycode) {
  if(!keycode) return;
  if(keycode == 255) {
    reset(); // TODO: make a table of codes -> functions
  } else if(keycode > 108 && pressed_count < 6) {
    keyboard_modifier_keys |= KEY_SHIFT;
    keyboard_keys[pressed_count++] = (keycode - 108);
  } else if(keycode > 100) {
    keyboard_modifier_keys |= (keycode - 100);
  } else if(pressed_count < 6){
    keyboard_keys[pressed_count++] = keycode;
  };
};

void activate_row(int row) {
  PORTD = (char)(~(1 << row)) | 32; // leave the LED on
  _delay_us(50);
};

void scan_row(int row) {
  // if((~PINF) & 64) reset();
  unsigned int col_bits = ((~PINF << 4) & (1024 | 512 | 256)) | (~PINB & 255);
  /* for(int col = 0; col < COL_COUNT; col++) { */
  /*   if(col_bits & 1024) { */
  /*     press(current_row[col]); */
  /*   } */
  /*   col_bits << 1; */
  /* } */
  if(col_bits & 1024) press(current_row[0]);
  if(col_bits & 512) press(current_row[1]);
  if(col_bits & 256) press(current_row[2]);
  if(col_bits & 128) press(current_row[3]);
  if(col_bits & 64) press(current_row[4]);
  if(col_bits & 32) press(current_row[5]);
  if(col_bits & 16) press(current_row[6]);
  if(col_bits & 8) press(current_row[7]);
  if(col_bits & 4) press(current_row[8]);
  if(col_bits & 2) press(current_row[9]);
  if(col_bits & 1) press(current_row[10]);
};



void init() {
  CPU_PRESCALE(0);
  DDRD = 255;
  DDRB = DDRF = 0;
  PORTB = PORTF = 255;
  usb_init();
  while (!usb_configured()) /* wait */ ;
  _delay_ms(1000);
};

void clear_keys() {
  keyboard_modifier_keys = 0;
  for(int i = 0; i < 6; i++) {
    keyboard_keys[i] = 0;
  };
};

void scan_rows() {
  // 4th row is still active from last scan
  current_row = FN_PRESSED ? fn_layout : base_layout;
  pressed_count = 0;
  for(int i = 0; i < ROW_COUNT; i++) {
    activate_row(i);
    scan_row(i);
    current_row += COL_COUNT;
  };
};

void debounce() {
  int passes = 0;
  while(passes < DEBOUNCE_PASSES) {
    memcpy(keyboard_keys, debouncing_keys, 6);
    debouncing_modifier_keys = keyboard_modifier_keys;
    scan_rows();
    _delay_ms(1);
    // TODO: include fn in debouncing calculation
    if(!pressed_count || \
       (memcmp(keyboard_keys, debouncing_keys, pressed_count) &&    \
        debouncing_modifier_keys == keyboard_modifier_keys)) {
      passes++;
    } else {
      passes = 0;
    }
  }
};

int main() {
  init();
  while(1) {
    debounce();
    usb_keyboard_send();
    clear_keys();
  };
};

void reset(void) {
  UDCON = 1; USBCON = (1<<FRZCLK); UCSR1B = 0;
  _delay_ms(5);
  EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
  TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
  DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
  PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
  asm volatile("jmp 0x7E00");
};
