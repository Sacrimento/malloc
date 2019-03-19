#include "malloc.h"

int     main(int argc, char **argv)
{
    struct rlimit rlim;

    char    *tt;
    char    *aa;

    tt = (char*)ft_malloc(11);
    aa = (char*)malloc(11);

    // printf("%p\n", ft_malloc(5));
    // printf("%d\n", getpagesize());
    // getrlimit(RLIMIT_AS, &rlim);
    // printf("%lu, %lu\n", rlim.rlim_cur, rlim.rlim_max);

    return (0);
}

void    *find_first_fit(size_t size)
{
    if (!(g_page))
        return (NULL);
    return (NULL);
}

void    *alloc_new_page(size_t size)
{
    t_page  page;
    t_page  *curr;

    page.type = get_page_type(size);
    page.size = get_page_size(page.type, size);
    page.addr = mmap(NULL, page.size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    page.next = NULL;

    if (!(g_page))
        g_page = &page;
    curr = g_page;
    while (curr->next)
        curr = curr->next;
    curr->next = &page;
}

void    *ft_malloc(size_t size)
{
    void    *ptr;
    
    if (!(ptr = find_first_fit(size)) && !(ptr = alloc_new_page(size)))
        return ((void*)-1);
    
    return (ptr);
}