#include "../../minishell.h"

// Tell sstrktok to skip one or two char, depending on the delimiter
// it also skip the second char, 
// its not really needed since strtok will skip it but yea
static void sstrtok_helper(char **stock) {
    if (is_delimiter(*stock) == 4 || is_delimiter(*stock) == 5)
	{
		(*stock)[0] = 0;
		(*stock)[1] = 0;
		*stock += 2;
	}
	else
	{
		(*stock)[0] = 0;
		*stock += 1;
	}
}

// Split the entire thing
t_parser	*ft_sstrtok(char *str)
{
	static t_parser	output;
	static char		*stock;
	static char		*head;
	bool			swltch;
	uint8_t			quote;

	swltch = false;
	ft_bzero(&output, sizeof(output));
	if (str)
	{
		stock = ft_strdup(str);
		head = stock;
		if (is_delimiter(stock))
			set_flags(&output.flags, is_delimiter(stock), false);
	}
	while (*stock)
	{
		if (!swltch && !is_delimiter(stock))
		{
			swltch = true;
			output.str = stock;
		}
		else if (swltch && quote == 0 && is_delimiter(stock))
		{
			set_flags(&output.flags, is_delimiter(stock), true);
			sstrtok_helper(&stock);
			break ;
		}
		if (swltch && quote == 0 && is_quote(stock))
			quote = is_quote(stock);
		else if (swltch && quote != 0 && quote == is_quote(stock))
			quote = 0;
		stock++;
	}
	if (!output.str && head)
		free(head);
	return (&output);
}
