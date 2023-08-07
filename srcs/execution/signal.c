/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:17:26 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/06 22:17:11 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_running_shell(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
}

void	sigint_interactive(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_replace_line("", 0);
	rl_forced_update_display();
}

int	intercept_signals(void)
{
	signal(SIGINT, sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
/*
int	get_file_type(char *path)
{
	struct stat	path_stat;

	if (!stat(path, &path_stat))
	{
		if (S_ISREG(path_stat.st_mode))
		{
			if (path_stat.st_mode & S_IXUSR)
			{
				return (EXE);
			}
			else
			{
				g_last_result = COMMAND_NOT_FOUND_EXIT;
				return (NORMAL_FILE);
			}
		}
		else if (S_ISDIR(path_stat.st_mode))
		{
			g_last_result = IS_DIR_EXIT;
			return (DIR);
		}
	}
	g_last_result = COMMAND_NOT_FOUND_EXIT;
	return (NORMAL_FILE);
}
*/

int	get_file_type(char *path)
{
	struct stat	path_stat;

	if (!stat(path, &path_stat))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			g_last_result = IS_DIR_EXIT;
			return (IS_DIR_EXIT);
		}
		else if (S_ISREG(path_stat.st_mode) && !(path_stat.st_mode & S_IXUSR))
		{
			g_last_result = COMMAND_NOT_FOUND_EXIT;
			return (NORMAL_FILE);
		}
		else
			return (EXE);
	}
	g_last_result = COMMAND_NOT_FOUND_EXIT;
	return (NORMAL_FILE);
}
