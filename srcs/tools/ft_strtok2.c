/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:33:31 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 01:51:28 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_strtokhelper2(bool *swtch, uint8_t *quote, char *stock)
{
	if (*swtch && !*quote && ft_isquote(stock))
		*quote = ft_isquote(stock);
	else if (*swtch && *quote && *quote == ft_isquote(stock))
		*quote = 0;
}


