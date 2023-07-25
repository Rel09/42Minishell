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

		
		char s = '<';
		/* get the first token */
		char *token = ft_strtok(input, s);
		
		/* walk through other tokens */
		while( token != NULL ) {
			printf("[%s]\n", token );
			
			token = ft_strtok(NULL, s);
		}



		//linkedlist = parse_input(input);
	}

	return (0);
}
