BUILDDIR := build

TOOLCHAIN :=../toolchain/bin/
CC :=$(TOOLCHAIN)arm-none-eabi-gcc
LINKER :=$(TOOLCHAIN)arm-none-eabi-ld
OBJCOPY :=$(TOOLCHAIN)arm-none-eabi-objcopy
CFLAGS :=-O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -fpic -mtune=cortex-a7 -ffreestanding -std=gnu99 -c
SOURCES_ASM := $(wildcard *.S)
SOURCES_C   := $(wildcard *.c)
SOURCES :=$(SOURCES_ASM)
SOURCES +=$(SOURCES_C)

OBJ_FILES   := $(patsubst %.S,%.o,$(SOURCES_ASM))
OBJ_FILES   += $(patsubst %.c,%.o,$(SOURCES_C))
OBJS        := $(addprefix $(BUILDDIR)/, $(OBJ_FILES))

all: $(BUILDDIR)/kernel.img
	
$(BUILDDIR)/kernel.elf: $(OBJS) linker.ld
	$(LINKER) -Tlinker.ld -o $@ $(OBJS)
		
$(BUILDDIR)/kernel.img: $(BUILDDIR)/kernel.elf
	$(OBJCOPY) $(BUILDDIR)/kernel.elf -O binary $@

$(BUILDDIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.o: %.S Makefile
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@