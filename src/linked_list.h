#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct node {
    void *val;
    struct node *next;
};

struct linked_list {
    struct node *head;
};

int add(struct linked_list *list, void *val);

#endif /* _LINKED_LIST_H */
