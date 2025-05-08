PREFIX ?= riscv-none-elf
OBJCOPY = $(PREFIX)-objcopy
CC = $(PREFIX)-gcc
SIZE = $(PREFIX)-size
READELF = $(PREFIX)-readelf
OBJDUMP = $(PREFIX)-objdump
NM = $(PREFIX)-nm

# -march=rv32imac_zicsr_zifencei_zba_zbb_zbkb_zbs_zcmp
CFLAGS = -Wall -Os -ggdb3 -mabi=ilp32 -march=rv32i_zicsr -ffunction-sections
LDFLAGS = --specs=nano.specs -Wl,--gc-sections -Wl,-Map,$(TARGET).map -Wl,-T../ld/spram.ld
# -nostdlib -ffreestanding
FLAGS = $(CFLAGS) $(LDFLAGS)

all: $(TARGET).elf

$(TARGET).elf: $(SRC)
	$(CC) $(FLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $^ $@

clean:
	$(RM) *.elf
	$(RM) *.bin
	$(RM) *.map

bin: $(TARGET).bin

size: $(TARGET).elf
	$(SIZE) --format=SysV $^

readelf: $(TARGET).elf
	$(READELF) $^ -a

objdump: $(TARGET).elf
	$(OBJDUMP) -D > $(TARGET).dmp $^

nm: $(TARGET).elf
	$(NM) $^
