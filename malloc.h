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
    FREE,
    ALLOCATED
}               t_status;

typedef struct s_alloc
{
    size_t          size;
    t_status        status;
    void            *data_addr;
    struct s_alloc  *next;
}               t_alloc;


typedef struct  s_page
{
    t_type          type;
    size_t          size;
    t_alloc         *alloc;
    struct s_page   *next;
}               t_page;

t_page  *g_page;

void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    *ft_realloc(void *ptr, size_t size);

void    show_alloc_mem();

t_type  get_page_type(size_t size);
size_t  get_page_size(t_type type, size_t size);

void    *get_first_fit_addr(t_page *page, size_t size);
void    *fragment_page(t_page *page, t_alloc *alloc, size_t size);
t_alloc *new_mmap_alloc(size_t size);

t_page  *free_ptr(void *ptr);
int     allocs_defragmentation(t_page *page);
void    search_and_destroy(t_type type);

int     count_pages(t_type type);
int     count_allocs(t_alloc *alloc);

#endif