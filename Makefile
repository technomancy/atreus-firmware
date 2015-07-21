MCU=atmega32u4

F_CPU=16000000

TARGET=atreus

SWAPCOLUMNS=no
# set to allow for flipping the PCB

LAYOUT ?= qwerty
ifneq ($(LAYOUT), qwerty)
LAYOUT_DEPENDS=jsonlayout
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  USB ?= /dev/tty.usbmodem1411
else
  USB ?= /dev/ttyACM0
endif

# Build your keyboard layout
#
#   make build LAYOUT=softdvorak
build: $(TARGET).hex

# Upload your keyboard layout to your keyboard.  You will need to reset your
# keyboard for the upload to complete
#
#   make upload LAYOUT=softdvorak
upload: $(TARGET).hex
	while [ ! -r $(USB) ]; do sleep 1; done; \
	avrdude -p $(MCU) -c avr109 -U flash:w:$(TARGET).hex -P $(USB)

# Build a keyboard layout from a JSON description.
jsonlayout: atreus.el $(LAYOUT).json
	emacs --batch -l dash.el -l atreus.el --eval "(atreus-make-layout \"$(LAYOUT).json\")"
	./atreus-layout-to-svg.sh $(LAYOUT).json

# remove build files
clean:
	-rm -f $(TARGET) $(TARGET).hex *.o

layout.h: $(LAYOUT_DEPENDS)
	-cp -n layout_qwerty.h layout.h

$(TARGET).o: layout.h
usb_keyboard.o: usb_keyboard.h

$(TARGET): $(TARGET).o usb_keyboard.o
	avr-gcc -mmcu=$(MCU) usb_keyboard.o $(TARGET).o -o $(TARGET)

$(TARGET).hex: $(TARGET)
	avr-size $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex

%.o: %.c
ifeq ($(SWAPCOLUMNS),yes)
	avr-gcc -std=gnu99 -DSWAPCOLUMNS=$(SWAPCOLUMNS) -Os -D F_CPU=$(F_CPU)UL -mmcu=$(MCU) -c -o $@ $<
else
	avr-gcc -std=gnu99 -Os -D F_CPU=$(F_CPU)UL -mmcu=$(MCU) -c -o $@ $<
endif

udev:
	cp a-star.rules /etc/udev/rules.d/
