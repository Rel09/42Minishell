/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:52:54 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:41:49 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linkedlist(t_input *LL)
{
	int	i;

	while (LL)
	{
		i = 0;
		while (LL->commands[i])
			printf("[%s] ", LL->commands[i++]);
		printf("     STDIN:[%i]  STDOUT:[%i]\n", LL->_stdin, LL->_stdout);
		LL = LL->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_input	*linkedlist;

	(void)ac;
	(void)av;
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
		print_linkedlist(linkedlist);		// Print Linked list
		free_input(linkedlist);				// Free Linked List
	}
	free_env();								// Free Env
	rl_clear_history();
	return (0);
}
