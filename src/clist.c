#include "clist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void clist_init(/*@out@*/ struct clist *clist) {
    cdlist->link.next = &cdlist->link;
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

int cdlist_size(/*@notnull@*/ const struct cdlist *cdlist) {
    int count = 0;

    cdlist_for_each(cdlist, elem)
        count++;

    return count;
}

/*@null@*/
struct clist_elem* clist_get_tail(/*@notnull@*/ const struct clist *clist) {
    struct clist_elem *elem;
    
    if (clist->link.next == &clist->link)
        return NULL;

    for(elem = clist->link.next; elem->next != &clist->link; elem = elem->next);

    return elem;
}

int clist_is_empty(/*@notnull@*/ const struct clist *clist) {
// ###
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
    elem->next = elem_new;
    elem_new->data = data;
    return 0;
}

int clist_ins_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void *data) {
    struct clist *elem;

    elem = clist_get_tail(clist);
    if (elem == NULL)
        return -1;

    return clist_ins_next(elem, data);
}

int clist_rem_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    if (clist_is_empty(clist))
        return -1;

    return cdlist_rem_next(clist->link, destroy);
}

int clist_rem_next(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data)) {
// ###
    return 0;
}

int cdlist_rem_tail(/*@notnull@*/ struct cdlist *cdlist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct cdlist_elem *head;

    head = cdlist_get_head(cdlist);
    if (head == NULL)
        return -1;

    return cdlist_rem_elem(head, destroy);
}
