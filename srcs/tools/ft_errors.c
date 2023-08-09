/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 03:07:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 03:11:20 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	argschecker(t_input *LL)
{
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

bool	check_input(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token '|'\n",
			STDERR_FILENO);
		//Faut mettre le bon error code quand le user ecrit juste "|"
		//g_last_result = 268;
		free(input);
		return (false);
	}
	return (true);
}

void	clean_mess(char *input, t_input *LL)
{
	free(input);
	free_input(LL);
	heredoc_state()->cancel = false;
}

void	restoreline()
{
	dup2(heredoc_state()->stdin_clone, STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_replace_line("", 0);
}