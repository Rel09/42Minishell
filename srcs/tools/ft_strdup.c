#include "../../minishell.h"

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = -1;
	while (src[++size])
        ;
	new = malloc(size + 1);
    if (!new)
		return (NULL);
	i = -1;
	while (src[++i])
		new[i] = src[i];
	new[i] = 0;
	return (new);
}