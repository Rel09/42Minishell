#include "../../minishell.h"

// Return a non-zero value if its a quote, return its uint8_t value
// so we can also store what kind is it
uint8_t	ft_isquote(char	*str)
{
	if (!ft_strncmp(str, "\"", 1))
		return (1);
	else if (!ft_strncmp(str, "'", 1))
		return (2);
	return (0);
}
