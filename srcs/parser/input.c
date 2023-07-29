#include "../../minishell.h"


// Init the node, here the << >> < > are split by strtok_monkas
static void    init_node(t_input *newNode, char *token)
{
    char *commands;
    
    if (!newNode)
    {
        printf("Malloc error while trying to add Node to LL\n");
        exit(1);
    }
    
    commands = ft_strtok_monkas(token);
    while (commands)
    {
        printf("[%s] ", commands);

        commands = ft_strtok_monkas(0);
        // build 2d array with those here
    }
    printf("\n");
    
    newNode->_stdin = 0;
    newNode->_stdout = 1;
    newNode->next = NULL;
    newNode->previous = NULL;
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
        init_node(newNode, token);
        init_next(&linkedlist, &newNode, &linkedlisthead);
        newNode->previous = previousNode;
        previousNode = newNode;
        token = ft_strtok(NULL);
        }
    return linkedlisthead;
}
