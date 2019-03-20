#include "malloc.h"

int     main(int argc, char **argv)
{
    struct rlimit rlim;

    char    *tt;
    char    *aa;

    tt = (char*)ft_malloc(9000);
    aa = (char*)malloc(1000);
    tt = (char*)ft_malloc(9000);
    tt = (char*)ft_malloc(9000);
    tt = (char*)ft_malloc(9000);
    tt = (char*)ft_malloc(9000);
    tt = (char*)ft_malloc(111119000);

    ft_free(tt);

    return (0);
}

void    *find_first_fit(size_t size)
{
    t_page  *curr;
    t_type  type;
    void    *ptr;

    ptr = NULL;
    if (!(g_page))
        return (NULL);
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
    t_page  *page;
    t_page  *curr;

    if ((page = mmap(NULL, sizeof(t_page), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
        return (NULL);

    page->type = get_page_type(size);
    page->size = get_page_size(page->type, size);
    if (!(page->alloc = new_mmap_alloc(page->size)))
        return (NULL);
    page->next = NULL;

    if (!(g_page))
        g_page = page;
    else
    {
        curr = g_page;
        while (curr->next)
            curr = curr->next;
        curr->next = page;
    }

    return (find_first_fit(size));
}

void    *ft_malloc(size_t size)
{
    void    *ptr;
    
    if (!(ptr = find_first_fit(size)) && !(ptr = alloc_new_page(size)))
        return ((void*)-1);
    
    printf("Malloc returned : %p\n", ptr);
    return (ptr);
}