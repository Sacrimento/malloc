#include "malloc.h"

void    debug_allocs(t_page *page)
{
    t_alloc *alloc;

    // ft_putstr("\n");
    alloc = page->alloc;
    while(alloc)
    {
        // ft_putstr("%s %lu\n", alloc->status ? "ALLOCATED" : "FREED", alloc->size);
        alloc = alloc->next;
    }
}

void    debug_pages(void)
{
    t_page  *page;

    for (int i = 0; i < 3; i++)
    {
        page = g_page[i];
        // ft_putstr("%d\n", i);
        while (page)
        {
            // ft_putstr("%lu %d\n", page->size, count_allocs(page->alloc));
            page = page->next;
        }
    }
}