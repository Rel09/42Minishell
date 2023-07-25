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
		
		// Read Input
		input = readline("Minishell > ");
		if (!input)
		{
			printf("Readline Input Error\n");
			exit(1);
		}

		// Add to history
		add_history(input);


		//linkedlist = parse_input(input);
	}

	return (0);
}
