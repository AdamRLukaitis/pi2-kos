void mmio_write(unsigned int reg, unsigned int data)
{
	*(volatile unsigned int *)reg = data;
}
 
unsigned int mmio_read(unsigned int reg)
{
	return *(volatile unsigned int *)reg;
}

unsigned int bus_address(void *address)
{
	return ((unsigned int)address) + 0xC0000000;
}
