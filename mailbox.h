#ifndef MAILBOX_H_INCLUDED
#define MAILBOX_H_INCLUDED

#include "io.h"

enum MAIL0
{
	// The base address for Mailbox
    MAIL0_BASE = (GPIO_BASE + 0xB880),
 
    // The offsets for reach register for mailbox.
	MAIL0_READ = (MAIL0_BASE + 0x00),
	MAIL0_PEAK = (MAIL0_BASE + 0x10),
	MAIL0_SENDER = (MAIL0_BASE + 0x14),
	MAIL0_STATUS = (MAIL0_BASE + 0x18),
	MAIL0_CONFIG = (MAIL0_BASE + 0x1C),
	MAIL0_WRITE = (MAIL0_BASE + 0x20)
};

typedef enum 
{
	MAIL_STATUS_EMPTY = 0x40000000,
	MAIL_STATUS_FULL = 0x80000000	
}
MAIL_STATUS;

unsigned int mailbox_read(unsigned char channel);
void mailbox_write(unsigned char channel, unsigned int value);

#endif