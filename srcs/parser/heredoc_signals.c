/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 02:07:35 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/09 02:30:23 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Allow us to exit the HEREDOC if signal is called
int	*heredoc_pid(void)
{
	static int	heredoc_pid;

	return (&heredoc_pid);
}

// Allow us to close fd if signal is called
int	*heredoc_fd(void)
{
	static int	heredoc_fd;

	return (&heredoc_fd);
}

// Allow us to free the linkedlist in heredoc
t_input	**heredoc_ll(void)
{
	static t_input	*ll;

	return (&ll);
}

// Norminette on heredoc
void	free_garbage(t_input *ll, char **input, int fd)
{
	free_input(ll);
	clean_static_memory();
	free(*input);
	close(fd);
}
