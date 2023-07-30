#include "../../minishell.h"


static char	*get_arg_name(char *str, char delim)
{
	int	i;
	int j;
	static char	temp[100];

	i = 0;
	j = 0;
	ft_bzero(temp, 100);
	while (str[i] && str[i] != delim)
		temp[j++] = str[i++]; 
	temp[j] = '=';
	return (find_and_return(temp));
}

char	*ft_isvariable(char *str)
{
	int			i;
	int			j;
	char		*temp;
	static char	cashreturn[11];

	i = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '{')
		{
			i++;
			return (get_arg_name(&str[i], '}'));
		}
		else if (str[i] == '?')
		{
			ft_bzero(cashreturn, 11);
			temp = ft_itoa(g_last_result);
			ft_strcpy(cashreturn, temp);
			free(temp);
			return (cashreturn);
		}
		else if (!ft_isspace(str[i]))
			return (get_arg_name(&str[i], ' '));
	}
	return (0);
}
