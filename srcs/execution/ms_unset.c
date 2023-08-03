/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 05:56:50 by dpotvin           #+#    #+#             */
/*   Updated: 2023/08/02 23:00:35 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ms_unset(char **args)
{
	char	temp[500];

	ft_bzero(temp, 500);
	(void)args;
	/*if (get_env_arg(temp))
		remove_env_arg(temp);*/ //need to use our env
}
