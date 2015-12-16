#include "util.h"

/* Loop <delay> times in a way that the compiler won't optimize away. */
void delay(unsigned int count)
{
	for(int ra=0;ra<count;ra++) noop(ra);
}