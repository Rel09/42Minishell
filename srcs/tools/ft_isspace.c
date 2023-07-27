#include "../../minishell.h"

bool    ft_isspace(char c)
{
    return ((c >= 8 && c <= 12) || c == 32);
}