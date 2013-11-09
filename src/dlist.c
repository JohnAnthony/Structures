#include "dlist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void dlist_init(/*@out@*/ struct dlist *dlist) {
    dlist->head = NULL;
}

void dlist_destroy(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    dlist_for_each_safe(dlist, elem) {
        if (destroy != NULL)
            destroy(elem->data);
        free(elem);
    }
}

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/*@null@*/
struct dlist_elem* dlist_get_head(/*@notnull@*/ const struct dlist *dlist) {
    return dlist->head;
}

/*@null@*/
struct dlist_elem* dlist_get_tail(/*@notnull@*/ const struct dlist *dlist) {
    struct dlist_elem *elem;

    for (elem = dlist->head; elem->next; elem = elem->next);
    return elem;
}

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

int dlist_ins_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void *data) {
    struct dlist_elem *elem;

    elem = malloc(sizeof(struct dlist_elem));
    if (elem == NULL)
        return -1;
    elem->next = dlist->head;
    elem->prev = NULL;
    elem->data = data;
    dlist->head = elem;

    return 0;
}

int dlist_ins_next(/*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data) {
    struct dlist_elem *elem_new;

    elem_new = malloc(sizeof(struct dlist_elem));
    if (elem_new == NULL)
        return -1;

    elem->next->prev = elem_new;
    elem_new->next = elem->next;
    elem->next = elem_new;
    elem_new->prev = elem;
    elem_new->data = data;

    return 0;
}

int dlist_ins_prev(/*@notnull@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data) {
    struct dlist_elem *elem_new;

    elem_new = malloc(sizeof(struct dlist_elem));
    if (elem_new == NULL)
        return -1;

    if (dlist->head == elem)
        dlist->head = elem_new;

    elem->prev->next = elem_new;
    elem_new->prev = elem->prev;
    elem->prev = elem_new;
    elem_new->next = elem;
    elem_new->data = data;

    return 0;
}

int dlist_ins_tail(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void *data) {
    return dlist_ins_next(dlist_get_tail(dlist), data);
}

int dlist_rem_elem(/*@notnull@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data)) {
    if (elem->next)
        elem->next->prev = elem->prev;
    if (elem->prev)
        elem->prev->next = elem->next;

    if (dlist->head == elem)
        dlist->head = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    return 0;
}

int dlist_rem_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct dlist_elem *elem;

    elem = dlist->head;
    if (elem == NULL)
        return -1;

    dlist->head = elem->next;
    if (dlist->head != NULL)
        dlist->head->prev = NULL;

    if (destroy)
        destroy(elem->data);
    free(elem);
    return 0;
}

int dlist_rem_tail(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    return dlist_rem_elem(dlist, dlist_get_tail(dlist), destroy);
}

int dlist_size(/*@notnull@*/ const struct dlist *dlist) {
    struct dlist_elem *elem;
    int count = 0;

    for (elem = dlist->head; elem; elem = elem->next)
        count++;
    return count;
}
