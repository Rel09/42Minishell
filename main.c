/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:54:02 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 19:11:54 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	read_input(char	*input)
{
	t_input	*linkedlist;

	while (true)
	{
		intercept_signals();
		input = readline("Minishell > ");
		if (!input)
			ms_exit(NULL);
		add_history(input);
		if (!check_input(input))
			continue ;
		linkedlist = parse_input(input, NULL);
		if (!linkedlist)
			continue ;
		interactive_sighandlers();
		if (!heredoc_state()->cancel || !argschecker(linkedlist))
			command_handler(linkedlist);
		else
		{
			clean_mess(linkedlist);
			continue ;
		}
		delete_heredocs_files();
		free_input(linkedlist);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env(env);
	intercept_signals();
	save_std(SAVE_IN | SAVE_OUT);
	read_input(NULL);
	return (0);
}
