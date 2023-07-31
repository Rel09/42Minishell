/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 00:22:25 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Change Ouput and close it if its not the default one
static void	change_output(char *file, t_input *node, bool append)
{
	int	fd;
	int	ret;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT , 0644);
	if (fd == -1)
		node->_stdout = STDOUT_FILE_NO_EXIST;
	else
	{
		ret = dup2(node->_stdout, fd);
		if (ret == -1)
			node->_stdout = STDOUT_FAILED_DUP2;
		else
		{
			if (node->_stdout != STDOUT_FILENO)
				close(node->_stdout);
			node->_stdout = fd;
		}
	}
}

// Change Input and close it if its not the default one
static void	change_input(char *file, t_input *node)
{
	int	fd;
	int	ret;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		node->_stdin = STDIN_FILE_NO_EXIST;
	else
	{
		ret = dup2(node->_stdout, fd);
		if (ret == -1)
			node->_stdin = STDIN_FAILED_DUP2;
		else
		{
			if (node->_stdin != STDIN_FILENO)
				close(node->_stdin);
			node->_stdin = fd;
		}
	}
}

// Apply the redirection
static void	do_redirect(char *type, char* file, t_input *node)
{
	if (!ft_strcmp(type, "<<"))
		change_input(file, node);
	else if (!ft_strcmp(type, ">>"))
		change_output(file, node, true);
	else if (!ft_strcmp(type, "<"))
		change_input(file, node);
	else if (!ft_strcmp(type, ">"))
		change_output(file, node, false);
}

// Backend for the Redirection and pretty much all
void	compute_node(char *command, t_input *node, int *index)
{
	if (ft_isredir(command))
		do_redirect(command, ft_strtok_monkas(0), node);

	else {
		node->commands[(*index)++] = convert_all_the_shit_and_malloc(command);
	}
}
