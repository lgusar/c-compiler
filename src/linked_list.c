#include <stdlib.h>

#include "linked_list.h"

struct linked_list *linked_list_init() {
    struct linked_list *list = malloc(sizeof(struct linked_list));
    list->head = NULL;

    return list;
}

int linked_list_add(struct linked_list *list, void *val) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp->next = NULL;
    tmp->val = val;
    if (list->head == NULL) {
        list->head = tmp;

        return 0;
    }

    struct node *p = list->head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = tmp;

    return 0;
}
