#include "malloc.h"

void    debug_allocs(t_page *page)
{
    t_alloc *alloc;

    printf("\n\n");
    alloc = page->alloc;
    while(alloc)
    {
        printf("%s %lu\n", alloc->status ? "ALLOCATED" : "FREED", alloc->size);
        alloc = alloc->next;
    }
}