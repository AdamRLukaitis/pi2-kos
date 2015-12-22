#include "util.h"
#include "uart.h"
#include "fb.h"
#include "console.h"
#define UART_DEBUG
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
 	delay(150);
 
 	uart_puts("Framebuffer initialization\n\r");
	init_fb();
	uart_puts("Framebuffer initialization complete\n\r");	
 	delay(150);
	 
    unsigned int columns = 0;
    unsigned int rows = 0;
    unsigned char uchar = 0; 
     
	while ( TRUE ) 
    {   
	    uchar = uart_getc();
    	
        uart_putc(uchar);
        
        draw_char_fb(uchar, rows, columns++);
        
        if(columns > (1024/8))
        {
            rows++;
            columns = 0;
        }
    }
}
