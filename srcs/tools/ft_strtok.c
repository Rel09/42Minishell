#include "../../minishell.h"

int     count_strtok_monkas(char *str)
{
    char    *commands;
    char    *temp;
    int     i;
    
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

char    *ft_strtok(char *str)
{
    static char *output;
    static char *stock;
    bool        swtch;
    uint8_t     quote;

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
        if (swtch && !quote && ft_isquote(stock))
            quote = ft_isquote(stock);
        else if (swtch && quote && quote == ft_isquote(stock))
            quote = 0;
        stock++;
    }
    return (output);
}

char    *ft_strtok_monkas(char *str)
{
    static char *output;
    static char *stock;
    bool        swtch;
    uint8_t     quote;
    static char last_char;

    output = 0;
    quote = 0;
    swtch = false;
    if (str)
        stock = str;

    if (last_char)
    {
        *stock = last_char;
        last_char = 0;
    }

    while (ft_isspace(*stock))
        stock++;

    // If this char is a Delimiter, Split
    if (ft_isredir(stock))
    {
        if (!ft_strncmp(stock, "<<", 2))
        {
            stock += 2;
            return "<<";
        }
        else if (!ft_strncmp(stock, ">>", 2))
        {
            stock += 2;
            return ">>";
        }
        else if (!ft_strncmp(stock, "<", 1))
        {
            stock++;
            return "<";
        }
        else if (!ft_strncmp(stock, ">", 1))
        {
            stock++;
            return ">";
        }
    }
    while (*stock)
    {
    
        // Record Start
        if (!swtch && !(ft_isspace(*stock)))
        {
            swtch = true;
            output = stock;
        }

        // Record Stop
        else if (swtch && !quote && ft_isspace(*stock))
        {
            *stock = 0;
            stock++;
            break;
        }
        
        // Special Delimiters
        if (swtch && !quote && ft_isredir(stock))
        {
            last_char = *stock;
            *stock = 0;
            break;
        }
        
        // Quote Start
        if (swtch && !quote && ft_isquote(stock))
            quote = ft_isquote(stock);

        // Quote End
        else if (swtch && quote && quote == ft_isquote(stock))
            quote = 0;

        stock++;
    }

    return (output);
}
