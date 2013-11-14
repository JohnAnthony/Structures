#include "clist.h"
#include <stdlib.h>

// -----------------------------------------------------------------------------
//                                 Management
// -----------------------------------------------------------------------------

void clist_init(/*@out@*/ struct clist *clist) {
    clist->link.next = &clist->link;
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
    return clist_is_empty(clist) ? NULL : clist->link.next;
}

int clist_get_size(/*@notnull@*/ const struct clist *clist) {
    int count = 0;

    clist_for_each(clist, elem)
        count++;

    return count;
}

/*@null@*/
struct clist_elem* clist_get_tail(/*@notnull@*/ const struct clist *clist) {
    struct clist_elem *elem;
    
    if (clist_is_empty(clist))
        return NULL;

    for(elem = clist->link.next; elem->next != &clist->link; elem = elem->next);

    return elem;
}

int clist_is_empty(/*@notnull@*/ const struct clist *clist) {
    return clist->link.next == &clist->link;
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
    struct clist_elem *elem;

    elem = clist_get_tail(clist);
    if (elem == NULL)
        return -1;

    return clist_ins_next(elem, data);
}

int clist_rem_head(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    if (clist_is_empty(clist))
        return -1;

    return clist_rem_next(clist, &clist->link, destroy);
}

int clist_rem_next(/*@notnull@*/ struct clist *clist,
                   /*@notnull@*/ struct clist_elem *elem,
                   /*@null@*/ void (*destroy)(void *data)) {
    if (clist_is_empty(clist))
        return -1;

    elem->next->next = elem;
    elem->next = elem->next->next;

    if (destroy != NULL)
        destroy(elem->next->data);
    free(elem->next);
    
    return 0;
}

int clist_rem_tail(/*@notnull@*/ struct clist *clist,
                   /*@null@*/ void (*destroy)(void *data)) {
    struct clist_elem *pretail;

    if (clist_is_empty(clist))
        return -1;

    for(pretail = clist->link.next;
        pretail->next->next != &clist->link;
        pretail = pretail->next);
    return clist_rem_next(clist, pretail, destroy);
}
