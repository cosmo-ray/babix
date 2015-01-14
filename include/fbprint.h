#ifndef  __FBPRINT_H__
# define __FBPRINT_H__

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/* Some screen stuff. */
/* The number of columns. */
#define COLUMNS                 80
/* The number of lines. */
#define LINES                   24
/* The attribute of an character. */
#define ATTRIBUTE               7
/* The video memory address. */
#define VIDEO                   0xB8000

void	itoa (char *buf, int32_t base, int32_t d);
void    cls (void);
void	putchar (int32_t c);
void	kprintf (const char *format, ...);

#endif /* __FBPRINT32_T_H__ */
