#include "../../minishell.h"

void	show_env(void)
{
	int		i;
	char	**e;

	i = -1;
	e = *get_env();
	while (e[++i])
		printf("%s\n", e[i]);
}

void	show_env_export(void)
{
	int			i;
	int			j;
	char		**t;

	t = *get_env();
	i = -1;
	while (t[++i])
	{
		printf("declare -x ");
		j = -1;
		while (t[i][++j])
		{
			printf("%c", t[i][j]);
			if (t[i][j] == '=')
				printf("\"");
		}
		printf("\"\n");
	}
}
