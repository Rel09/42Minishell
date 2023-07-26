#include "../../minishell.h"

// Check if its a single char or multi char delimiter
uint8_t	is_delimiter(char	*str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (4);
	else if (!ft_strncmp(str, ">>", 2))
		return (5);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (2);
	else if (!ft_strncmp(str, "|", 1))
		return (3);
	return (0);
}
