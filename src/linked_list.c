#include <stdlib.h>

#include "linked_list.h"

int add(struct linked_list *list, void *val) {
    struct node *tmp = malloc(sizeof(struct node));
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
