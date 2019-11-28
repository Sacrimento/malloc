#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

#define TINY_MAX 128
#define SMALL_MAX 1024

#define TINY_SIZE 16384
#define SMALL_SIZE 131072

#define ALIGNEMENT 32

typedef enum    e_type
{
    TINY,
    SMALL,
    LARGE
}               t_type;

typedef struct  s_page
{
    t_type          type;
    void            *alloc;
    struct s_page   *next;
}               t_page;

typedef struct s_header
{
    size_t  prev_size;
    size_t  size;
    size_t  free;
    size_t  padding;
}               t_header;

t_page  *g_page[3];

void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    *ft_realloc(void *ptr, size_t size);

#include <stdio.h>

#endif