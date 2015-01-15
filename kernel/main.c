#if !defined(__cplusplus)

#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "fbprint.h"

#include "vga.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
# error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
# error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


/* Hardware text mode color constants. */


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(unsigned long magic, unsigned long stacktart)
{
  multiboot_info_t *mbi;

  /* Clear the screen. */
   /* Am I booted by a Multiboot-compliant boot loader? */


  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      kprintf ("Invalid magic number: 0x%x\n", (unsigned) magic);
      return;
    }


  initmem(addr);
  
  while (1);
  return;
}
