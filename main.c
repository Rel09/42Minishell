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
		input = readline("Minishell > ");
		if (!input)
		{
			printf("Readline Input Error\n");
			exit(1);
		}

		// Add to history
		add_history(input);

		// Split everything
		linkedlist = parse_input(input);

		t_input	*temp = linkedlist;
		while (temp)
		{
			printf("[%i] [%s]\n", temp->index, temp->str);
			temp = temp->next;    
		}


	}

	return (0);
}
