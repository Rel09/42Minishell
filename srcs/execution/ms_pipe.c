/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:35:43 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/02 22:31:32 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*dup2 the open fd from the pipe fonction and calls the single command handler*/
/*to execute the command*/
static void	dup_fd_chain_child(t_fd_chain *fd_chain, t_input *input,
	t_fd_chain *fd_head, t_input *input_head)
{
	int	fd;

	fd = 0;
	close(fd_chain->fd[0]);
	dup2(fd_chain->fd[1], STDOUT_FILENO);
	close(fd_chain->fd[1]);
	save_std(CLOSE_IN | CLOSE_OUT);
	close_unused_fd(fd_chain->next);
	if (fd == -1)
		pipeline_error_cleaning (input_head, fd_head, NULL, true);
	single_command_handler(input);
	if (fd > 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	pipeline_error_cleaning (input_head, fd_head, NULL, true);
}

/*dup2() the entire fd chain open by the pipe fonction to create a pipeline*/
/*the fonction is recusirve and called itself using a increment variable*/
/*to know how many next it need to do */
static int	dup_fd_chain(t_fd_chain *fd_chain, t_input *input,
	t_fd_chain *fd_head, t_input *input_head)
{
	if (!fd_chain || !input)
		return (EXIT_SUCCESS);
	fd_chain->pid = fork();
	if (fd_chain->pid < 0)
	{
		pipeline_error_cleaning(NULL, fd_chain, "fork", false);
		return (EXIT_FAILURE);
	}
	else if (fd_chain->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup_fd_chain_child(fd_chain, input, fd_chain, input_head);
	}
	close(fd_chain->fd[1]);
	dup2(fd_chain->fd[0], STDIN_FILENO);
	close(fd_chain->fd[0]);
	return (dup_fd_chain(fd_chain->next, input->next, fd_head, input_head));
}

static void	wait_for_my_child(t_fd_chain *fd_chain)
{
	while (fd_chain)
	{
		waitpid(fd_chain->pid, &g_last_result, 0);
		fd_chain = fd_chain->next;
	}
}

static void	last_command(t_input *input, t_fd_chain *fd_chain)
{
	int			pid;
	t_input		*head;

	pid = fork();
	if (pid < 0)
	{
		perror_global("fork");
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		head = input;
		while (input->next)
			input = input->next;
		save_std(CLOSE_IN | CLOSE_OUT);
		single_command_handler(input);
		pipeline_error_cleaning(head, NULL, NULL, true);
	}
	wait_for_my_child(fd_chain);
	waitpid(pid, &g_last_result, 0);
}

/*recreation of the pipe ' | ' for the minishell project */
/*only the parent process does return to this function after the forks*/
/**/
void	ms_pipes(t_input *input, t_fd_chain *fd_chain)
{
	t_input		*tmp;

	save_std(SAVE_IN | SAVE_OUT);
	fd_chain = open_new_pipe(fd_chain);
	if (!fd_chain)
		return ;
	tmp = input->next;
	while (tmp && tmp->next)
	{
		fd_chain = open_new_pipe(fd_chain);
		if (!fd_chain)
			return ;
		tmp = tmp->next;
	}
	if (dup_fd_chain(fd_chain, input, fd_chain, input))
		return ;
	close_fd_chain(fd_chain);
	last_command(input, fd_chain);
	free_fd_chain(fd_chain);
	save_std(CLOSE_IN | CLOSE_OUT | RESTORE_IN | RESTORE_OUT);
}
