#include "malloc.h"

int     main(int argc, char **argv)
{
    struct rlimit rlim;

    char    *tt;
    char    *aa;

    tt = (char*)ft_malloc(9000);
    aa = (char*)malloc(11);

    printf("%p\n", tt);

    // printf("%p\n", ft_malloc(5));
    // printf("%d\n", getpagesize());
    // getrlimit(RLIMIT_AS, &rlim);
    // printf("%lu, %lu\n", rlim.rlim_cur, rlim.rlim_max);

    return (0);
}

void    *find_first_fit(size_t size)
{
    t_page  *curr;
    t_type  type;
    void    *ptr;

    printf("FIND FIRST FIT WAS CALLED\n");
    if (g_page)
        printf("%d\n", g_page->alloc->status); 
    ptr = NULL;
    if (!(g_page))
    {
        printf("FIND FIRST FIT RETURNED NULL\n");
        return (NULL);
    }
    printf("%d\n", g_page->alloc->status);
    curr = g_page;
    type = get_page_type(size);

    while (curr)
    {
        if (curr->type == type && (ptr = get_first_fit_addr(curr, size)))
            return (ptr);
        curr = curr->next;
    }
    return (NULL);
}

void    *alloc_new_page(size_t size)
{
    t_page  page;
    t_page  *curr;

    page.type = get_page_type(size);
    page.size = get_page_size(page.type, size);
    if (!(page.alloc = new_mmap_alloc(page.size)))
        return (NULL);
    page.next = NULL;

    if (!(g_page))
        g_page = &page;
    else
    {
        curr = g_page;
        while (curr->next)
            curr = curr->next;
        curr->next = &page;
    }

    printf("%d\n", g_page->alloc->status);
    return (find_first_fit(size));
}

void    *ft_malloc(size_t size)
{
    void    *ptr;
    
    if (!(ptr = find_first_fit(size)) && !(ptr = alloc_new_page(size)))
        return ((void*)-1);
    
    return (ptr);
}