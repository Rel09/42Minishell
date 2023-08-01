/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:47:30 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 21:32:53 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Init the node, here the commands/delimiter are split by strtok_monkas
static void	init_node(t_input *newNode, char *token)
{
	int		i;
	int		len;
	char	*commands;

	i = 0;
	len = count_strtok_monkas(token) + 1;
	newNode->commands = malloc(len * sizeof(char *));
	newNode->_stdin = STDIN_FILENO;
	newNode->_stdout = STDOUT_FILENO;
	newNode->next = NULL;
	newNode->previous = NULL;
	commands = ft_strtok_monkas(token);
	while (commands)
	{
		compute_node(commands, newNode, &i);
		commands = ft_strtok_monkas(0);
	}
	newNode->commands[len - 1] = 0;
}

// Init the next node in the linkedlist / linkedlisthead, to save lines
static void	init_next(t_input **ll, t_input **newnode, t_input **llh)
{
	if (!(*ll))
	{
		*ll = *newnode;
		*llh = *ll;
	}
	else
	{
		(*ll)->next = *newnode;
		*ll = (*ll)->next;
	}
}

// Split the | commands
t_input	*parse_input(char *input)
{
	char		*token;
	t_input		*newnode;
	t_input		*linkedlist;
	t_input		*previousnode;
	t_input		*linkedlisthead;

	linkedlist = NULL;
	previousnode = NULL;
	linkedlisthead = NULL;
	token = ft_strtok(input);
	while (token)
	{
		newnode = malloc(sizeof(t_input));
		if (!newnode)
		{
			printf("Malloc error while trying to add Node to LL\n");
			exit(1);
		}
		init_node(newnode, token);
		init_next(&linkedlist, &newnode, &linkedlisthead);
		newnode->previous = previousnode;
		previousnode = newnode;
		token = ft_strtok(NULL);
	}
	return (linkedlisthead);
}
