#include "allocation.h"
#include "page.h"

void    *alloc_new_page(size_t size)
{
    t_page  *page;
    size_t  page_size;


    if ((page = mmap(NULL, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);

    page->type = get_page_type(size);
    page->next = g_page[page->type];
    g_page[page->type] = page;

    page_size = get_page_size(size);

    if ((page->alloc = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);

    (*(t_header*)page->alloc).prev_size = 0;
    (*(t_header*)page->alloc).size = page_size - sizeof(t_header);
    (*(t_header*)page->alloc).free = 1;

    printf("%lu %lu\n", (*(t_header*)page->alloc).size, getpagesize());

    (*(t_header*)(page->alloc + (*(t_header*)page->alloc).size)).size = 0;

    return (first_fit(size, page));
}

t_type  get_page_type(size_t size)
{
    if (size < TINY_MAX)
        return (TINY);
    else if (size < SMALL_MAX)
        return (SMALL);
    else
        return (LARGE);
}

size_t  get_page_size(size_t size)
{
    int     page_alignement;

    page_alignement = getpagesize();
    if (size < TINY_MAX)
        return (align(TINY_SIZE, page_alignement));
    else if (size < SMALL_MAX)
        return (align(SMALL_SIZE, page_alignement));
    else
        return (align(size + 2 * sizeof(t_header), page_alignement));
}