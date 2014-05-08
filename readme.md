# Atreus Firmware

This is my own firmware for the [Atreus keyboard](https://github.com/technomancy/atreus) I designed and built.

## Usage

Install `gcc-avr` and the
[teensy loader](http://www.pjrc.com/teensy/loader_cli.html).

To use the default layout, `cp layout_qwerty.h layout.h`, then run
`make upload`. To use another layout, load `atreus.el` in Emacs and
run `M-x atreus-make`, giving it the layout JSON file you want to use,
followed by `make upload`.

Designed to run on a Teensy 2 but could probably be adapted to run on
other USB-capable atmega boards.

## Pinout

Outputs:

    |------------+----+----+----+----|
    | row number |  0 |  1 |  2 |  3 |
    |------------+----+----+----+----|
    | pin number | D0 | D1 | D2 | D3 |
    |------------+----+----+----+----|

Inputs:

    |---------------+----+----+----+----+----+----+----+----+----+----+----|
    | column number |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
    |---------------+----+----+----+----+----+----+----+----+----+----+----|
    | pin number    | B0 | B1 | B2 | B3 | B4 | B5 | B6 | B7 | F4 | F5 | F6 |
    |---------------+----+----+----+----+----+----+----+----+----+----+----|

## Layouts in JSON

See `qwerty.json` for an example. `M-x atreus-make` will compile a
given JSON file into a `.hex` file for uploading, and `M-x
atreus-view` will compile JSON into an HTML table and open it in the
browser.

TODO: describe JSON format more thoroughly.

## Layouts in C

Layouts in C are arrays of integers. For basic key presses, use the
keycodes defined in `usb_keyboard.h`. For shifted key presses, add 100
to the code listed there. Layouts can also include references to
functions to execute. Place a `void` function pointer in the
`layout_functions` array and add 300 to the index of the function, and
that keycode will cause the function to be invoked.

The `layouts` pointer should be set to an array of layouts. Every scan
through the keyboard matrix will set the current layout to the
`current_layout_number`th element of the `layouts` array. To make a
keybinding that changes the current layout, simply set this number.

However, most functions will be called the final pass where each
keypress is looked up in the currently active layout. That means if
you have a function that changes the current layout, it needs to run
sooner so it can affect regular keycode lookups. Keycodes between 200
and 300 will trigger functions that run on a separate pre-invoke pass
before the rest of the keycodes are looked up, so this is how
layer-changing functions should be defined.

## How it works

Since the microcontroller has a limited number of pins, the switches
are wired in a matrix where each has its positive contact connected to
those in the same row and its negative contact wired in with those
above and below it. Reading the state of the switches can only happen
a row at a time: a single row (output) pin is brought low, and all the
column inputs are read. Any of them that read low are recorded as a
keypress. Low voltage is used to for pressed keys because each input
pin has a built-in pullup resistor.

However, because of the electrical properties of switches, it's
necessary to go through a
[debouncing](https://en.wikipedia.org/wiki/Switch#Contact_bounce)
process as the switches settle. This means taking a few scans over the
matrix and waiting until you get N successive reads of the same state
before counting any single keypress or release as legitimate.

## TODO

* Improve debouncing
* Support layer toggle bindings
* Double-duty keys (modifiers when held, insertions on press/release)
* SVG output of layouts?

## License

Copyright © 2014 Phil Hagelberg

Released under the [GNU GPL version 3](https://www.gnu.org/licenses/gpl.html).
