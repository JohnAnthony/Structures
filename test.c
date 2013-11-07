#include "dlist.h"
#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------

bool test_clist(void);
bool test_dlist(void);
bool test_list(void);

// -----------------------------------------------------------------------------

int main(void) {
    test_list();
    test_dlist();
    test_clist();
    return 0;
}

// -----------------------------------------------------------------------------

bool test_clist(void) {
    return true;
}

bool test_dlist(void) {
    return true;
}

bool test_list(void) {
    struct list l;
    char *string1;
    char *string2;
    char *string3;

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

