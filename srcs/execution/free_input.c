/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:26:14 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 00:57:45 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*to free all the allocated memory for the input and  all next input linked*/
void	free_input(t_input *input)
{
	if (!input)
		return ;
	while (input->previous)
	{
		input = input->previous;
	}
	while (input)
	{
		close_redirection(input);
		if (input->commands)
			free_double_array((void **)input->commands);
		if (input->_stdoutname)
			free(input->_stdoutname);
		if (input->_stdinname)
			free(input->_stdinname);
		free(input);
		input = input->next;
	}
}
