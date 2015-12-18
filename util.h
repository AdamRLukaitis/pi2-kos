#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#define TRUE 1
#define FALSE 0

#define HAS_FLAG(d, b) ((d & b) == b)

extern void noop ( unsigned int );
void delay(unsigned int count);

#endif