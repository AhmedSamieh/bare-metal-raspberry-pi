# By Ahmed Samieh
ARMGNU     = arm-none-eabi
SOURCE     = src/
# get object file name from c file name
OBJECTS    = $(patsubst %.c,%.o,$(wildcard $(SOURCE)*.c))
TARGET     = kernel
# arm-none-eabi-gcc --help > gcc.help
GCC_OPTION = -O1 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wall
# arm-none-eabi-ld --help > ld.help
LD_OPTION  = -e main -N -O --relax --gc-sections --verbose

all: $(TARGET).nm $(TARGET).list $(TARGET).img

# NOTE:
#       $@ the left side of the :
#       $^ is the right side of the :
#       $< is the first item in the right side of the :

$(TARGET).img: $(TARGET).elf
	$(ARMGNU)-objcopy $^ -O binary $@

$(TARGET).list: $(TARGET).elf
	$(ARMGNU)-objdump -d $^ > $@

$(TARGET).nm: $(TARGET).elf
	$(ARMGNU)-nm -n $^ > $@

$(TARGET).elf: $(OBJECTS)
	$(ARMGNU)-ld $(LD_OPTION) $^ -Map $(TARGET).map -o $@ > $(TARGET).ld

%.o: %.c
	$(ARMGNU)-gcc $(GCC_OPTION) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET).*

