#include "../../minishell.h"

uint8_t	ft_isvariable(char *str)
{
	int		i;

	// 0 = $?
	// 1 = $ARG
	// 2 = ${ARG}
	// 3 = INVALID

	i = 0;
	if (str[i] == '$')
	{
		i++;
		//{ } FORMAT
		if (str[i] == '{')
		{
			
		}

		// $?
		else if (str[i] == '?')
		{

		}

		// $ARG
		else if (!ft_isspace(str[i]))
		{

		}
	}
	return (0);
}
