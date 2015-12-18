#include "util.h"
#include "io.h" 
#include "mailbox.h"
#include "fb.h"
#include "uart.h"

#define FB_INVALID_WIDTH -1
#define FB_INVALID_HEIGHT -2

void initialize_fb_struct(volatile pi_framebuffer *fb, unsigned int width, unsigned int height, unsigned int depth) 
{	
	fb->width = width;
	fb->height = height;
	fb->virtual_width = fb->width;
	fb->virtual_height = fb->height;
	fb->pitch = 0;
	fb->depth = depth;
	fb->x_offset = 0;
	fb->y_offset = 0;
	fb->pointer = 0;
	fb->size = 0;
}

unsigned int fb_get_pixel_address(pi_framebuffer* fb, unsigned int x, unsigned y) 
{	
	unsigned int pixel_size = fb->depth / 8;
	unsigned int row_offset = fb->width * y;
	
	return physical_address((void *)fb->pointer) + ((row_offset + x) * pixel_size);
}

int fb_set_pixel(pi_framebuffer* fb, unsigned int x, unsigned int y, unsigned int pixel) 
{
	if(x > fb->width) 
	{
		return FB_INVALID_WIDTH;	
	}
	
	if(y > fb->height) 
	{
		return FB_INVALID_HEIGHT;	
	}
	
	unsigned int pixel_address = fb_get_pixel_address(fb, x, y);
	
	mmio_write(pixel_address, pixel);
	
	return 0;
}

void fb_venezuela_flag(pi_framebuffer* fb)
{
	for(int x = 0; x < fb->width; x++) 
	{
		for(int y = 0; y < fb->height; y++) {
			if(y < 252) 
			{
				fb_set_pixel(fb, x, y, 0xFFFF00);
			}
			else if((y > 252) && (y < 504))
			{
				fb_set_pixel(fb, x, y, 0x0000FF);
			}
			else 
			{
				fb_set_pixel(fb, x, y, 0xFF0000);
			}
		}
	}
}

void fb_test_gradient(pi_framebuffer* fb, unsigned int steps) 
{
   uart_puts("[fb_test_gradient]:: Displaying test gradient.\n\r");
   unsigned int counter = 0;
   unsigned int red_diff = 255;
   unsigned int green_diff = 255;
   unsigned int blue_diff = 255;

   unsigned int red_step = red_diff / steps;
   unsigned int green_step = green_diff / steps;
   unsigned int blue_step = blue_diff / steps;

   unsigned int current_red = 0;
   unsigned int current_green = 0;
   unsigned int current_blue = 0;

	do
	{
		counter = 0;
		while(counter < (fb->height / steps))
		{
			for(int y = 0; y < fb->width; y++)
			{
				fb_set_pixel(fb, counter, y, (0xFF0000 & current_red) | (0x00FF00 & current_green) | (0x0000FF & current_blue));
			}
			
			counter++;
		}
		
		current_red += red_step;
		current_green += green_step;
		current_blue += blue_step;
	}
	while ((current_red != 255) && (current_green != 255) && (current_blue != 255));
}

void init_fb() 
{
	dmb();
	
	unsigned int mailbox_message;
	pi_framebuffer *fb = (pi_framebuffer *) FRAMEBUFFER_ADDRESS;
	
	
	uart_puts("[init_fb]:: Framebuffer struct address: ");
	uart_puth(FRAMEBUFFER_ADDRESS);
	uart_puts(" \n\r");
	
	initialize_fb_struct(fb, 1024, 768, 32);
	
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
	
	uart_puts("[init_fb]:: Framebuffer bus address: ");
	uart_puth(fb->pointer);
	uart_puts(" \n\r");
	
	unsigned int fb_physical_address = physical_address((void *)fb->pointer);
	
	uart_puts("[init_fb]:: Framebuffer physical address: ");
	uart_puth(fb_physical_address);
	uart_puts(" \n\r");
	
	uart_puts("[init_fb]:: Framebuffer pitch: ");
	uart_puth(fb->pitch);
	uart_puts(" \n\r");
	
	uart_puts("[init_fb]:: Framebuffer size: ");
	uart_puth(fb->size);
	uart_puts(" \n\r");
	
	fb_venezuela_flag(fb);
	
	
	//fb_test_gradient(fb, 80);
	//fb_blank_screen(fb);
}