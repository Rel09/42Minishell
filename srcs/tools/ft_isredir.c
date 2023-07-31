/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:24 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 20:33:25 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool  ft_isredir(char *str)
{
    int     i;
    char    *delimiters[4];

    i = -1;
    delimiters[0] = "<<";
    delimiters[1] = ">>";
    delimiters[2] = "<";
    delimiters[3] = ">";
    while (++i < 4)
    {
        if (!ft_strncmp(str, delimiters[i], ft_strlen(delimiters[i])))
            return true;
    }
    return false;
}
