#include "list.h"
#include <stdlib.h>
#include <string.h>

void test_list(void) {
    struct list l;
    char *string1;
    char *string2;
    char *string3;
    char *s;

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
}

int main(void) {
    test_list();
    return 0;
}
