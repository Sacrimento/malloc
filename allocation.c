#include "malloc.h"

void    *get_first_fit_addr(t_page *page, size_t size)
{
    t_alloc *curr;

    curr = page->alloc;
    while (curr)
    {
        if (curr->status == FREE && size <= curr->size)
            return (fragment_page(page, curr, size));
        curr = curr->next;
    }
    return (NULL);
}

t_alloc *new_mmap_alloc(size_t size)
{
    t_alloc *new_alloc;
    
    if ((new_alloc = mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);

    new_alloc->size = size;
    new_alloc->status = FREE;
    if (!(new_alloc->data_addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)))
        return (NULL);
    new_alloc->next = NULL;

    return (new_alloc);
}

t_alloc *new_alloc(size_t size, void *addr, t_alloc *next)
{
    t_alloc *new_alloc;

    if ((new_alloc = mmap(NULL, sizeof(t_alloc), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);
    new_alloc->status = FREE;
    new_alloc->size = size;
    new_alloc->data_addr = addr;
    new_alloc->next = next;

    return (new_alloc);
}

void    *fragment_page(t_page *page, t_alloc *alloc, size_t size)
{
    t_alloc *curr;

    curr = page->alloc;
    while (curr)
    {
        if (curr == alloc)
        {
            alloc->status = ALLOCATED;
            if (!(alloc->next = new_alloc(alloc->size - size, (void*)(alloc->data_addr + size), alloc->next)))
                return (NULL);
            alloc->size = size;
            return (alloc->data_addr);
        }
        curr = curr->next;
    }
    return (NULL);
}