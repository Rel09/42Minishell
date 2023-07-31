/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:33:57 by dpotvin           #+#    #+#             */
/*   Updated: 2023/07/31 01:49:51 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_strtok_monkas(char *str)
{
    char	*commands;
    char	*temp;
    int		i;

	i = 0;
	temp = ft_strdup(str);
	commands = ft_strtok_monkas(temp);
	while (commands)
	{
		i++;
		commands = ft_strtok_monkas(NULL);
	}
	free (temp);
	return (i);
}

char	*ft_strtok(char *str)
{
    static char	*output;
    static char	*stock;
    bool		swtch;
    uint8_t		quote;

	output = 0;
	quote = 0;
	swtch = false;
	if (str)
		stock = str;
	while (*stock)
	{
		if (!swtch && !(*stock == '|'))
		{
			swtch = true;
			output = stock;
		}
		else if (swtch && !quote && *stock == '|')
		{
			*stock = 0;
			stock++;
			break;
		}
		ft_strtokhelper2(&swtch, &quote, stock);
		stock++;
	}
	return (output);
}

static char	*return_redirtype(char	**stock)
{
	if (!ft_strncmp(*stock, "<<", 2))
	{
		(*stock) += 2;
		return "<<";
	}
	else if (!ft_strncmp(*stock, ">>", 2))
	{
		(*stock) += 2;
		return ">>";
	}
	else if (!ft_strncmp(*stock, "<", 1))
	{
		(*stock)++;
		return "<";
	}
	else
	{
		(*stock)++;
		return ">";
	}
}

void	strtok_helper(char *str, char **stock, char *last_char)
{
	if (str)
		*stock = str;
	if (*last_char != '\0')
	{
		**stock = *last_char;
		*last_char = '\0';
	}
	while (**stock != '\0' && isspace(**stock))
		(*stock)++;
}

char	*ft_strtok_monkas(char *str)
{
    static char	*output;
    static char	*stock;
    bool		swtch;
    uint8_t		quote;
    static char	last_char;

	output = 0;
	quote = 0;
	swtch = false;
	strtok_helper(str, &stock, &last_char);
    if (ft_isredir(stock))
		return (return_redirtype(&stock));
    while (*stock)
    {
        if (!swtch && !(ft_isspace(*stock)))
        {
            swtch = true;
            output = stock;
        }
        else if (swtch && !quote && ft_isspace(*stock))
        {
            *stock = 0;
            stock++;
            break;
        }
        if (swtch && !quote && ft_isredir(stock))
        {
            last_char = *stock;
            *stock = 0;
            break;
        }
		ft_strtokhelper2(&swtch, &quote, stock);
        stock++;
    }
    return (output);
}
