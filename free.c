#include "malloc.h"

void    align_allocations(t_page *page);

void    ft_free(void *ptr)
{
    t_page  *page;

    if (!(ptr))
        return ;
    if (!(page = free_ptr(ptr)))
        return ;
    align_allocations(page);
    if (!(allocs_defragmentation(page))) // TO IMPROVE BY MOVING THE DATA LEFT IN MIDDLE IF EXISTS
        return ;
    // search_and_destroy(page->type); // TO REWORK
}

void    align_allocations(t_page *page)
{
    t_alloc *curr;
    t_alloc *tmp;

    curr = page->alloc;
    if (count_allocs(curr) == 1)
        return;
    if (curr->status == FREE)
    {
        page->alloc = curr->next;
        page->alloc->next = curr;
    }
    while (curr->next)
    {
        if (curr->next->status == FREE && curr->next->next)
        {
            tmp = curr->next;
            curr->next = curr->next->next;
            curr->next->next = tmp;
        }
        curr = curr->next;
    }
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

void    search_and_destroy(t_type type) // TO TEST
{
    t_page  *curr;
    t_page  *tmp_next;
    int     type_count;

    curr = g_page;
    type_count = count_pages(type);
    while (curr->next)
    {
        if (curr->next->type == type && (type_count > 1 || type == LARGE) && count_allocs(curr->next->alloc) == 1 && curr->next->alloc->status == FREE)
        {
            tmp_next = curr->next->next;
            munmap(curr->next->alloc->data_addr, curr->next->alloc->size) == -1;
            munmap(curr->next->alloc, sizeof(t_alloc)) == -1;
            munmap(curr->next, sizeof(t_page)) == -1;
            curr->next = tmp_next;
            printf("freed one page\n");
            return ;
        }
        curr = curr->next;
    }
}