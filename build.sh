CFLAGS="-O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7"
../toolchain/bin/arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostdlib -c boot.S -o boot.o 
../toolchain/bin/arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostdlib -c test.c -o kernel.o
../toolchain/bin/arm-none-eabi-gcc -O2 -mfpu=vfp -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -ffreestanding -nostdlib -T linker.ld -o kos.elf boot.o kernel.o
