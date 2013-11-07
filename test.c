#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool test_dl_list(void) {
// -----------------------------------------------------------------------------
// void dl_list_init(/*@out@*/ struct dl_list *dl_list);
// -----------------------------------------------------------------------------
// void dl_list_destroy(struct dl_list *dl_list, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dl_list_ins_head(struct dl_list *dl_list, void *data);
// int dl_list_ins_next(struct dl_list_elem *elem, void *data);
// -----------------------------------------------------------------------------
// int dl_list_ins_prev(struct dl_list *dl_list,
//                     struct dl_list_elem *elem,
//                     void *data);
// -----------------------------------------------------------------------------
// int dl_list_rem_head(struct dl_list *dl_list, void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dl_list_rem(struct dl_list *dl_list,
//               struct dl_list_elem *elem,
//                void (*destroy)(void *data));
// -----------------------------------------------------------------------------
// int dl_list_size(const struct dl_list *dl_list);
// -----------------------------------------------------------------------------
// struct dl_list_elem* dl_list_tail(const struct dl_list *dl_list);
// -----------------------------------------------------------------------------
// MACRO dl_list_for_each(list, name)
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
    test_dl_list();
    test_list();
    return 0;
}
