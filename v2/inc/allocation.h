#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "malloc.h"

void    *first_fit(size_t size, t_page *priority_page);
void    *split_allocation(void *alloc_ptr, size_t size);
size_t  align(size_t val, size_t alignement);

#endif