#include "../../minishell.h"

// Free t_input Linkedlist
void free_input(t_input *head)
{
    t_input *current;
    t_input *next;
    int     i;

    current = head;
    while (current)
    {
        next = current->next;
        i = -1;
        while (current->commands[++i])
        {
            if (current->commands[i])
                free(current->commands[i]);
        }
        free(current);
        current = next;
    }
}