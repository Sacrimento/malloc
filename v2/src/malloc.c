#include "allocation.h"
#include "malloc.h"
#include <stdio.h>

void    *ft_malloc(size_t size)
{
    return (first_fit(size, NULL));
}


void main()
{
    void *p = ft_malloc(1028);
    printf("%lu\n", (*(t_header*)(g_page[2]->alloc)).size);
    printf("%lu %lu %lu\n", sizeof(t_header), sizeof(size_t), sizeof(int));

}