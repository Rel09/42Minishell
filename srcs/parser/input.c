#include "../../minishell.h"

// Init the node, here the commands/delimiter are split by strtok_monkas
static void    init_node(t_input *newNode, char *token)
{
    int     i;
    char    *commands;
    
    i = 0;
    newNode->commands = malloc((count_strtok_monkas(token) + 1) * sizeof(char *));
    if (!newNode->commands)
    {
        printf("Malloc error while trying to malloc new Node in LL\n");
        exit(1);
    }
    newNode->_stdin = STDIN_FILENO;
    newNode->_stdout = STDOUT_FILENO;
    newNode->next = NULL;
    newNode->previous = NULL;
    newNode->commands[i] = NULL;
    commands = ft_strtok_monkas(token);
    while (commands)
    {
        compute_node(commands, newNode, &i);
        commands = ft_strtok_monkas(0);
    }
    newNode->commands[i] = NULL;
}

// Init the next node in the linkedlist / linkedlisthead, to save lines
static void init_next(t_input **ll, t_input **newnode, t_input **llh)
{
    if (!(*ll))
    {
        *ll = *newnode;
        *llh = *ll;
    }
    else
    {
        (*ll)->next = *newnode;
        *ll = (*ll)->next;
    }
}

// Split the | commands
t_input *parse_input(char *input)
{
    char        *token;
    t_input     *newNode;
    t_input     *linkedlist;
    t_input     *previousNode;
    t_input     *linkedlisthead;

    linkedlist = NULL;
    previousNode = NULL;
    linkedlisthead = NULL;
    token = ft_strtok(input);
    while (token)
    {
        newNode = malloc(sizeof(t_input));
        if (!newNode)
        {
            printf("Malloc error while trying to add Node to LL\n");
            exit(1);
        }
        init_node(newNode, token);
        init_next(&linkedlist, &newNode, &linkedlisthead);
        newNode->previous = previousNode;
        previousNode = newNode;
        token = ft_strtok(NULL);
    }
    return linkedlisthead;
}
