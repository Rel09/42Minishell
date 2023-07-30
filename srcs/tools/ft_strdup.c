#include "../../minishell.h"

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
        size++;
	new = malloc(size + 1);
    if (!new)
		return (0);
	i = -1;
	while (src[++i])
		new[i] = src[i];
	new[i] = 0;
	return (new);
}
