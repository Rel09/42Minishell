/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:08:35 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/03 00:28:58 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	redirection_handler(t_input *input)
{
	if (input->_stdout != STDOUT_FILENO) 
	{
		if (dup2(input->_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		save_std(SAVE_OUT);
		close (input->_stdout);
		input->_stdout = STDOUT_FILENO;
	}
	if (input->_stdin != STDIN_FILENO) 
	{
		if (dup2(input->_stdin, STDIN_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		save_std(SAVE_IN);
		close (input->_stdin);
		input->_stdin = STDIN_FILENO;
	}
	return (EXIT_SUCCESS);
}

/*handle singular command without any type of pipe/redirection */
void	single_command_handler(t_input *input)
{
	if (redirection_handler(input))
		return ;
	if (!ft_strcmp(input->commands[0], "echo"))
		ms_echo(input->commands);
	else if (!ft_strcmp(input->commands[0], "cd"))
		ms_cd(input->commands);
	else if (!ft_strcmp(input->commands[0], "exit"))
		ms_exit(input);
	else if (!ft_strcmp(input->commands[0], "pwd"))
		ms_pwd(input->commands);
	else if (!ft_strcmp(input->commands[0], "env"))
		ms_env(input->commands);
	else if (!ft_strcmp(input->commands[0], "unset"))
		ms_unset(input->commands);
	else 
		ms_exe(input);
	save_std(CLOSE_OUT | RESTORE_OUT | CLOSE_IN | RESTORE_IN);
}

/*function that receive the input struct and redirect it to handle it*/
void	command_handler(t_input *input)
{
	if (!input->next)
		single_command_handler(input);
	else
		ms_pipes(input, NULL);
	free_input(input);
	save_std(CLOSE_OUT | RESTORE_OUT | CLOSE_IN | RESTORE_IN);
}
