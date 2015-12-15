CFLAGS="-O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7"

../toolchain/bin/arm-none-eabi-gcc -march=armv7-a -fpic -ffreestanding -c boot.S -o boot.o 
../toolchain/bin/arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -fpic -mtune=cortex-a7 -ffreestanding -std=gnu99 -c test.c -o kernel.o
../toolchain/bin/arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostdlib -T linker.ld -o kos.elf boot.o kernel.o
../toolchain/bin/arm-none-eabi-objcopy kos.elf -O binary kernel.img