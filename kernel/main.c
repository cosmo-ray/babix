#if !defined(__cplusplus)

#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "fbprint.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


/* Hardware text mode color constants. */
enum vga_color
  {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
  };

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
  return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

size_t strlen(const char* str)
{
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
  return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
    }
}

void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if ( ++terminal_column == VGA_WIDTH )
    {
      terminal_column = 0;
      if ( ++terminal_row == VGA_HEIGHT )
	{
	  terminal_row = 0;
	}
    }
}

void terminal_writestring(const char* data)
{
  size_t datalen = strlen(data);
  for ( size_t i = 0; i < datalen; i++ )
    terminal_putchar(data[i]);
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main(unsigned long magic, unsigned long addr)
{

  multiboot_info_t *mbi;

  /* Clear the screen. */
  cls ();

  /* Am I booted by a Multiboot-compliant boot loader? */
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
      kprintf ("Invalid magic number: 0x%x\n", (unsigned) magic);
      return;
    }

  /* Set MBI to the address of the Multiboot information structure. */
  mbi = (multiboot_info_t *) addr;

  /* Print out the flags. */
  kprintf ("flags = 0x%x\n", (unsigned) mbi->flags);

  /* Are mem_* valid? */
  if (CHECK_FLAG (mbi->flags, 0))
    kprintf ("mem_lower = %uKB, mem_upper = %uKB\n",
	    (unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);

  /* Is boot_device valid? */
  if (CHECK_FLAG (mbi->flags, 1))
    kprintf ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);

  /* Is the command line passed? */
  if (CHECK_FLAG (mbi->flags, 2))
    kprintf ("cmdline = %s\n", (char *) mbi->cmdline);

  /* Are mods_* valid? */
  if (CHECK_FLAG (mbi->flags, 3))
    {
      multiboot_module_t *mod;
      unsigned int i;

      kprintf ("mods_count = %d, mods_addr = 0x%x\n",
	      (int) mbi->mods_count, (int) mbi->mods_addr);
      for (i = 0, mod = (multiboot_module_t *) mbi->mods_addr;
	   i < mbi->mods_count;
	   i++, mod++)
	kprintf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",
		(unsigned) mod->mod_start,
		(unsigned) mod->mod_end,
		(char *) mod->cmdline);
    }

  /* Bits 4 and 5 are mutually exclusive! */
  if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
    {
      kprintf ("Both bits 4 and 5 are set.\n");
      return;
    }

  /* Is the symbol table of a.out valid? */
  if (CHECK_FLAG (mbi->flags, 4))
    {
      multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);

      kprintf ("multiboot_aout_symbol_table: tabsize = 0x%0x, "
	      "strsize = 0x%x, addr = 0x%x\n",
	      (unsigned) multiboot_aout_sym->tabsize,
	      (unsigned) multiboot_aout_sym->strsize,
	      (unsigned) multiboot_aout_sym->addr);
    }

  /* Is the section header table of ELF valid? */
  if (CHECK_FLAG (mbi->flags, 5))
    {
      multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);

      kprintf ("multiboot_elf_sec: num = %u, size = 0x%x,"
	      " addr = 0x%x, shndx = 0x%x\n",
	      (unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,
	      (unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
    }

  /* Are mmap_* valid? */
  if (CHECK_FLAG (mbi->flags, 6))
    {
      multiboot_memory_map_t *mmap;

      kprintf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",
	      (unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
      for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
	   (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
	   mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
					      + mmap->size + sizeof (mmap->size)))
	kprintf (" size = 0x%x, base_addr = 0x%x%x,"
		" length = 0x%x%x, type = 0x%x\n",
		(unsigned) mmap->size,
		mmap->addr >> 32,
		mmap->addr & 0xffffffff,
		mmap->len >> 32,
		mmap->len & 0xffffffff,
		(unsigned) mmap->type);
    }
  
  //  (void)s;
  //(void)z;

  //  terminal_initialize();
  /* Since there is no support for newlines in terminal_putchar yet, \n will
     produce some VGA specific character instead. This is normal. */
  //terminal_writestring("Hello, kernel World!\n");
}
