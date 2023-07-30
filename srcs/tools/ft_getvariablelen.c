#include "../../minishell.h"

int	ft_getvariablelen(char *str)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '{')
		{
			len++;
			while (str[i] && str[i] != '}')
			{
				i++;
				len++;
			}
			return (len + 1);
		}
		else if (str[i] == '?')
			return (2);
		else if (!ft_isspace(str[i]))
		{
			while (str[i] && str[i] != ' ')
			{
				i++;
				len++;
			}
			return (len + 1);
		}
	}
	return (len);
}
