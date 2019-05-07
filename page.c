#include "malloc.h"

t_type  get_page_type(size_t size)
{
    size_t  page_size;

    page_size = (size_t)getpagesize();

    if (size <= TINY_MAX)
        return (TINY);
    else if (size <= SMALL_MAX)
        return (SMALL);
    else
        return (LARGE);
}

size_t  get_page_size(t_type type, size_t size)
{
    size_t  page_size;
    size_t  ret;

    page_size = (size_t)getpagesize();

    if (type == TINY)
        return (4 * page_size);
    else if (type == SMALL)
        return (32 * page_size);
    else
    {
        ret = 32 * page_size;
        while (ret < size)
            ret += page_size;
        return (ret);
    }
}

int     is_page_removable(t_page *page)
{
    t_page  *curr;
    size_t  page_size;

    if (page->type == LARGE)
        return (1);
    page_size = (size_t)getpagesize();
    curr = g_page[page->type];
    while (curr)
    {
        if (curr != page && curr->type == page->type)
        {
            // ft_putstr("Hello there\n");
            if (curr->alloc->status == FREE && curr->alloc->size >= (page->type == TINY ? TINY_MAX : SMALL_MAX))
                return (1);
        }
        curr = curr->next;
    }
    // ft_putstr("PAGE NOT REMOVABLE !!\n");
    return (0);
}