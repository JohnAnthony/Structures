#include "cdlist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void cdlist_init(/*@out@*/ struct cdlist *cdlist) {
    cdlist->link.next = &cdlist->link;
    cdlist->link.prev = &cdlist->link;
}

void cdlist_destroy(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    cdlist_for_each_safe(cdlist, elem) {
        if (destroy != NULL)
            destroy(elem->data);
        free(elem);
    }
}

// -----------------------------------------------------------------------------
//                                 Accessors
// -----------------------------------------------------------------------------

/*@null@*/
struct cdlist_elem* cdlist_get_head(/*@notnull@*/ const struct cdlist *cdlist) {
    return cdlist->link.next == &cdlist->link ? NULL : cdlist->link.next;
}

/*@null@*/
struct cdlist_elem* cdlist_get_tail(/*@notnull@*/ const struct cdlist *cdlist) {
    return cdlist->link.prev == &cdlist->link ? NULL : cdlist->link.next;
}

// -----------------------------------------------------------------------------
//                                Manipulation
// -----------------------------------------------------------------------------

int cdlist_ins_head(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void *data) {
    return cdlist_ins_next(&cdlist->link, data);
}

int cdlist_ins_next(/*@notnull@*/ struct cdlist_elem *elem,
                   /*@null@*/ void *data) {
    struct cdlist_elem *elem_new;

    elem_new = malloc(sizeof(struct cdlist_elem));
    if (elem_new == NULL)
        return -1;

    elem_new->next = elem->next;
    elem_new->prev = elem;
    elem_new->next->prev = elem_new;
    elem_new->prev->next = elem_new;

    elem_new->data = data;
    return 0;
}

int cdlist_ins_prev(/*@notnull@*/ struct cdlist_elem *elem,
                   /*@null@*/ void *data) {
    struct cdlist_elem *elem_new;

    elem_new = malloc(sizeof(struct cdlist_elem));
    if (elem_new == NULL)
        return -1;

    elem_new->next = elem;
    elem_new->prev = elem->prev;
    elem_new->next->prev = elem_new;
    elem_new->prev->next = elem_new;

    elem_new->data = data;
    return 0;
}

int cdlist_ins_tail(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void *data) {
    return cdlist_ins_prev(&cdlist->link, data);
}

int cdlist_rem_elem(/*@notnull@*/ struct cdlist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data)) {
    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    return 0;
}

int cdlist_rem_head(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct cdlist_elem *head;

    head = cdlist_get_head(cdlist);
    if (head == NULL)
        return -1;

    return cdlist_rem_elem(head, destroy);
}

int cdlist_rem_tail(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct cdlist_elem *tail;

    tail = cdlist_get_tail(cdlist);
    if (tail == NULL)
        return -1;

    return cdlist_rem_elem(tail, destroy);
}

int cdlist_size(/*@notnull@*/ const struct cdlist *cdlist) {
    int count = 0;

    cdlist_for_each(cdlist, elem)
        count++;

    return count;
}
