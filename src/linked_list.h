#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct node {
    void *val;
    struct node *next;
};

struct linked_list {
    struct node *head;
};

struct linked_list *linked_list_init();

int linked_list_add(struct linked_list *list, void *val);

#endif /* _LINKED_LIST_H */
