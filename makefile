MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyACM0
PROGRAM = telegrafo

CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall -Wextra
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

all: $(PROGRAM).hex

$(PROGRAM).hex: $(PROGRAM).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(PROGRAM).elf: $(PROGRAM).o
	avr-gcc $(CFLAGS) -o $@ $^

%.o: %.c
	avr-gcc $(CFLAGS) -c -o $@ $<

flash: $(PROGRAM).hex
	$(AVRDUDE) -F -V -c arduino -p $(MCU) -P $(PORT) -b 115200 -U flash:w:$<

clean:
	rm -f *.o *.elf *.hex