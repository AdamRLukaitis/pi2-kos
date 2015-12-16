#include "util.h"
#include "uart.h"

#define HELLO_WORLD_MESSAGE "Hello World\r\n"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{
	(void) r0;
	(void) r1;
	(void) atags;
 
	uart_init();
	uart_puts(HELLO_WORLD_MESSAGE);
 
	while ( TRUE )
		uart_putc(uart_getc());
}