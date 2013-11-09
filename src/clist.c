#include "clist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void clist_init(/*@out@*/ struct clist *clist) {
    clist->link.next = &clist->link.next;
    clist->link.prev = &clist->link.prev;
}

void clist_destroy(/*@notnull@*/ struct dlist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    clist_for_each_safe(clist, elem) {
        if (destroy != NULL)
            destroy(elem->data);
        free(elem);
    }
}

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/*@null@*/
struct clist_elem* clist_get_head(/*@notnull@*/ const struct clist *clist) {
    return clist->link.next == &clist->link ? NULL : clist->link.next;
}

/*@null@*/
struct clist_elem* clist_get_tail(/*@notnull@*/ const struct clist *clist) {
    return clist->link.prev == &clist->link ? NULL : clist->link.next;
}

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

int clist_ins_head(/*@notnull@*/ struct dlist *clist,
                   /*@null@*/ void *data) {
    return clist_ins_next(&clist->link, data);
}

int clist_ins_next(/*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data) {
    struct clist_elem *elem_new;

    elem_new = malloc(sizeof(struct clist_elem));
    if (elem_new == NULL)
        return -1;

    elem_new->next = elem->next;
    elem_new->prev = elem;
    elem_new->next->prev = elem_new;
    elem_new->prev->next = elem_new;

    elem_new->data = data;
    return 0;
}

int clist_ins_prev(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void *data) {
    struct clist_elem *elem_new;

    elem_new = malloc(sizeof(struct clist_elem));
    if (elem_new == NULL)
        return -1;

    elem_new->next = elem;
    elem_new->prev = elem->prev;
    elem_new->next->prev = elem_new;
    elem_new->prev->next = elem_new;

    elem_new->data = data;
    return 0;
}

int clist_ins_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void *data) {
    return clist_ins_prev(&clist->link, data);
}

int dlist_rem_elem(/*@notnull@*/ struct dlist_elem *elem,
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

int clist_size(/*@notnull@*/ const struct clist *clist) {
    int count = 0;

    clist_for_each(clist, elem)
        count++;

    return count;
}
