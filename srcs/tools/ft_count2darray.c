#include "../../minishell.h"

int ft_count2darray(char **s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}
