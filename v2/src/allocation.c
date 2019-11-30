#include "page.h"
#include "allocation.h"

void    *first_fit(size_t size, t_page *priority_page)
{
    t_page  *curr_page;
    void    *p;

    curr_page = (priority_page ? priority_page : g_page[get_page_type(size)]);
    if (!curr_page && get_page_type(size) == LARGE)
        return alloc_new_page(size);
    while (curr_page)
    {
        p = curr_page->alloc;
        while (((t_header*)p)->size)
        {
            if (((t_header*)p)->free && ((t_header*)p)->size - sizeof(t_header) >= size)
                return split_allocation(p, size);
            p += ((t_header*)p)->size;
        }
        curr_page = curr_page->next;
    }
    return alloc_new_page(size);
}

void    *split_allocation(void *alloc_ptr, size_t size)
{
    void    *new_block;
    size_t  new_size;
    size_t  old_size;

    ((t_header*)alloc_ptr)->free = 0;
    if (get_page_size(size) != LARGE)
    {
        new_size = align(sizeof(t_header) + size, ALIGNEMENT);
        old_size = ((t_header*)alloc_ptr)->size;

        ((t_header*)alloc_ptr)->size = new_size;

        new_block = alloc_ptr + ((t_header*)alloc_ptr)->size;
        ((t_header*)new_block)->prev_size = new_size;
        ((t_header*)new_block)->size = old_size - new_size;
        ((t_header*)new_block)->free = 1;
    }

    return (alloc_ptr + sizeof(t_header));
}

size_t  align(size_t val, size_t alignement)
{
    return (val + alignement - (!(val % alignement) ? alignement : val % alignement));
}
