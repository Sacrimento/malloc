#include "malloc.h"

unsigned int    ft_strlen(char *str)
{
    return (*str ? 1 + ft_strlen(++str) : 0);
}

void    ft_putstr(char *str)
{
    write(1, str, ft_strlen(str));
}

unsigned long   show_allocs(t_alloc *alloc)
{
    unsigned long   ttl;

    ttl = 0;
    while (alloc)
    {
        if (alloc->status == ALLOCATED)
        {
            ttl += alloc->size;
            printf("%p - %p : %lu octets\n", alloc->data_addr, alloc->data_addr + alloc->size, alloc->size);
        }
        alloc = alloc->next;
    }
    return (ttl);
}

unsigned long   show_pages(t_type type)
{
    t_page          *page;
    unsigned long   ttl;

    page = g_page[type];
    ttl = 0;
    if (type == TINY)
        ft_putstr("TINY : ");
    else if (type == SMALL)
        ft_putstr("SMALL : ");
    else
        ft_putstr("LARGE : ");
    while (page)
    {
        if (page->type == type && !(count_allocs(page->alloc) == 1 && page->alloc->status == FREE))
        {
            printf("%p\n", page);
            ttl += show_allocs(page->alloc);
        }
        page = page->next;
    }
    return (ttl);
}

void    show_alloc_mem()
{
    unsigned long   ttl;

    ttl = 0;
    if (!(g_page[0])) /////////////////
        ft_putstr("No allocations\n");
    else
    {
        ttl += show_pages(TINY);
        ttl += show_pages(SMALL);
        ttl += show_pages(LARGE);
    }
    ft_putstr("Total : ");
    printf("%lu", ttl);
    ft_putstr(" octets\n");
}