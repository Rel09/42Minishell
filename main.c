#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	//t_input	*linkedlist;
	init_env(env);
	while (true)
	{
		input = readline("Minishell > ");
		if (!input)
		{
			printf("Readline Input Error\n");
			exit(1);
		}
		add_history(input);

		if (!ft_strcmp(input, "ADD")) {
			add_to_env("VA CHIER GINETTE");

			printf("Added\n");

		}
		else if (!ft_strcmp(input, "SHOW"))
		{
			char **TEMP = *get_env();
			for (int i = 0; TEMP[i]; i++)
				printf("%s\n", TEMP[i]);
		}
		else if (!ft_strcmp(input, "REMOVE"))
		{
			remove_from_env("VA CHIER");
		}
		//linkedlist = parse_input(input);
	}

	return (0);
}
