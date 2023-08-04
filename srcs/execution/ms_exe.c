/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:24:02 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 01:51:40 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*return the part of the env that contain the information about PATH*/
static char	*get_env_path(void)
{
	char	*str;

	str = getenv("PATH"); // need to change for the new env
	return (str);
}

/*build an absolute path using "path" + "/" + "name" */
static char	*path_builder(char *path, char *exe_name)
{
	char	*absolute_path;
	size_t	pathsize;
	size_t	exesize;

	pathsize = ft_strlen(path);
	exesize = ft_strlen(exe_name);
	absolute_path = malloc(pathsize + exesize + 2);
	if (!absolute_path)
		return (NULL);
	ft_bzero(absolute_path, pathsize + exesize + 2);
	ft_strlcat(absolute_path, path, pathsize + 1);
	ft_strlcat(absolute_path, "/", pathsize + 2);
	ft_strlcat(absolute_path, exe_name, pathsize + exesize + 2);
	return (absolute_path);
}

/*search the environment variable path to find if the command is there*/
/*return absolute path if found return NULL if not found*/
static char	*search_exe_in_path_env(char **args)
{
	char	**split_path;
	char	*build_path;
	int		i;

	split_path = ft_split(get_env_path(), ':');
	i = 0;
	while (split_path[i])
	{
		build_path = path_builder(split_path[i], args[0]);
		if (access(build_path, F_OK | X_OK) == 0)
		{
			free_double_array((void **) split_path);
			return (build_path);
		}
		free (build_path);
		i++;
	}
	free_double_array((void **) split_path);
	return (NULL);
}

static void	exe_command(char **args)
{
	char	*path;

	save_std(CLOSE_IN | CLOSE_OUT);
	path = args[0];
	if (access(path, F_OK | X_OK))
		execve(path, args, NULL); //change the NULL for getenv
	path = search_exe_in_path_env(args);
	if (path)
	{
		execve(path, args, NULL); //change the NULL for getenv
		free(path);
	}
}

/*Execute a exe by vertue of fork.*/
/*Parent is main proccess Child is exe*/
void	ms_exe(t_input *input)
{
	int		pid;

	pid = fork();
	if (pid < 0)
	{
		perror_global("fork :");
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exe_command(input->commands);
		perror_global("exe");
		clean_static_memory();
		exit (g_last_result);
	}
	else
		waitpid(pid, &g_last_result, 0);
}
