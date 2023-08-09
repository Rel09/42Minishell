/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:54:02 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 03:11:53 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(void)
{
	char	*input;
	t_input	*linkedlist;

	while (true)
	{
		input = readline("Minishell > ");
		signal(SIGINT, sigint_running_shell);
		if (!input)
			ms_exit(NULL);
		add_history(input);
		if (!check_input(input))
			continue ;
		linkedlist = parse_input(input);
		if (!linkedlist)
			continue ;
		signal(SIGINT, sigint_interactive);
		if (*heredoc_pid() != HEREDOC_KILLED || !argschecker(linkedlist))
			command_handler(linkedlist);
		else
			clean_mess(input, linkedlist);
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
	read_input();
	return (0);
}
