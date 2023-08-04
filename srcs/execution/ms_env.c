/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 23:00:32 by pbergero          #+#    #+#             */
/*   Updated: 2023/08/04 00:07:03 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sort_strings(char ***strings)
{
	char		*temp;
	char		**strings_ptr;
	int16_t		i;
	int16_t		j;
	uint16_t	num_strings;

	num_strings = 0;
	strings_ptr = *strings;
	while (strings_ptr[num_strings])
		num_strings++;
	i = -1;
	j = -1;
	while (++i < num_strings - 1)
	{
		while (++j < num_strings - i - 1)
		{
			if (ft_strcmp(strings_ptr[j], strings_ptr[j + 1]) > 0)
			{
				temp = strings_ptr[j];
				strings_ptr[j] = strings_ptr[j + 1];
				strings_ptr[j + 1] = temp;
			}
		}
	}
}

void	ms_env(char **args)
{
	char	**env;

	(void)args;
	show_env();
}
