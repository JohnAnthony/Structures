#include "clist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void clist_init(/*@out@*/ struct clist *clist) {
    clist->link.next = &clist->link;
    clist->link.prev = &clist->link;
}

void clist_destroy(/*@notnull@*/ struct clist *clist,
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

int clist_ins_head(/*@notnull@*/ struct clist *clist,
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

int clist_ins_prev(/*@notnull@*/ struct clist_elem *elem,
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

int clist_rem_elem(/*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data)) {
    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    return 0;
}

int clist_rem_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct clist_elem *head;

    head = clist_get_head(clist);
    if (head == NULL)
        return -1;

    return clist_rem_elem(head, destroy);
}

int clist_rem_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct clist_elem *head;

    head = clist_get_head(clist);
    if (head == NULL)
        return -1;

    return clist_rem_elem(head, destroy);
}

int clist_size(/*@notnull@*/ const struct clist *clist) {
    int count = 0;

    clist_for_each(clist, elem)
        count++;

    return count;
}
