/**
 * liblc/shift.c
 *
 * Copyright (c) Manfred Touron 2008
 */

#include <stdarg.h>

#include "core.h"

void	*lc_shift(lc lc)
{
  void	*ptr;

  ptr = lc->root->ptr;
  lc_remove(lc, lc->root);
  return (ptr);
}
