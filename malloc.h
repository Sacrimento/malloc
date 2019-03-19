#ifndef MALLOC_H
#  define MALLOC_H

#  include <stdlib.h>
#  include <unistd.h>
#  include <sys/mman.h>
#  include <sys/time.h>
#  include <sys/resource.h>

#  include <stdio.h>

typedef enum    e_type
{
    TINY,
    SMALL,
    LARGE
}               t_type;

typedef enum    e_status
{
    ALLOCED,
    FREED
}               t_status;

typedef struct  s_page
{
    t_type          type;
    size_t          size;
    void            *addr;
    struct s_page   *next;
}               t_page;

typedef struct s_alloc
{
    size_t      size;
    t_status    status;
}               t_alloc;


t_page  *g_page;

void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    *ft_realloc(void *ptr, size_t size);

t_type  get_page_type(size_t size);
size_t  get_page_size(t_type type, size_t size);

#endif