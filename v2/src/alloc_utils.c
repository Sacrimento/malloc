#include "allocation.h"

static void     *get_begin(void *alloc)
{
    while (((t_header*)alloc)->prev_size)
        alloc -= ((t_header*)alloc)->prev_size;
    return alloc;
}

t_page          *get_page_from_alloc(void *alloc)
{
    int     i;
    t_page  *curr_page;

    i = 0;
    alloc = get_begin(alloc);
    while (i < 3)
    {
        curr_page = g_page[i];
        while (curr_page)
        {
            if (curr_page->alloc == alloc)
                return (curr_page);
            curr_page = curr_page->next;
        }
        i++;
    }
    return (NULL);
}

int     is_page_free(void *alloc)
{
    while (((t_header*)alloc)->size)
    {
        if (!((t_header*)alloc)->free)
            return (0);
        alloc += ((t_header*)alloc)->size;
    }
    return (1);
}