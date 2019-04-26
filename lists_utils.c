#include "malloc.h"

int     count_pages(t_type type)
{
    int     i;
    t_page  *curr;

    i = 0;
    if (type == LARGE)
        return (i);
    curr = g_page;
    while (curr)
    {
        if (curr->type == type)
            ++i;
        curr = curr->next;
    }
    return (i);
}

int count_allocs(t_alloc *alloc)
{
    return (alloc ? 1 + count_allocs(alloc->next) : 0);
}