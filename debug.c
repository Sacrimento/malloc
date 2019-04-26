#include "malloc.h"

void    debug_allocs(t_page *page)
{
    t_alloc *alloc;

    printf("\n");
    alloc = page->alloc;
    while(alloc)
    {
        printf("%s %lu\n", alloc->status ? "ALLOCATED" : "FREED", alloc->size);
        alloc = alloc->next;
    }
}

void    debug_pages(void)
{
    t_page  *page;

    for (int i = 0; i < 3; i++)
    {
        page = g_page[i];
        printf("%d\n", i);
        while (page)
        {
            printf("%lu %d\n", page->size, count_allocs(page->alloc));
            page = page->next;
        }
    }
}