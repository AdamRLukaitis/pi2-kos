#include "util.h"
#include "io.h"
#include "fb.h"
#include "console.h"
#include "memory.h"
#include "uart.h"

typedef struct {
    unsigned int rows;
    unsigned int columns;
    unsigned int current_row;
    unsigned int current_column;
    unsigned int offset_x;
    unsigned int offset_y;
    char *buffer;
    void (*console_writer[2])(void *cs);
}
console;

unsigned long long latin_font_8x8[128] = {
	0x0000000000000000ULL, /* NUL */
	0x0000000000000000ULL, /* SOH */
	0x0000000000000000ULL, /* STX */
	0x0000000000000000ULL, /* ETX */
	0x0000000000000000ULL, /* EOT */
	0x0000000000000000ULL, /* ENQ */
	0x0000000000000000ULL, /* ACK */
	0x0000000000000000ULL, /* BEL */
	0x0000000000000000ULL, /* BS */
	0x0000000000000000ULL, /* TAB */
	0x0000000000000000ULL, /* LF */
	0x0000000000000000ULL, /* VT */
	0x0000000000000000ULL, /* FF */
	0x0000000000000000ULL, /* CR */
	0x0000000000000000ULL, /* SO */
	0x0000000000000000ULL, /* SI */
	0x0000000000000000ULL, /* DLE */
	0x0000000000000000ULL, /* DC1 */
	0x0000000000000000ULL, /* DC2 */
	0x0000000000000000ULL, /* DC3 */
	0x0000000000000000ULL, /* DC4 */
	0x0000000000000000ULL, /* NAK */
	0x0000000000000000ULL, /* SYN */
	0x0000000000000000ULL, /* ETB */
	0x0000000000000000ULL, /* CAN */
	0x0000000000000000ULL, /* EM */
	0x0000000000000000ULL, /* SUB */
	0x0000000000000000ULL, /* ESC */
	0x0000000000000000ULL, /* FS */
	0x0000000000000000ULL, /* GS */
	0x0000000000000000ULL, /* RS */
	0x0000000000000000ULL, /* US */
	0x0000000000000000ULL, /* SPACE */
	0x183C3C1818001800ULL, /* ! */
	0x6C6C000000000000ULL, /* " */
	0x6C6CFE6CFE6C6C00ULL, /* # */
	0x307CC0780CF83000ULL, /* $ */
	0x00C6CC183066C600ULL, /* % */
	0x386C3876DCCC7600ULL, /* & */
	0x6060C00000000000ULL, /* ' */
	0x1830606060301800ULL, /* ( */
	0x6030181818306000ULL, /* ) */
	0x00663CFF3C660000ULL, /* * */
	0x003030FC30300000ULL, /* + */
	0x0000000000303060ULL, /* , */
	0x000000FC00000000ULL, /* - */
	0x0000000000303000ULL, /* . */
	0x060C183060C08000ULL, /* / */
	0x7CC6CEDEF6E67C00ULL, /* 0 */
	0x307030303030FC00ULL, /* 1 */
	0x78CC0C3860CCFC00ULL, /* 2 */
	0x78CC0C380CCC7800ULL, /* 3 */
	0x1C3C6CCCFE0C1E00ULL, /* 4 */
	0xFCC0F80C0CCC7800ULL, /* 5 */
	0x3860C0F8CCCC7800ULL, /* 6 */
	0xFCCC0C1830303000ULL, /* 7 */
	0x78CCCC78CCCC7800ULL, /* 8 */
	0x78CCCC7C0C187000ULL, /* 9 */
	0x0030300000303000ULL, /* : */
	0x0030300000303060ULL, /* ; */
	0x183060C060301800ULL, /* < */
	0x0000FC0000FC0000ULL, /* = */
	0x6030180C18306000ULL, /* > */
	0x78CC0C1830003000ULL, /* ? */
	0x7CC6DEDEDEC07800ULL, /* @ */
	0x3078CCCCFCCCCC00ULL, /* A */
	0xFC66667C6666FC00ULL, /* B */
	0x3C66C0C0C0663C00ULL, /* C */
	0xF86C6666666CF800ULL, /* D */
	0xFE6268786862FE00ULL, /* E */
	0xFE6268786860F000ULL, /* F */
	0x3C66C0C0CE663E00ULL, /* G */
	0xCCCCCCFCCCCCCC00ULL, /* H */
	0x7830303030307800ULL, /* I */
	0x1E0C0C0CCCCC7800ULL, /* J */
	0xE6666C786C66E600ULL, /* K */
	0xF06060606266FE00ULL, /* L */
	0xC6EEFEFED6C6C600ULL, /* M */
	0xC6E6F6DECEC6C600ULL, /* N */
	0x386CC6C6C66C3800ULL, /* O */
	0xFC66667C6060F000ULL, /* P */
	0x78CCCCCCDC781C00ULL, /* Q */
	0xFC66667C6C66E600ULL, /* R */
	0x78CCE0701CCC7800ULL, /* S */
	0xFCB4303030307800ULL, /* T */
	0xCCCCCCCCCCCCFC00ULL, /* U */
	0xCCCCCCCCCC783000ULL, /* V */
	0xC6C6C6D6FEEEC600ULL, /* W */
	0xC6C66C38386CC600ULL, /* X */
	0xCCCCCC7830307800ULL, /* Y */
	0xFEC68C183266FE00ULL, /* Z */
	0x7860606060607800ULL, /* [ */
	0xC06030180C060200ULL, /* \ */
	0x7818181818187800ULL, /* ] */
	0x10386CC600000000ULL, /* ^ */
	0x00000000000000FFULL, /* _ */
	0x3030180000000000ULL, /* ` */
	0x0000780C7CCC7600ULL, /* a */
	0xE060607C6666DC00ULL, /* b */
	0x000078CCC0CC7800ULL, /* c */
	0x1C0C0C7CCCCC7600ULL, /* d */
	0x000078CCFCC07800ULL, /* e */
	0x386C60F06060F000ULL, /* f */
	0x000076CCCC7C0CF8ULL, /* g */
	0xE0606C766666E600ULL, /* h */
	0x3000703030307800ULL, /* i */
	0x0C000C0C0CCCCC78ULL, /* j */
	0xE060666C786CE600ULL, /* k */
	0x7030303030307800ULL, /* l */
	0x0000CCFEFED6C600ULL, /* m */
	0x0000F8CCCCCCCC00ULL, /* n */
	0x000078CCCCCC7800ULL, /* o */
	0x0000DC66667C60F0ULL, /* p */
	0x000076CCCC7C0C1EULL, /* q */
	0x0000DC766660F000ULL, /* r */
	0x00007CC0780CF800ULL, /* s */
	0x10307C3030341800ULL, /* t */
	0x0000CCCCCCCC7600ULL, /* u */
	0x0000CCCCCC783000ULL, /* v */
	0x0000C6D6FEFE6C00ULL, /* w */
	0x0000C66C386CC600ULL, /* x */
	0x0000CCCCCC7C0CF8ULL, /* y */
	0x0000FC983064FC00ULL, /* z */
	0x1C3030E030301C00ULL, /* { */
	0x1818180018181800ULL, /* | */
	0xE030301C3030E000ULL, /* } */
	0x76DC000000000000ULL, /* ~ */
	0x0000000000000000ULL, /* DEL */
};

void draw_char_fb(unsigned char character, unsigned int row, unsigned int column) 
{   
    unsigned int char_width = 8;
    unsigned int char_height = 8;
    
    pi_framebuffer *fb = (pi_framebuffer *) FRAMEBUFFER_ADDRESS;
    pi_framebuffer_region *region = (pi_framebuffer_region *) (1 << 24);
    
    region->x = column * char_width;
    region->y = row * char_height;
    region->width = 8;
    region->height = 8;
    
    unsigned int y = 8;
    unsigned int x = 8;
    
    while(y--) 
    {
        while(x--) 
        {
            fb_set_pixel_region(fb, region, x, y, HAS_FLAG(latin_font_8x8[character], (1ULL << (x + (y * 8)))) ? 0xFFFFFF : 0x000000);
            //uart_puts(HAS_FLAG(latin_font_8x8[character], (1ULL << (x + (y * 8)))) ? "0" : "_");
        }
        
        //uart_puts("\n\r");
        x = 8;
    }
}

/*
void console_init(unsigned int columns, unsigned int rows, unsigned int screen_columns , unsigned int screen_rows) 
{
    if(screen_rows > rows) 
    {
        screen_rows = rows;
    }
    
    if(screen_columns > columns) 
    {
        screen_columns = columns;
    }
    
    console *cs = (console*)CONSOLE_ADDRESS;
    cs->rows = rows;
    cs->columns = columns;
    cs->offset_x = screen_columns;
    cs->offset_y = screen_rows;
    cs->current_row = 0;
    cs->current_column = 0;
    cs->buffer = (char*) CONSOLE_BUFFER_ADDRESS;
    cs->console_writer[0] = NULL;
    cs->console_writer[1] = NULL;
}

void console_moveup()
{
     console *cs = (console*)CONSOLE_ADDRESS;   
     char *buffer = (char*)cs->buffer;
     
     memmove(buffer, buffer+cs->columns, cs->columns);
     
     for(int i = 0; i < cs->columns; i++) 
     {
         mmio_write(buffer+(cs->rows * cs->columns), 0);
         
     }
}

void console_update(){}

void console_putc(unsigned char character) 
{
    console *cs = (console*)CONSOLE_ADDRESS;
    char *buffer = (char*)cs->buffer;
    
    cs->current_column += 1;
    
    if(cs->current_column > (cs->columns - 1)) 
    {
        cs->current_column = 0;
        cs->current_row += 1;
    }
    
    if(cs->current_row > (cs->rows - 1)) 
    {
        cs->current_column = 0;
        cs->current_row -= 1;
        
        console_moveup();
    }
    
    unsigned int cursor_address = cs->current_column + (cs->current_column * cs->columns);
    
    mmio_write((unsigned int)(buffer+cursor_address), character);
    
    console_update();
}
*/
