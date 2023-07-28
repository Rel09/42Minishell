#include "../../minishell.h"

// Transform all $ARG, ${ARG} and $? to their actual value
char	*expand_vars(char *str)
{
	int		i;
	int		j;
	//char	*newstr;
	char	temp[200];

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && !ft_isspace(str[i + 1]))
		{
			while (str[i] && !ft_isspace(str[i]))
				temp[j++] = str[i++];
		}
	}
	return (0);
}
