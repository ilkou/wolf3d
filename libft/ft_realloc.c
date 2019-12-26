
#include <libft.h>

void    *ft_realloc(void **ptr, size_t old, size_t len)
{
    void    *real;

    real = malloc(len);
    ft_memset(real, 0, len);
    if (real)
        ft_memcpy(real, *ptr, old);
    if (*ptr)
        free(*ptr);
    return (real);
}
