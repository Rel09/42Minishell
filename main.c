/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:52:54 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 01:52:55 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linkedlist(t_input *LL)
{
	//t_input	*temp = LL;
	while (LL)
	{
		for (int i = 0; LL->commands[i]; i++) {
			printf("[%s] ", LL->commands[i]);
		}
		printf("     STDIN:[%i]  STDOUT:[%i]\n", LL->_stdin, LL->_stdout);
		LL = LL->next;
	}

	// Testing for Previous node
	/*
	while (temp && temp->next)
		temp = temp->next;

    while (temp)
    {
        for (int i = 0; temp->commands[i]; i++) {
			printf("[%s] ", temp->commands[i]);
		}
		printf("     STDIN:[%i]  STDOUT:[%i]\n", temp->_stdin, temp->_stdout);
		temp = temp->previous;
    }
	*/

}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	t_input	*linkedlist;
	init_env(env);
	while (true)
	{
		printf(COLOR_KIRBY_PINK);
		input = readline("Minishell > ");
		printf(COLOR_RESET);
		if (!input)
		{
			printf("Readline Input Error\n");
			return (1);
		}
		add_history(input);
		linkedlist = parse_input(input);
		print_linkedlist(linkedlist);		// temp
		free_input(linkedlist);				// free
		//break;							// Valgrind Test
	}
	free_env();								// free
	rl_clear_history();						// free
	return (0);
}
