#include "list.h"
#include <stdlib.h>

void list_init(struct list *list) {
    list->head = NULL;
}

void list_destroy(struct list *list, void (*destroy)(void *data)) {
    struct list_elem *l1;
    struct list_elem *l2;

    l1 = list->head;
    while (l1) {
        if (destroy)
            destroy(l1->data);
        l2 = l1->next;
        free(l1);
        l1 = l2;
    }
}

int list_ins_head(struct list *list, const void *data) {
    struct list_elem *elem;

    elem = malloc(sizeof(struct list_elem));
    if (elem == NULL)
        return -1;
    elem->next = list->head;
    list->head = elem;
    
    return 0;
}

int list_ins_next(struct list_elem *elem, const void *data) {
    struct list_elem *elem_new;

    elem_new = malloc(sizeof(struct list_elem));
    if (elem_new == NULL)
        return -1;
    elem_new->next = elem->next;
    elem->next = elem_new;

    return 0;
}

int list_rem_head(struct list *list, void **data) {
    struct list_elem *elem;

    elem = list->head;
    if (elem == NULL)
        return -1;

    list->head = elem->next;
    *data = elem->data;
    free(elem);
    return 0;
}

int list_rem_next(struct list_elem *elem, void **data) {
    struct list_elem *target;

    target = elem->next;
    if (target == NULL)
        return -1;

    elem->next = target->next;
    *data = target->data;
    free(target);
    return 0;
}

int list_size(struct list *list) {
    struct list_elem *elem;
    int count = 0;

    for (elem = list->head; elem; elem = elem->next)
        count++;

    return count;
}

struct list_elem* list_tail(struct list *list) {
    struct list_elem *elem;

    if (list->head == NULL)
        return NULL;

    for (elem = list->head; elem->next; elem = elem->next);
    return elem;
}
