/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:55:06 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 02:30:16 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create a fork during HEREDOC so we can kill it while its running
static void	heredoc_fork(char **input, char *keyword, int fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_child_sighandler);
		(*heredoc_fd()) = fd;
		while (ft_strcmp(*input, keyword))
		{
			free(*input);
			*input = readline("> ");
			if (ft_strcmp(*input, keyword))
			{
				ft_putstr_fd(convert_all_args_hd(*input), fd);
				ft_putstr_fd("\n", fd);
			}
		}
		free_garbage(*heredoc_ll(), input, fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_last_result, 0);
		convert_exit();
	}
}

// If Heredoc get interrupted, close all open fds;
void	heredoc_cleanup(t_input	*node)
{
	while (node)
	{
		if (node->_stdin != STDIN_FILENO)
			close(node->_stdin);
		if (node->_stdout != STDOUT_FILENO)
			close(node->_stdout);
		node = node->next;
	}
}

// Return true if one FD failed to open, so we can skip the rest
bool	*heredoc_broken(void)
{
	static bool	broken;

	return (&broken);
}

// Heredoc Entry
void	heredoc(char *keyword, t_input *node)
{
	char	*input;
	char	*filename;
	int		fd;

	if (*heredoc_broken())
		return ;
	input = malloc(1);
	*input = 0;
	filename = get_uniquefilename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, sigint_running_heredoc);
	*heredoc_ll() = node;
	heredoc_fork(&input, keyword, fd);
	if (*heredoc_pid() != HEREDOC_KILLED)
		(*heredoc_pid()) = 0;
	close(fd);
	free(input);
	*heredoc_ll() = 0;
	(*heredoc_fd()) = 0;
	change_input(filename, node);
	if (node->_stdin == -1)
		*heredoc_broken() = true;
	signal(SIGINT, sigint_running_shell);
}
