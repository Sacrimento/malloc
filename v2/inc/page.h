#ifndef PAGE_H
#define PAGE_H

#include "malloc.h"

void    *alloc_new_page(size_t size);
t_type  get_page_type(size_t size);
size_t  get_page_size(size_t size);
void    destroy_page(t_page *page);

#endif