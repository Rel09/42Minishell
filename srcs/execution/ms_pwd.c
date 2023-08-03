/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:48:47 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/02 22:31:34 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*recreation of exit as a buitin for minishell*/
/*print the current working directory */
void	ms_pwd(char **args)
{
	char	pwd[1024];

	g_last_result = 0;
	(void)args;
	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
	}
	else
	{
		perror_global("getcwd");
	}
}
