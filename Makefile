MCU=atmega32u4

F_CPU=16000000

TARGET=atreus

LAYOUT ?= qwerty

layout: layout.h

layout.h: atreus.el $(LAYOUT).json
	emacs --batch -l dash.el -l atreus.el --eval "(atreus-make-layout \"$(LAYOUT).json\")"

build: layout
	avr-gcc -std=gnu99 -Os -D F_CPU=$(F_CPU)UL -mmcu=$(MCU) -c -o $(TARGET).o $(TARGET).c
	avr-gcc -std=gnu99 -Os -D F_CPU=$(F_CPU)UL -mmcu=$(MCU) -c -o usb_keyboard.o usb_keyboard.c
	avr-gcc -mmcu=$(MCU) usb_keyboard.o $(TARGET).o -o $(TARGET)
	avr-size $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

upload: build
	teensy_loader_cli -w -mmcu=$(MCU) $(TARGET).hex
