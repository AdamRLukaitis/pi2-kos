BUILDDIR := build
TOOLCHAIN :=../toolchain/
TOOLCHAIN_BIN := $(TOOLCHAIN)bin/
CC :=$(TOOLCHAIN_BIN)arm-none-eabi-gcc
#TOOLCHAIN_LIB_GCC := $(dir $(shell $(CC) -print-libgcc-file-name))
TOOLCHAIN_LIB_GCC := /Users/Kellerman/Develop/toolchain/lib/gcc/arm-none-eabi/4.9.3
LINKER :=$(TOOLCHAIN_BIN)arm-none-eabi-ld
OBJCOPY :=$(TOOLCHAIN_BIN)arm-none-eabi-objcopy
CFLAGS := -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -fpic -mtune=cortex-a7 -ffreestanding -std=gnu99 -c
LDFLAGS := -L $(TOOLCHAIN_LIB_GCC) -lgcc
SOURCES_ASM := $(wildcard *.S)
SOURCES_C   := $(wildcard *.c)
HEADERS_C   := $(wildcard *.h)
SOURCES :=$(SOURCES_ASM)
SOURCES +=$(SOURCES_C)

OBJ_FILES   := $(patsubst %.S,%.o,$(SOURCES_ASM))
OBJ_FILES   += $(patsubst %.c,%.o,$(SOURCES_C))
OBJS        := $(addprefix $(BUILDDIR)/, $(OBJ_FILES))

.PHONY: clean

all: $(BUILDDIR)/kernel.img
	
$(BUILDDIR)/kernel.elf: $(OBJS) linker.ld
	$(LINKER) $(LDFLAGS) -Tlinker.ld -o $@ $(OBJS) $(shell $(CC) -print-libgcc-file-name)
		
$(BUILDDIR)/kernel.img: $(BUILDDIR)/kernel.elf
	$(OBJCOPY) $(BUILDDIR)/kernel.elf -O binary $@

$(BUILDDIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.o: %.S Makefile
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -Rvf $(BUILDDIR)