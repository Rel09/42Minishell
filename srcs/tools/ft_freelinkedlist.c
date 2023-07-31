/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelinkedlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:06 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/30 20:33:07 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Free t_input Linkedlist
void free_input(t_input *head)
{
    int     i;
    t_input *current;
    t_input *next;

    current = head;
    while (current)
    {
        next = current->next;
        i = 0;
        while (current->commands[i])
        {
            free(current->commands[i]);
            i++;
        }
        free(current);
        current = next;
    }
    head = 0;
}
