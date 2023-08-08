/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:55:06 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/08 06:00:48 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Allow us to exit the HEREDOC if signal is called
int	*heredoc_pid(void)
{
	static int	heredoc_pid;

	return (&heredoc_pid);
}

// Create a fork during HEREDOC so we can kill it while its running
static void	heredoc_fork(char **input, char *keyword, int fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		while (ft_strcmp(*input, keyword))
		{
			free(*input);
			*input = NULL;
			*input = readline("> ");
			if (ft_strcmp(*input, keyword))
			{
				ft_putstr_fd(convert_all_args_hd(*input), fd);
				ft_putstr_fd("\n", fd);
			}
		}
		exit(0);
	}
	else
	{
		(*heredoc_pid()) = pid;
		waitpid(pid, NULL, 0);
	}
}

// If Heredoc get interrupted, close all open fds;
void	heredoc_cleanup(t_input	*node)
{
	while (node)
	{
		if (node->_stdin != STDIN_FILENO)
			close(node->_stdin);
		if (node->_stdin != STDOUT_FILENO)
			close(node->_stdout);
		node = node->next;
	}
}

// Heredoc Entry
void	heredoc(char *keyword, t_input *node)
{
	char	*input;
	char	*filename;
	int		fd;

	input = malloc(1);
	*input = 0;
	filename = get_uniquefilename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, sigint_running_heredoc);
	heredoc_fork(&input, keyword, fd);
	signal(SIGINT, sigint_running_shell);
	if (*heredoc_pid() != HEREDOC_KILLED)
		(*heredoc_pid()) = 0;
	close(fd);
	free(input);
	change_input(filename, node);
}
