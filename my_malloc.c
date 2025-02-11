#include "fractol.h"
t_garbage *new_node(void *ptr)
{
    t_garbage *new_node;

    new_node = malloc(sizeof(t_garbage));
    if (!new_node)
        return (NULL);
    new_node->_malloc = ptr;
    new_node->next = NULL;
    return (new_node);
} 
void add_node(t_garbage **head, t_garbage *new_node)
{
    if (!*head)
    {
        (*head) = new_node;
        return;
    }
    t_garbage *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}
void _free(t_garbage **list)
{
    t_garbage *tmp;

    while (*list)
    {
        tmp = *list;
        *list = (*list)->next;
        free(tmp->_malloc);
        free(tmp);
    }
    *list = NULL;
}
void *_malloc(size_t size, void *ptr, bool free_flag, bool error_flag)
{
    static t_garbage *head = NULL;
    void *instant;
    t_garbage *new;

    if (free_flag)
        return (_free(&head), NULL);
    else if (!ptr)
    {
        instant = malloc(size);
        if (!instant)
            error_flag = true;
    }
    else
        instant = ptr;
    if (error_flag)
    {
        _free(&head);
        perror("we faced a problem");
        exit(EXIT_FAILURE);
    }
    new = new_node(instant);
    if (!new)
        return (free(instant), NULL);
    add_node(&head, new);
    return (instant);
}
