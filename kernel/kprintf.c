/* Clear the screen and initialize VIDEO, XPOS and YPOS. */

#include <stdint.h>

#include "fbprint.h"
#include "vga.h"     
/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal. */
void	itoa (char *buf, int32_t base, int32_t d)
{
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
  
  /* If %d is specified and D is minus, put `-' in the head. */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;
     
  /* Divide UD by DIVISOR until UD == 0. */
  do
    {
      int remainder = ud % divisor;
     
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);
     
  /* Terminate BUF. */
  *p = 0;
     
  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}
     
/* Put the character C on the screen. */

/* Format a string and print it on the screen, just like the libc
   function printf. */
void kprintf (const char *format, ...)
{
  char **arg = (char **) &format;
  int c;
  char buf[20];
     
  arg++;
     
  while ((c = *format++) != 0)
    {
      if (c != '%')
	putchar (c);
      else
	{
	  char *p;
     
	  c = *format++;
	  switch (c)
	    {
	    case 'd':
	    case 'u':
	    case 'x':
	      itoa (buf, c, *((int *) arg++));
	      p = buf;
	      goto string;
	      break;
     
	    case 's':
	      p = *arg++;
	      if (! p)
		p = "(null)";
     
	    string:
	      while (*p)
		putchar(*p++);
	      break;
     
	    default:
	      putchar(*((int *) arg++));
	      break;
	    }
	}
    }
}

