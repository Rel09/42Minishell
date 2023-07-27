#include "../../minishell.h"


// Init the node, to save lines
static void    init_node(t_input *newNode, int index, t_parser *token)
{
    if (!newNode)
    {
        printf("Malloc error while trying to add Node to LL\n");
        exit(1);
    }
    newNode->index = index++;
    newNode->str = ft_strdup(token->str);
    newNode->flags = token->flags;
    newNode->next = NULL;
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

// Split everything with the << >> < > |*/
t_input *parse_input(char *input)
{
    int         i;
    t_parser    *token;
    t_input     *newNode;
    t_input     *linkedlist;
    t_input     *linkedlisthead;

    i = 0;
    linkedlist = 0; 
    linkedlisthead = 0;
    token = ft_sstrtok(input);
    while (token->str)
    {
        newNode = malloc(sizeof(t_input));
        init_node(newNode, i, token);
        init_next(&linkedlist, &newNode, &linkedlisthead);
        token = ft_sstrtok(0);
    }
    return (linkedlisthead);
}