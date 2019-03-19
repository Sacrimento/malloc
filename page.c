#include "malloc.h"

t_type  get_page_type(size_t size)
{
    size_t  page_size;

    page_size = (size_t)getpagesize();

    if (size < 2 * page_size)
        return (TINY);
    else if (size < 8 * page_size)
        return (SMALL);
    else
        return (LARGE);
}

size_t  get_page_size(t_type type, size_t size)
{
    size_t  page_size;
    size_t  ret;

    page_size = (size_t)getpagesize();

    if (type == TINY)
        return (2 * page_size);
    else if (type == SMALL)
        return (8 * page_size);
    else
    {
        ret = 0;
        while (ret < size)
            ret += page_size;
        return (ret);
    }
}