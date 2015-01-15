#include <stddef.h>
#include <stdint.h>

#include "strops.h"

size_t strlen(const char* str)
{
  size_t i;
  i = 0;
  while (str[i] > 0)
    i++;
  return (i);
}
