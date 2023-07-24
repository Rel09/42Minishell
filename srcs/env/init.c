#include "../../minishell.h"

// Hold the Env
char    ***get_env()
{
    static char    **env;

    return (&env);
}

// Init the Env
void    init_env(char **env)
{
    char    **e;

    ft_copy2darray(&e, env);
    ft_sort2darray(&e);
    *get_env() = e;
}

// Add element to env
void    add_to_env(char *str)
{
    char    **e;
    char    **newenv;

    // Remove it first if it exist
    e = *get_env();
    ft_insert2darray(&newenv, e, str);
    ft_sort2darray(&newenv);
    free_env();
    *get_env() = newenv;
}

// Remove element from env
void    remove_from_env(char *str)
{
    char    **e;
    char    **newenv;
    
    e = *get_env();
    if (!ft_isin2darray(e, str))
        printf("[%s] Not in ENV\n", str);
    else {
        ft_remove2darray(&newenv, e, str);
        ft_sort2darray(&newenv);
        free_env();
        *get_env() = newenv;
    }
}

// Free the env
void    free_env()
{
    int     i;
    char    **e;

    i = -1;
    e = *get_env();
    while (e[++i])
        free(e[i]);
    free(e);
    *get_env() = 0;
}