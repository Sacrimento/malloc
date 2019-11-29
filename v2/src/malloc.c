#include "malloc.h"
#include "show_alloc_mem.h"

void    *ft_malloc(size_t size)
{
    return (first_fit(size, NULL));
}

void    ft_free(void *ptr)
{
    if (!ptr)
        return;
    if (((t_header*)(ptr - sizeof(t_header)))->free)
        printf("%p: double free\n", ptr);
    ((t_header*)(ptr - sizeof(t_header)))->free = 1;
}

void main()
{
    void *p = ft_malloc(300);
    p = ft_malloc(300);
    p = ft_malloc(300);
    p = ft_malloc(300);
    show_alloc_mem();
    ft_free(p);
    show_alloc_mem();
    // printf("%lu\n", (*(t_header*)(g_page[2]->alloc)).size);

}