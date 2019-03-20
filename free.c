#include "malloc.h"

void    ft_free(void *ptr)
{
    t_page  *page;

    if (!(ptr))
        return ;
    if (!(page = free_ptr(ptr)))
        return ;
    if (!(allocs_defragmentation(page)))
        return ;
    search_and_destroy(page->type);
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

int     allocs_defragmentation(t_page *page)
{
    t_alloc *curr;
    t_alloc *tmp_next;

    curr = page->alloc;
    while (curr)
    {
        if (curr->status == FREE && curr->next && curr->next->status == FREE)
        {
            tmp_next = curr->next->next;
            curr->size += curr->next->size;
            if (munmap(curr->next, sizeof(t_alloc)) == -1)
                return (0);
            curr->next = tmp_next;
        }
        curr = curr->next;
    }
    return (1);
}

void    search_and_destroy(t_type type)
{
    t_page  *curr;
    int     type_count;

    curr = g_page;
    type_count = count_pages(type);
    while (curr->next)
    {
        if (curr->type == type && (type_count > 1 || type == LARGE) && count_allocs(curr->alloc) == 1 && curr->alloc->status == FREE)
        {
            printf("YES");
            return ;
        }
        curr = curr->next;
    }
}