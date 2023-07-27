#include "../../minishell.h"

// Remove leading and trailing whitespace from a string
// This also free the input string, so be aware
char *ft_trimstr(char *str)
{
    int     len;
    char    *newstr;
    int     end_index;

    if (!str) {
        printf("ERROR WTF\n");
        return str;
    }
    while (ft_isspace(*str))
        str++;
    len = ft_strlen(str);
    end_index = len - 1;
    while (end_index >= 0 && ft_isspace(str[end_index]))
        end_index--;
    newstr = malloc(((end_index + 1) + 1));
    if (!newstr)
    {
        printf("Malloc error while Trimming Input!\n");
        exit(1);
    }
    ft_strncpy(newstr, str, (end_index + 1));
    newstr[(end_index + 1)] = 0;
    return newstr;
}