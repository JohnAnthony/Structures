#include "dlist.h"
#include <stdlib.h>

void dlist_init(/*@out@*/ struct dlist *dlist) {
    dlist->head = NULL;
}

void dlist_destroy(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct dlist_elem *l1;
    struct dlist_elem *l2;

    if (dlist->head == NULL)
        return;
    
    // Backwards
    l1 = dlist->head->prev;
    while (l1) {
        if (destroy != NULL)
            destroy(l1->data);
        l2 = l1->prev;
        free(l1);
        l1 = l2;
    }
    
    // Forwards
    l1 = dlist->head;
    while (l1) {
        if (destroy != NULL)
            destroy(l1->data);
        l2 = l1->next;
        free(l1);
        l1 = l2;
    }
}

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

int dlist_ins_prev(/*@null@*/ struct dlist *dlist,
                   /*@notnull@*/ struct dlist_elem *elem,
                   /*@null@*/ void *data) {
    struct dlist_elem *elem_new;

    elem_new = malloc(sizeof(struct dlist_elem));
    if (elem_new == NULL)
        return -1;

    elem->prev->next = elem_new;
    elem_new->prev = elem->prev;
    elem->prev = elem_new;
    elem_new->next = elem;
    elem_new->data = data;

    return 0;
}

int dlist_rem_head(/*@notnull@*/ struct dlist *dlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct dlist_elem *elem;

    elem = dlist->head;
    if (elem == NULL)
        return -1;

    dlist->head = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    if (dlist->head != NULL)
        dlist->head->prev = NULL;
        
    return 0;
}

int dlist_rem(/*@null@*/ struct dlist *dlist,
              /*@notnull@*/ struct dlist_elem *elem,
              /*@null@*/ void (*destroy)(void *data)) {
    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;

    if (dlist != NULL && dlist->head == elem)
        dlist->head = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    return 0;
}

int dlist_size(/*@notnull@*/ const struct dlist *dlist) {
    struct dlist_elem *elem;
    int count = 0;

    if (dlist->head == NULL)
        return 0;
    
    for (elem = dlist->head; elem; elem = elem->next)         // Forwards
        count++;
    for (elem = dlist->head->prev; elem; elem = elem->prev)   // Backwards
        count++;

    return count;
}

/*@null@*/
struct dlist_elem* dlist_tail(/*@notnull@*/ const struct dlist *dlist) {
    struct dlist_elem *elem;

    if (dlist->head == NULL)
        return NULL;

    for (elem = dlist->head; elem->next; elem = elem->next);
    return elem;
}
