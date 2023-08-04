/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:54:02 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/04 07:03:11 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linkedlist(t_input *LL)
{
	int	i;

	if (!LL)
	{
		printf("%p\n", LL);
		return ;
	}
	while (LL)
	{
		i = 0;
		while (LL->commands[i])
			printf("[%s] ", LL->commands[i++]);
		printf("     STDIN:[%i]  STDOUT:[%i]\n", LL->_stdin, LL->_stdout);
		LL = LL->next;
	}
}

bool	argschecker(t_input *LL, char *input)
{
	int	i;

	while (LL)
	{
		if (!LL->commands)
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token\n",
				STDERR_FILENO);
			return (false);
		}
		LL = LL->next;
	}
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	check_fd(t_input *input)
{
	if (input->_stdin == -1 || input->_stdout == -1)
	{
		if (input->_stdin == -1)
		{
			open(input->_stdinname, O_RDONLY);
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			perror_global(input->_stdinname);
		}
		if (input->_stdout == -1)
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			perror_global(input->_stdoutname);
		}
		return (false);
	}

	return (true);
}

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
		linkedlist = parse_input(input);
		if (!linkedlist || !argschecker(linkedlist, input))
			continue ;
		command_handler(linkedlist);
		signal(SIGINT, sigint_interactive);
		free(input);
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
