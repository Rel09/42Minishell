/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:08:35 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 01:14:09 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	output_redirection(t_input *input)
{
	if (input->_stdout != STDOUT_FILENO) 
	{
		if (dup2(input->_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close (input->_stdout);
		input->_stdout = STDOUT_FILENO;
	}
	return (EXIT_SUCCESS);
}

static int	input_redirection(t_input *input)
{
	if (input->_stdin != STDIN_FILENO) 
	{
		if (dup2(input->_stdin, STDIN_FILENO) == -1)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close (input->_stdin);
		input->_stdin = STDIN_FILENO;
	}
	return (EXIT_SUCCESS);
}

static int	redirection_handler(t_input *input)
{
	if (input_redirection(input))
		return (EXIT_FAILURE);
	if (output_redirection(input))
		return (EXIT_FAILURE);
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
}

/*function that receive the input struct and redirect it to handle it*/
void	command_handler(t_input *input)
{
	if (!input->next)
		single_command_handler(input);
	else
		ms_pipes(input, NULL);
	free_input(input);
	save_std(RESTORE_OUT | RESTORE_IN);
}
