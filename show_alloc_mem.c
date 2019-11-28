#include "malloc.h"

// unsigned int    ft_strlen(char *str)
// {
//     return (*str ? 1 + ft_strlen(++str) : 0);
// }

// void    ft_putstr(char *str)
// {
//     write(1, str, ft_strlen(str));
// }

size_t  show_pages(t_type type)
{
    t_page  *page;
    t_alloc *alloc;
    size_t  ttl;

    if (!g_page[type])
        ft_putstr("\tNo allocation\n");
    page = g_page[type];
    while (page)
    {
        printf("\t%p\n", page->alloc->data_addr);
        alloc = page->alloc;
        while (alloc)
        {
            if (alloc->status == ALLOCATED)
            {
                printf("%p - %p : %lu octets\n", alloc->data_addr, alloc->data_addr + alloc->size, alloc->size);
                ttl += alloc->size;
            }
            alloc = alloc->next;
        }
        page = page->next;
    }
    return (ttl);
}

void    show_alloc_mem()
{
    size_t  ttl;

    ttl = 0;
    if (!g_page[TINY] && !g_page[SMALL] && !g_page[LARGE])
        ft_putstr("No allocations\n");
    else
    {
        ft_putstr("TINY : \r");
        ttl += show_pages(TINY);
        ft_putstr("SMALL : \r");
        ttl += show_pages(SMALL);
        ft_putstr("LARGE : \r");
        ttl += show_pages(LARGE);
    }
    printf("Total : %lu octets\n", ttl);
}