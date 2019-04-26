#include "malloc.h"

int     count_allocs(t_alloc *alloc)
{
    return (alloc ? 1 + count_allocs(alloc->next) : 0);
}