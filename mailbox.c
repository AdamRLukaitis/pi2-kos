#include "util.h"
#include "io.h"
#include "mailbox.h"
#include "uart.h" 

unsigned int mailbox_read(unsigned char channel) 
{	
	volatile unsigned int status;
	
	for(;;) {
		
		
		while(((status = mmio_read(MAIL0_STATUS)) & MAIL_STATUS_EMPTY)); 
	
		unsigned int data = mmio_read(MAIL0_READ);	
		unsigned char _channel = data & 0xF;
		
		
		uart_puts("[mailbox_read]:: From: ");
		uart_puth(MAIL0_READ);
		uart_puts(" message: \n\r");
		uart_puts("\tdata: ");
		uart_puth(data);
		uart_puts("\n\r\tchannel: ");
		uart_puth(_channel);
		
		
		data >>= 4;
		
		
		uart_puts("\n\r\tmdata: ");
		uart_puth(data);
		uart_puts("\n\r");
		
		
		if(channel == _channel) 
		{
			return data;
		}
	}
}

void mailbox_write(unsigned char channel, unsigned int value) 
{
	value &= 0xFFFFFFF0;
	
	while((mmio_read(MAIL0_STATUS) & MAIL_STATUS_FULL));
	
	
	uart_puts("[mailbox_write]:: To: ");
	uart_puth(MAIL0_WRITE);
	uart_puts(" message: \n\r");
	uart_puts("\tdata: ");
	uart_puth(value);
	uart_puts("\n\r\tchannel: ");
	uart_puth(channel);
	uart_puts("\n\r");
	
	
	mmio_write(MAIL0_WRITE, channel | value);	
}