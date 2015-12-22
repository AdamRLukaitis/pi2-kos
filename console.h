#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#define CONSOLE_ADDRESS (1 << 24)
#define CONSOLE_BUFFER_ADDRESS ((1 << 24) + 0x1E)

/*
void console_init(unsigned int columns, unsigned int rows, unsigned int screen_columns , unsigned int screen_rows);
void console_putc(unsigned char byte);
void console_puts(const char* str);
*/

void draw_char_fb(unsigned char character, unsigned int row, unsigned int column);

#endif