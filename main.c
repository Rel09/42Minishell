#include "minishell.h"

// Convert the $args, ${}, $?
// Store the HEREDOC exit keyword inside struct and remove?
// Convert command to bitshift variables and remove?
// Tweak STRTOK for less lines

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	t_input	*linkedlist;

	init_env(env);
	while (true)
	{
		// Read Input
		printf(COLOR_KIRBY_PINK);
		input = readline("Minishell > ");
		printf(COLOR_RESET);
		if (!input)
		{
			printf("Readline Input Error\n");
			return (1);
		}

		// Add to history
		add_history(input);

		// Split everything
		linkedlist = parse_input(input);

		// Print everything
		/*
		t_input	*temp = linkedlist;
		while (temp)
		{
			printf(COLOR_CYAN);

			for (int i = 0; temp->commands[i]; i++)
			{
				printf("[%s] ", temp->commands[i]);
			}
			printf("\n");


			printf(COLOR_RESET);
			temp = temp->next;    
		}
		*/
		

		//free_input(linkedlist);
	}
	free_env();
	rl_clear_history();
	return (0);
}
