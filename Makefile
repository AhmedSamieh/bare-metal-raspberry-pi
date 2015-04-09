# By Ahmed Samieh

ARMGNU  = arm-none-eabi
SOURCE  = src/
BUILD   = obj/
# get object file name from c file name)
OBJECTS = $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))
ELF     = kernel.elf
TARGET  = kernel.img
LIST    = kernel.list
MAP     = kernel.map
OPTION  = -O2 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles

all: $(TARGET) $(LIST)

# NOTE:
#       $@ the left side of the :
#       $^ is the right side of the :
#       $< is the first item in the right side of the :
$(BUILD):
	mkdir $@

$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	$(ARMGNU)-gcc $(OPTION) -c $< -o $@

$(ELF): $(OBJECTS)
	$(ARMGNU)-ld $^ -Map $(MAP) -o $@

$(TARGET): $(ELF)
	$(ARMGNU)-objcopy $^ -O binary $@

$(LIST): $(ELF)
	$(ARMGNU)-objdump -d $^ > $@

clean:
	rm -rf $(BUILD) $(TARGET) $(LIST) $(ELF) $(MAP) $(OBJECTS)

