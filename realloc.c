#include "malloc.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst);
}

t_page  *get_page_from_ptr(void *ptr)
{
    int     i;
    t_page  *curr_page;
    t_alloc *curr_alloc;

    i = -1;
    while (++i < 3)
    {
        curr_page = g_page[i];
        while (curr_page)
        {
            curr_alloc = curr_page->alloc;
            while (curr_alloc)
            {
                if (curr_alloc->data_addr == ptr && curr_alloc->status == ALLOCATED)
                    return (curr_page);
                curr_alloc = curr_alloc->next;
            }
            curr_page = curr_page->next;
        }
    }
    return (NULL);
}

int     extend(t_page *page, void *ptr, size_t size)
{
    t_alloc     *curr;

    curr = page->alloc;
    while (curr)
    {
        if (curr->data_addr == ptr && curr->next && curr->next->status == FREE && curr->next->size + curr->size > size)
        {
            if (!(curr->next = new_alloc(curr->size + curr->next->size - size, (void*)(curr->data_addr + size), curr->next)))
                return (0);
            curr->next->size = size;
            return (1);
        }
        curr = curr->next;
    }
    return (0);
}

void    *try_to_extend(void *ptr, size_t size)
{
    t_page  *page;
    void    *ret;                                                                                                                                                                                                                                                                                                                                                                                                                                                           

    if (!(page = get_page_from_ptr(ptr)))
        return (NULL);

    if (extend(page, ptr, size))
        return (ptr);
    return (NULL);
}

void    *realloc(void *ptr, size_t size)
{
    void    *ret;

    ft_putstr("realloc begin\n");

    if (!ptr)
        return (malloc(size));
    if (!size)
    {
        free(ptr);
        return (malloc(16));
    }
    if (!(ret = try_to_extend(ptr, size)))
    {
        ret = malloc(size);
        ft_memcpy(ret, ptr, size);
        free(ptr);
    }
    ft_putstr("realloc end\n");
    return (ret);
}