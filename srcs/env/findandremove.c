#include "../../minishell.h"

// Backend for find_and_remove
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

	i = -1;
	ft_bzero(varname, 200);
	while (str[++i])
	{
		if (str[i] == '=')
		{
			ft_strncat(varname, str, i + 1);
			remove_from_env(varname);
			return ;
		}
	}
	printf("ERROR -> find_and_remove never found var with = in its name\n");
	exit(1);
}

// Find and Return variable in Env
// pass ARG name and its value will be returned
char	*find_and_return(char *str)
{
	int		i;
	int		len;
	char	**e;

	i = -1;
	e = *get_env();
	len = ft_strlen(str);
	while (e[++i])
	{
		if (!ft_strncmp(e[i], str, len))
			return (&e[i][len]);
	}
	return ("");
}
