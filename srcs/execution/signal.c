/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:17:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 02:36:19 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_running_shell(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
}

void	sigint_running_heredoc(int sig)
{
	(void) sig;
	(*heredoc_pid()) = HEREDOC_KILLED;
	rl_on_new_line();
}

void	sigint_interactive(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_replace_line("", 0);
	rl_forced_update_display();
}

int	intercept_signals(void)
{
	signal(SIGINT, sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	heredoc_child_sighandler(int sig)
{
	int	fd;

	(void) sig;
	clean_static_memory();
	fd = *heredoc_fd();
	if (fd > 2)
	{
		close(fd);
		(*heredoc_fd()) = 0;
	}
	free_input(*heredoc_ll());
	exit(EXIT_FAILURE);
}
