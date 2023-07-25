#include "../../minishell.h"

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
