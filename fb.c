#include "util.h"
#include "io.h" 
#include "mailbox.h"
#include "fb.h"
#include "uart.h"

void initialize_fb_struct(volatile pi_framebuffer *fb) 
{	
	fb->width = 640;
	fb->height = 480;
	fb->virtual_width = fb->width;
	fb->virtual_height = fb->height;
	fb->pitch = 0;
	fb->depth = 24;
	fb->x_offset = 0;
	fb->y_offset = 0;
	fb->pointer = 0;
	fb->size = 0;
}

void init_fb() 
{
	dmb();
	
	volatile unsigned int mailbox_message;
	volatile pi_framebuffer *fb = (pi_framebuffer *) FRAMEBUFFER_ADDRESS;
	
	
	uart_puts("[init_fb]:: Framebuffer struct address: ");
	uart_puth(FRAMEBUFFER_ADDRESS);
	uart_puts(" \n\r");
	
	initialize_fb_struct(fb);
	
	dmb();
	uart_puts("[init_fb]:: Writing to mailbox\n\r");
	mailbox_write(FRAMEBUFFER_MAILBOX_CHANNEL, bus_address((void *)FRAMEBUFFER_ADDRESS));
	delay(150);
	uart_puts("[init_fb]:: Waiting for mailbox response\n\r");
	

	mailbox_message = mailbox_read(FRAMEBUFFER_MAILBOX_CHANNEL);
	dmb();
	uart_puts("[init_fb]:: ..\n\r");
	dmb();
	
	if(mailbox_message) 
	{
		uart_puts("[init_fb]:: Error obtaining framebuffer. mailbox_message != 0 \n\r");
		return;
	}
	
	if(!fb->pointer) 
	{
		uart_puts("[init_fb]:: Error obtaining framebuffer. no fb pointer \n\r");
		return;
	}
	
	uart_puts("[init_fb]:: Framebuffer address: ");
	uart_puth(fb->pointer);
	uart_puts(" \n\r");
	
	/*
	uart_puts("[init_fb]:: Sending data to framebuffer");
	for(int i = 0; i < (fb->width * fb->height); i++) 
	{
		mmio_write((fb->pointer + i), 0x00FFFFFF);
	}*/
}