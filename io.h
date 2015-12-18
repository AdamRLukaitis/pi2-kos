#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#define BUS_ADDRESS_OFFSET 0xC0000000
#define GPIO_BASE 0x3F000000

#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")

void mmio_write(unsigned int reg, unsigned int data);
unsigned int mmio_read(unsigned int reg);
unsigned int bus_address(void *address);
unsigned int physical_address(void *address);
#endif