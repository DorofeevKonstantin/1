#include <stdio.h>
#include <stdlib.h>

#include "Set.h"

int main(void) {
    Set* set = setNew();
    setInsert(set, 8);
    setInsert(set, 1);
    setInsert(set, 4);
    setPrint(set);
    system("pause");

    printf_s("Set %s 1\n", setContains(set, 1) ? "contains" : "doesn't contain");
    system("pause");

    setRemove(set, 1);
    printf_s("Removed 1\n");
    setPrint(set);
    system("pause");

    printf_s("Set %s 1\n", setContains(set, 1) ? "contains" : "doesn't contain");
    system("pause");

    setDelete(set);

    system("pause");
    return 0;
}