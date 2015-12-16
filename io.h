#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#define GPIO_BASE 0x3F000000

#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

void mmio_write(unsigned int reg, unsigned int data);
unsigned int mmio_read(unsigned int reg);

#endif