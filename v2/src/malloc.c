#include "malloc.h"
#include "page.h"

void    *ft_malloc(size_t size)
{
    if (size == 0)
        return (first_fit(ALIGNEMENT, NULL));
    return (first_fit(size, NULL));
}

void    *ft_calloc(size_t nmemb, size_t size)
{
    char    *ptr;
    size_t  i;

    ptr = (char*)ft_malloc(nmemb * size);
    i = 0;

    if (ptr)
        while (i < nmemb * size)
            *(ptr + i++) = 0;

    return (ptr);
}

void    *ft_realloc(void *ptr, size_t size)
{
    
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
    struct rlimit   r;
    size_t a = -2;
    getrlimit(RLIMIT_AS, &r);
    printf("%p\n", malloc(0));
    printf("%p\n", malloc(18));
    printf("%lu\n", a);
    printf("%lu %lu\n", r.rlim_cur, r.rlim_max);
//     void *p = ft_malloc(-1);
//     p = ft_malloc(2000);
//     show_alloc_mem();
//     ft_free(p);
    // show_alloc_mem();
    // printf("%lu\n", (*(t_header*)(g_page[2]->alloc)).size);

}