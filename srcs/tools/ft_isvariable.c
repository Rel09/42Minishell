#include "../../minishell.h"

uint8_t	ft_isvariable(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '$')
	{

		// { } FORMAT
		if (str[i + 1] == '{')
		{

		}

		// $?
		else if (str[i + 1] == '?')
		{

		}

		// $ARG
		else if (!ft_isspace(str[i + 1]))
		{

		}
	}

}
