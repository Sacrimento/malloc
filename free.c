#include "malloc.h"

void    ft_free(void *ptr)
{
    t_page  *page;

    if (!(ptr))
        return ;
    if (!(page = free_ptr(ptr)))
        return ;
    allocs_defragmentation(page);
}

t_page  *free_ptr(void *ptr)
{
    t_page  *curr_page;
    t_alloc *curr_alloc;

    if (!(g_page))
        return (NULL);
    curr_page = g_page;
    while (curr_page)
    {
        curr_alloc = curr_page->alloc;
        while (curr_alloc)
        {
            if (curr_alloc->data_addr == ptr)
            {
                curr_alloc->status = FREE;
                printf("%p was freed\n", ptr);
                return curr_page;
            }
            curr_alloc = curr_alloc->next;
        }
        curr_page = curr_page->next;
    }
    return (NULL);
}

void    allocs_defragmentation(t_page *page)
{
    t_alloc *curr;

    curr = page->alloc;
}