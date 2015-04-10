# By Ahmed Samieh
ARMGNU     = arm-none-eabi
SOURCE     = src/
BUILD      = obj/
# get object file name from c file name)
OBJECTS    = $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))
TARGET     = kernel
# arm-none-eabi-gcc --help > gcc.help
GCC_OPTION = -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wall
# arm-none-eabi-ld --help > ld.help
LD_OPTION  = -e main -N -O --relax --gc-sections --verbose

all: $(TARGET).img $(TARGET).list $(TARGET).nm

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

$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	$(ARMGNU)-gcc $(GCC_OPTION) -c $< -o $@

$(BUILD):
	mkdir $@

clean:
	rm -rf $(BUILD) $(TARGET).*

