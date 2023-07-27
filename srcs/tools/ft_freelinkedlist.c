#include "../../minishell.h"

// Free t_input Linkedlist
void free_input(t_input *head)
{
    t_input *current;
    t_input *next;

    current = head;
    while (current)
    {
        next = current->next;
        if (current->str)
            free(current->str);
        free(current);
        current = next;
    }
}