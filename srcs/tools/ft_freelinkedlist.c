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
