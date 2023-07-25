#include "../../minishell.h"

// Return false if this is an invalid ENV variable name
bool	ft_iscorrectenvname(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return false;
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
			return false;
		i++;
	}
	return true;
}
