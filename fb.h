#ifndef FB_H_INCLUDED
#define FB_H_INCLUDED

#define FRAMEBUFFER_MAILBOX_CHANNEL 1
#define FRAMEBUFFER_ADDRESS (1 << 22)

#define FB_INVALID_WIDTH -1
#define FB_INVALID_HEIGHT -2
#define FB_INVALID_REGION_WIDTH -1
#define FB_INVALID_REGION_HEIGHT -2

typedef struct {
   unsigned int width;
   unsigned int height;
   unsigned int virtual_width;
   unsigned int virtual_height;
   unsigned int pitch;
   unsigned int depth;
   unsigned int x_offset;
   unsigned int y_offset;
   unsigned int pointer;
   unsigned int size;
} 
pi_framebuffer;

typedef struct 
{
    unsigned int x;
    unsigned int y;
    unsigned int height;
    unsigned int width;    
}
pi_framebuffer_region;

void init_fb();
int fb_set_pixel(pi_framebuffer* fb, unsigned int x, unsigned int y, unsigned int pixel);
int fb_set_pixel_region(pi_framebuffer* fb, pi_framebuffer_region *region, unsigned int region_x, unsigned int region_y, unsigned int pixel);
#endif