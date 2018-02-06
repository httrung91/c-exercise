#ifndef lcthw_List_algo_h
#define lcthw_List_algo_h

#include <stdlib.h>
#include <lcthw/list.h>
#include <string.h>

typedef int (*List_compare) (const char *str1, const char *str2);

int List_bubble_sort(List *list, List_compare cmp);
List *List_merge_sort(List *list, List_compare cmp);

#endif
