#include "../../minishell.h"

int ft_count2darray(char **s)
{
    int i;

    i = -1;
    while (s[++i])
        ;
    return (i);
}