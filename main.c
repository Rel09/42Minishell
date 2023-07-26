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

		// Parser input and Store in Linked list
		t_parser *token = ft_sstrtok(input);
		t_input *linkedlist = NULL;
		t_input *linkedlisthead = NULL;
		int i = 0;

		while (token->str)
		{
			t_input *newNode = malloc(sizeof(t_input));
			newNode->index = i++;
			newNode->str = ft_strdup(token->str);
			newNode->flags = token->flags;
			newNode->next = NULL;
			if (!linkedlist)
			{
				linkedlist = newNode;
				linkedlisthead = linkedlist;
			}
			else
			{
				linkedlist->next = newNode;
				linkedlist = linkedlist->next;
			}
			
			token = ft_sstrtok(0);
		}

		// Print LL
		t_input	*temp = linkedlisthead;
		while (temp)
		{
			printf("[%i] [%s]\n", temp->index, temp->str);
			temp = temp->next;    
		}


		//linkedlist = parse_input(input);
	}

	return (0);
}
