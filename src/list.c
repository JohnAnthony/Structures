#include "list.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void list_init(/*@out@*/ struct list *list) {
    list->head = NULL;
}

void list_destroy(/*@notnull@*/ struct list *list,
                  /*@null@*/ void (*destroy)(void *data)) {
    list_for_each_safe(list, elem) {
        if (destroy != NULL)
            destroy(elem->data);
        free(elem);
    }
}

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/*@null@*/
struct list_elem* list_get_head(/*@notnull@*/ const struct list *list) {
    return list->head;
}

int list_get_size(/*@notnull@*/ const struct list *list) {
    int count = 0;

    list_for_each(list, elem)
        count++;

    return count;
}

/*@null@*/
struct list_elem* list_get_tail(/*@notnull@*/ const struct list *list) {
    struct list_elem *elem;

    if (list->head == NULL)
        return NULL;

    for (elem = list->head; elem->next; elem = elem->next);
    return elem;
}

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

int list_ins_head(/*@notnull@*/ struct list *list,
                  /*@null@*/ void *data) {
    struct list_elem *elem;

    elem = malloc(sizeof(struct list_elem));
    if (elem == NULL)
        return -1;
    elem->next = list->head;
    elem->data = data;
    list->head = elem;

    return 0;
}

int list_ins_tail(/*@notnull@*/ struct list *list,
                  /*@null@*/ void *data) {
    return list_ins_next(list_get_tail(list), data);
}

int list_ins_next(/*@notnull@*/ struct list_elem *elem,
                  /*@null@*/ void *data) {
    struct list_elem *elem_new;

    elem_new = malloc(sizeof(struct list_elem));
    if (elem_new == NULL)
        return -1;
    elem_new->next = elem->next;
    elem_new->data = data;
    elem->next = elem_new;

    return 0;
}

int list_rem_head(/*@notnull@*/ struct list *list,
                  /*@null@*/ void (*destroy)(void *data)) {
    struct list_elem *elem;

    elem = list->head;
    if (elem == NULL)
        return -1;

    list->head = elem->next;
    if (destroy != NULL)
        destroy(elem->data);
    free(elem);
    return 0;
}

int list_rem_tail(/*@notnull@*/ struct list *list,
                  /*@null@*/ void (*destroy)(void *data)){
    struct list_elem *elem;

    elem = list_get_head(list);
    if (elem == NULL)
        return -1;
    if (elem->next == NULL)
        return list_rem_head(list, destroy);

    while(elem->next->next != NULL)
        elem = elem->next;
    return list_rem_next(elem, destroy);
}

int list_rem_next(/*@notnull@*/ struct list_elem *elem,
                  /*@null@*/ void (*destroy)(void *data)) {
    struct list_elem *target;

    target = elem->next;
    if (target == NULL)
        return -1;

    elem->next = target->next;
    if (destroy)
        destroy(elem->data);
    free(target);
    return 0;
}
