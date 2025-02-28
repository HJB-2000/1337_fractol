#include "fractol.h"
t_garbage *new_node(void *ptr, int i)
{
    t_garbage *new_node;

    new_node = malloc(sizeof(t_garbage));
    if (!new_node)
        return (NULL);
    new_node->_malloc = ptr;
    new_node->index = i;
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
    tmp = *list;
    *list = (*list)->next->next;
    mlx_destroy_window(tmp->_malloc, tmp->next->_malloc);
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
    static int i = 0;
    void *instant;
    t_garbage *new;

    if (free_flag)
    {
        for(t_garbage *tmp = head; tmp;tmp = tmp->next)
            printf("%p || index = %d\n", tmp, tmp->index);
        // return (_free(&head), NULL);
    }
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
    new = new_node(instant, i);
    i++;
    if (!new)
        return (free(instant), NULL);
    add_node(&head, new);
    return (instant);
}
