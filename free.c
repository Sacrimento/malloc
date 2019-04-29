#include "malloc.h"

void    ft_free(void *ptr)
{
    t_page  *page;

    if (!(ptr))
        return ;
    if (!(page = free_ptr(ptr)))
        return ;
    // debug_allocs(page);
    align_allocations(page); // MOVES FREED BLOCKS TO THE LEFT
    // debug_allocs(page);
    if (!(allocs_defragmentation(page))) //MERGES FREED ALLOCS
        return ;
    // debug_allocs(page);
    debug_pages();
    remove_empty_page(page);
    debug_pages();
}

void    align_allocations(t_page *page)
{
    t_alloc *curr;
    t_alloc *cnext;
    
    curr = page->alloc;
    while (curr)
    {
        cnext = curr->next;
        if (cnext && cnext->status == FREE)
        {
            curr->next = cnext->next;
            cnext->next = page->alloc;
            page->alloc = cnext;
        }
        else
            curr = curr->next;
    }
}

t_page  *free_ptr(void *ptr)
{
    t_page  *curr_page;
    t_alloc *curr_alloc;
    int     i;

    i = -1;
    while (++i < 3)
    {
        curr_page = g_page[i];
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
            curr->data_addr = curr->data_addr > curr->next->data_addr ? curr->next->data_addr : curr->data_addr;
            munmap(curr->next, sizeof(t_alloc));
            curr->next = tmp_next;
        }
        curr = curr->next;
    }
    return (1);
}

// void    search_and_destroy(t_type type) // TO TEST
// {
//     t_page  *curr;
//     t_page  *tmp_next;
//     int     type_count;

//     curr = g_page;
//     type_count = count_pages(type);
//     while (curr->next)
//     {
//         if (curr->next->type == type && (type_count > 1 || type == LARGE) && count_allocs(curr->next->alloc) == 1 && curr->next->alloc->status == FREE)
//         {
//             tmp_next = curr->next->next;
//             if ((munmap(curr->next->alloc->data_addr, curr->next->alloc->size) == -1)
//                 || (munmap(curr->next->alloc, sizeof(t_alloc)) == -1)
//                 || (munmap(curr->next, sizeof(t_page)) == -1))
//                 return; // TODO DO SMTH
//             curr->next = tmp_next;
//             printf("freed one page\n");
//             return ;
//         }
//         curr = curr->next;
//     }
// }

void    remove_empty_page(t_page *page)
{
    t_page  *curr;

    if (count_allocs(page->alloc) > 1 || !is_page_removable(page))
        return ;
    if (page == g_page[page->type])
        g_page[page->type] = page->next;
    curr = g_page[page->type];
    while (curr && curr->next)
    {
        if (curr->next == page)
            curr->next = curr->next->next;
        curr = curr->next;
    }
    munmap(curr->alloc->data_addr, curr->alloc->size);
    munmap(page->alloc, sizeof(t_alloc));
    munmap(page, sizeof(t_page));
}