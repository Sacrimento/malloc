#ifndef MALLOC_H
#  define MALLOC_H

#  include <stdlib.h>
#  include <unistd.h>
#  include <sys/mman.h>
#  include <sys/time.h>
#  include <sys/resource.h>

#  include <stdio.h>

/*
    BONUSES :
        -DEFRAGMENTATION++
        -CALLOC
        -ALIGNEMENT DES BYTES
        
        -MUTEX
*/

#  define TINY_MAX 128
#  define SMALL_MAX 1024

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

t_page  *g_page[3];

void    *ft_malloc(size_t size);
void    free(void *ptr);
void    *ft_realloc(void *ptr, size_t size);

void    show_alloc_mem();

t_type  get_page_type(size_t size);
size_t  get_page_size(t_type type, size_t size);
int     is_page_removable(t_page *page);

void    *get_first_fit_addr(t_page *page, size_t size);
void    *fragment_page(t_page *page, t_alloc *alloc, size_t size);
t_alloc *new_mmap_alloc(size_t size);

t_page  *free_ptr(void *ptr);
int     allocs_defragmentation(t_page *page);
void    align_allocations(t_page *page);
void    remove_empty_page(t_page *page);

int     count_allocs(t_alloc *alloc);

void    debug_allocs(t_page *page);
void    debug_pages(void);

#endif