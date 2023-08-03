/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:26:14 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/03 00:01:09 by pbergero         ###   ########.fr       */
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
		free(input);
		input = input->next;
	}
}
