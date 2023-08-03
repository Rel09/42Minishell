/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:09:08 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/02 22:36:49 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function that add a new entry in Env. Str is the value, 
// =and Prefix is the value name
// strlcat_addtoenv("\PATH\TO\HEAVEN", "JESUSPATH=");

void	perror_global(char *str)
{
	perror(str);
	g_last_result = EXIT_FAILURE;
}
/*
static void	strlcat_addtoenv(const char *str, const char *prefix)
{
	char	*temp;

	temp = malloc(ft_strlen(str) + ft_strlen(prefix) + 1);
	if (!temp)
	{
		perror_global("Malloc error [ ms_cd.c -> strlcat_addtoenv 0]");
		return ;
	}
	ft_bzero(temp, ft_strlen(str) + ft_strlen(prefix));
	ft_strlcat(temp, prefix, ft_strlen(prefix) + 1);
	ft_strlcat(temp, str, ft_strlen(str) + ft_strlen(prefix) + 1);
	add_env_arg(temp);
	free(temp);
}

// Update ENV path after changing folder
static void	update_env_path(void)
{
	char	*oldpwd;
	char	*buffer;

	oldpwd = get_env_arg("OLDPWD=");
	if (oldpwd)
		remove_env_arg("OLDPWD=");
	oldpwd = get_env_arg("PWD=");
	if (oldpwd)
	{
		strlcat_addtoenv(oldpwd + 4, "OLDPWD=");
		buffer = malloc(1024);
		if (!buffer)
		{
			perror_global("Malloc error [ ms_cd.c -> update_env_path 0]");
			return ;
		}
		remove_env_arg("PWD=");
		getcwd(buffer, 1024);
		strlcat_addtoenv(buffer, "PWD=");
		free(buffer);
	}
	else
		perror_global("No [PWD=] ? ms_cd -> update_env_path()");
}
*/

/*recreation of cd as a buitin for minishell*/
/*change current directory for the specified one in the input.arg*/
/*if input.arg == NULL redirect to root*/
void	ms_cd(char **args)
{
	char	*path;

	g_last_result = EXIT_SUCCESS;
	path = args[1];
	if (!args[1])
		path = "/";
	if (chdir(path) == -1)
	{
		perror_global("cd:");
		return ;
	}
	//update_env_path(); need to redo that part with the new env 
}
