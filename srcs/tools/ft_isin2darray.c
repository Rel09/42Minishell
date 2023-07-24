#include "../../minishell.h"

bool    ft_isin2darray(char **src, char *tofind)
{
    int             i;
    unsigned int    size;

    i = -1;
    size = ft_strlen(tofind);
    while (src[++i])
    {
        if (!ft_strncmp(src[i], tofind, size))
            return true;
    }
    return false;
}