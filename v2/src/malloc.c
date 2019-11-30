#include "malloc.h"
#include "page.h"

void    *ft_malloc(size_t size)
{
    if (size == 0)
        return (NULL);
    return (first_fit(size, NULL));
}

void    ft_free(void *ptr)
{
    t_page  *page;

    if (!ptr)
        return;
    if (((t_header*)(ptr - sizeof(t_header)))->free)
        printf("%p: double free\n", ptr);
    ((t_header*)(ptr - sizeof(t_header)))->free = 1;

    
    page = get_page_from_alloc(ptr - sizeof(t_header));
    if (is_page_free(page->alloc))
        destroy_page(page);
}

void main() // -1 BOUCLE INF
{
    void *p = ft_malloc(-1);
    p = ft_malloc(2000);
    show_alloc_mem();
    ft_free(p);
    // show_alloc_mem();
    // printf("%lu\n", (*(t_header*)(g_page[2]->alloc)).size);

}