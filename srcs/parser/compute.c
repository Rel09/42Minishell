/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/03 00:21:00 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Change Ouput and close it if its not the default one
static void	change_output(char *file, t_input *node, bool append)
{
	if (node->_stdout != STDOUT_FILENO)
		close(node->_stdout);
	if (append)
		node->_stdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		node->_stdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

// Change Input and close it if its not the default one
static void	change_input(char *file, t_input *node)
{
	if (node->_stdin != STDIN_FILENO)
		close(node->_stdin);
	node->_stdin = open(file, O_RDONLY);
}

// Apply the redirection
static void	do_redirect(char *type, char *file, t_input *node)
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
	else
		node->commands[(*index)++] = convert_all_the_shit_and_malloc(command);
}
