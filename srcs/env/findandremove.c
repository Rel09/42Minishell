#include "../../minishell.h"

static void    remove_from_env(char *str)
{
    char    **e;
    char    **newenv;

    e = *get_env();
    ft_remove2darray(&newenv, e, str);
    ft_sort2darray(&newenv);
    free_env();
    *get_env() = newenv;
}

// Find and Remove variable in Env
// pass hello=DIJASID and hello= var will be deleted
void	find_and_remove(char *str)
{
	int		i;
	char	varname[200];

	ft_bzero(varname, 200);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			ft_strncat(varname, str, i + 1);
			remove_from_env(varname);
			return ;
		}
	}
}
