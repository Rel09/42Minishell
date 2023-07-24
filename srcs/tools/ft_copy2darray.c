#include "../../minishell.h"

// Just copy the 2D Array
void    ft_copy2darray(char ***dist, char **src)
{
    int     i;
    char    **new;
    
    new = malloc((ft_count2darray(src) + 1) * sizeof(char *));
    if (!new)
    {
        printf("Malloc error while making new Env\n");
        exit(1);
    }
    i = -1;
    while (src[++i])
    {
        new[i] = ft_strdup(src[i]);
        if (!new[i])
        {
            printf("Malloc error while Copying Env\n");
            exit(1);
        }
    }
    new[++i] = 0;
    *dist = new;
}