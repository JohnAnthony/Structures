#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_dlist(void) {
// -----------------------------------------------------------------------------
// void dlist_init(/*@out@*/ struct dlist *dlist);
// -----------------------------------------------------------------------------
// void dlist_destroy(struct dlist *dlist, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dlist_ins_head(struct dlist *dlist, void *data);
// -----------------------------------------------------------------------------
// int dlist_ins_next(struct dlist_elem *elem, void *data);
// -----------------------------------------------------------------------------
// int dlist_ins_prev(struct dlist *dlist,
//                     struct dlist_elem *elem,
//                     void *data);
// -----------------------------------------------------------------------------
// int dlist_rem_head(struct dlist *dlist, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dlist_rem(struct dlist *dlist,
//               struct dlist_elem *elem,
//               void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dlist_size(const struct dlist *dlist);
// -----------------------------------------------------------------------------
// struct dlist_elem* dlist_tail(const struct dlist *dlist);
// -----------------------------------------------------------------------------
// MACRO dlist_for_each(list, name)
// -----------------------------------------------------------------------------
// MACRO dlist_for_each_safe(list, name, temp)
// -----------------------------------------------------------------------------
// MACRO dlist_for_each_elem(elem, name)
// -----------------------------------------------------------------------------
// MACRO dlist_for_each_elem_safe(elem, name, temp)
// -----------------------------------------------------------------------------

    return true;
}

bool test_list(void) {
    struct list l;
    char *string1;
    char *string2;
    char *string3;

// -----------------------------------------------------------------------------
// void list_init(/*@out@*/ struct list *list);
// -----------------------------------------------------------------------------
// void list_destroy(struct list *list, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int list_ins_head(struct list *list, void *data);
// -----------------------------------------------------------------------------
// int list_ins_next(struct list_elem *elem, void *data);
// -----------------------------------------------------------------------------
// int list_rem_head(struct list *list, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int list_rem_next(struct list_elem *elem, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int list_size(const struct list *list);
// -----------------------------------------------------------------------------
// struct list_elem* list_tail(const struct list *list);
// -----------------------------------------------------------------------------
// MACRO list_for_each(list, name)
// -----------------------------------------------------------------------------
// MACRO list_for_each_safe(list, name, temp)
// -----------------------------------------------------------------------------
// MACRO list_for_each_elem(elem, name)
// -----------------------------------------------------------------------------
// MACRO list_for_each_elem_safe(elem, name, temp)
// -----------------------------------------------------------------------------

    string1 = strdup("Pushed first");
    string2 = strdup("Pushed second");
    string3 = strdup("Pushed third");

    list_init(&l);
    list_ins_head(&l, string1);
    list_ins_head(&l, string2);
    list_ins_head(&l, string3);

    while(list_size(&l) > 0) {
        printf("%d elements in list.\n", list_size(&l));
        list_for_each(&l, elem) {
            puts(elem->data);
        }
        list_rem_head(&l, free);
    }
    
    list_destroy(&l, free);

    return true;
}

int main(void) {
    test_dlist();
    test_list();
    return 0;
}
