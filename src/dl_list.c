#include "dl_list.h"
#include <stdlib.h>

void dl_list_init(/*@out@*/ struct dl_list *dl_list) {
    dl_list->head = NULL;
}

void dl_list_destroy(struct dl_list *dl_list, void (*destroy)(void *data)) {
    struct dl_list_elem *l1;
    struct dl_list_elem *l2;

    if (dl_list->head == NULL)
        return;
    
    // Backwards
    l1 = dl_list->head->prev;
    while (l1) {
        if (destroy != NULL)
            destroy(l1->data);
        l2 = l1->prev;
        free(l1);
        l1 = l2;
    }
    
    // Forwards
    l1 = dl_list->head;
    while (l1) {
        if (destroy != NULL)
            destroy(l1->data);
        l2 = l1->next;
        free(l1);
        l1 = l2;
    }
}

int dl_list_ins_head(struct dl_list *dl_list, void *data) {
    struct dl_list_elem *elem;

    elem = malloc(sizeof(struct dl_list_elem));
    if (elem == NULL)
        return -1;
    elem->next = dl_list->head;
    elem->prev = NULL;
    elem->data = data;
    dl_list->head = elem;
    
    return 0;
}

int dl_list_ins_next(struct dl_list_elem *elem, void *data) {
    struct dl_list_elem *elem_new;

    elem_new = malloc(sizeof(struct dl_list_elem));
    if (elem_new == NULL)
        return -1;

    elem->next->prev = elem_new;
    elem_new->next = elem->next;
    elem->next = elem_new;
    elem_new->prev = elem;
    elem_new->data = data;

    return 0;
}

int dl_list_ins_prev(struct dl_list *dl_list,
                     struct dl_list_elem *elem,
                     void *data) {
    struct dl_list_elem *elem_new;

    elem_new = malloc(sizeof(struct dl_list_elem));
    if (elem_new == NULL)
        return -1;

    elem->prev->next = elem_new;
    elem_new->prev = elem->prev;
    elem->prev = elem_new;
    elem_new->next = elem;
    elem_new->data = data;

    return 0;
}

int dl_list_rem_head(struct dl_list *dl_list, void (*destroy)(void *data)) {
    struct dl_list_elem *elem;

    elem = dl_list->head;
    if (elem == NULL)
        return -1;

    dl_list->head = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    if (dl_list->head != NULL)
        dl_list->head->prev = NULL;
        
    return 0;
}

int dl_list_rem(struct dl_list *dl_list,
                struct dl_list_elem *elem,
                void (*destroy)(void *data)) {
    elem->next->prev = elem->prev;
    elem->prev->next = elem->next;

    if (dl_list != NULL && dl_list->head == elem)
        dl_list->head = elem->next;
    if (destroy)
        destroy(elem->data);
    free(elem);

    return 0;
}

int dl_list_size(const struct dl_list *dl_list) {
    struct dl_list_elem *elem;
    int count = 0;

    if (dl_list->head == NULL)
        return 0;
    
    for (elem = dl_list->head; elem; elem = elem->next)         // Forwards
        count++;
    for (elem = dl_list->head->prev; elem; elem = elem->prev)   // Backwards
        count++;

    return count;
}

struct dl_list_elem* dl_list_tail(const struct dl_list *dl_list){
    struct dl_list_elem *elem;

    if (dl_list->head == NULL)
        return NULL;

    for (elem = dl_list->head; elem->next; elem = elem->next);
    return elem;
}
