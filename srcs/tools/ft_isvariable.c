#include "../../minishell.h"

uint8_t	ft_isvariable(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		// { } FORMAT
		//if (str[i] == '{')
		//{
			//i++;
			//if (ft_iscorrectenvname(str[i]) || str[i] == '}')
		//}

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
