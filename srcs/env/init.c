/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:46:37 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 20:46:38 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    if (ft_iscorrectenvname(str))
    {
        find_and_remove(str);
        e = *get_env();
        ft_insert2darray(&newenv, e, str);
        ft_sort2darray(&newenv);
        free_env();
        *get_env() = newenv;
    }
    else
        printf("Export -> Invalid ARG Identifier\n");
}

// Free the env
void    free_env()
{
    int     i;
    char    **e;

    i = 0;
    e = *get_env();
    while (e[i])
        free(e[i++]);
    free(e);
    *get_env() = 0;
}
