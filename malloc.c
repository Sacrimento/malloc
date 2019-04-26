#include "malloc.h"

int     main(int argc, char **argv)
{
    char    *tt;
    char    *aa;
    char    *ss;
    char    *dd;
    char    *ff;
    char    *gg;
    char    *hh;
    char    *jj;
    char    *kk;
    char    *ll;

    // for (int i = 0; i < 100; i++)
    // {
        tt = ft_malloc(1024);
        aa = ft_malloc(1024);
        ff = ft_malloc(1024);
    // }

    show_alloc_mem();

    ft_free(aa);

    show_alloc_mem();

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
    
    if (size == 0)
        return (NULL);

    if (!(ptr = find_first_fit(size)) && !(ptr = alloc_new_page(size)))
        return ((void*)-1);
    
    printf("Malloc returned : %p\n", ptr);
    return (ptr);
}