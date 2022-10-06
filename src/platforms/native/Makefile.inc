CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS += -Istm32/include -mcpu=cortex-m3 -mthumb \
	-DSTM32F1 -DBLACKMAGIC -I../libopencm3/include \
	-Iplatforms/stm32 -DDFU_SERIAL_LENGTH=9 -Iplatforms/stm32/uf2

LDFLAGS_BOOT := $(LDFLAGS) --specs=nano.specs -lopencm3_stm32f1 \
	-Wl,-T,platforms/stm32/blackmagic.ld -nostartfiles -lc \
	-Wl,-Map=mapfile -mthumb -mcpu=cortex-m3 -Wl,-gc-sections \
	-L../libopencm3/lib
LDFLAGS = $(LDFLAGS_BOOT) -Wl,-Ttext=0x8002000

ifeq ($(ENABLE_DEBUG), 1)
LDFLAGS += --specs=rdimon.specs
else
LDFLAGS += --specs=nosys.specs
endif

VPATH += platforms/stm32
VPATH += platforms/stm32/uf2

SRC +=               \
	traceswodecode.c \
	traceswo.c	\
	serialno.c	\
	timing.c	\
	timing_stm32.c	\

all:	blackmagic.bin blackmagic_dfu.bin blackmagic_dfu.hex blackmagic_uf2.bin blackmagic_uf2.hex

blackmagic_dfu.elf: usbdfu.o dfucore.o dfu_f1.o serialno.o
	@echo "  LD      $@"
	$(Q)$(CC) $^ -o $@ $(LDFLAGS_BOOT)

blackmagic_uf2.elf: usbuf2.o dapboot.o dmesg.o dummy.o ghostfat.o usb_conf.o usb_msc.o webusb.o winusb.o
	@echo "  LD      $@"
	$(Q)$(CC) $^ -o $@ $(LDFLAGS_BOOT)

host_clean:
	-$(Q)$(RM) blackmagic.bin blackmagic_dfu blackmagic_dfu.bin blackmagic_dfu.hex blackmagic_uf2 blackmagic_uf2.bin blackmagic_uf2.hex
