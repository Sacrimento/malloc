#include "show_alloc_mem.h"

void    show_alloc_mem()
{
    int             i;
    const char      *type[3] = {"TINY", "SMALL", "LARGE"};
    t_page          *curr_page;
    void            *alloc;

    i = 0;
    while (i < 3)
    {
        printf("%s :", type[i]);
        curr_page = g_page[i];
        if (!curr_page)
            printf("\n");
        while (curr_page)
        {
            printf("\r\t%p\n", curr_page->alloc);
            alloc = curr_page->alloc;
            while (((t_header*)alloc)->size != 0)
            {
                if (!((t_header*)alloc)->free)
                    printf("%p - %p : %lu octets\n", alloc + sizeof(t_header), alloc + ((t_header*)alloc)->size, ((t_header*)alloc)->size - sizeof(t_header));
                alloc += ((t_header*)alloc)->size;
            }
            curr_page = curr_page->next;
        }
        i++;
    }
}