#ifndef FB_H_INCLUDED
#define FB_H_INCLUDED

#define FRAMEBUFFER_MAILBOX_CHANNEL 1
#define FRAMEBUFFER_ADDRESS (1 << 22)

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

void init_fb();

#endif