#include <lcthw/dbg.h>
#include <lcthw/list_algos.h>

int List_bubble_sort(List *list, List_compare cmp)
{
	int swap = 1;
	ListNode *temp = NULL;

	while (swap) {
		swap = 0;
		LIST_FOREACH(list, first, next, cur) {
			if (cur->next != NULL && cmp(cur->value, cur->next->value) > 0) {
				temp = cur->next;
				List_swap(list, cur, cur->next);
				cur = temp;
				swap = 1;
			}	
		}
	}

	return 0;

error:
	return 1;
}

inline void break_link(ListNode *node)
{
	if (node->prev) {
		node->prev->next = NULL;
		node->prev = NULL;
	}
}

ListNode *merge_sort_merge(ListNode * first, ListNode * second, List_compare cmp)
{
	ListNode *cur1 = first;
	ListNode *cur2 = second;
	ListNode *tmp = NULL;
	
	int check_count = 0;
	while(cur1 != NULL && cur2 != NULL) {
		if (cmp(cur1->value, cur2->value) > 0) {
			if (!tmp) {
				tmp = cur2;
				first = tmp;
			} else {
				tmp->next = cur2;
				cur2->prev = tmp;
				tmp = cur2;
			}
			
			cur2 = cur2->next;
			tmp->next = NULL;
			if (cur2) {
				cur2->prev = NULL;
			}

		} else {
			if (!tmp) {
				tmp = cur1;
				first = tmp;
			} else {
				tmp->next = cur1;
				cur1->prev = tmp;
				tmp = cur1;
			}

			cur1 = cur1->next;
			tmp->next = NULL;
			if (cur1) {
				cur1->prev = NULL;
			}
		}
		check_count++;
	}

	if (cur1) {
		tmp->next = cur1;
		cur1->prev = tmp;
	}

	if (cur2) {
		tmp->next = cur2;
		cur2->prev = tmp;
	}

	return first;

error:
	return NULL;
}

ListNode *merge_sort_split(ListNode * begin, int count, List_compare cmp)
{
	if (count < 2) {
		return begin;
	}

	int count_break = (int) count/2;
	int i;
	
	ListNode *mid = begin;
	for (i = 0; i < count_break; i++) {
		mid = mid->next;
	}
	break_link(mid);

	ListNode *first_half = merge_sort_split(begin, count_break, cmp);
	ListNode *second_half = merge_sort_split(mid, (count - count_break), cmp);
	
	begin = merge_sort_merge(first_half, second_half, cmp);

	return begin;
}

List * List_merge_sort(List *list, List_compare cmp)
{
	int count_break = (int) List_count(list) / 2;
	ListNode *mid = List_find_position(list, count_break);
	break_link(mid);
	
	ListNode *first_half = merge_sort_split(list->first, count_break, cmp);
	ListNode *second_half = merge_sort_split(mid, (List_count(list) - count_break), cmp);

	list->first = merge_sort_merge(first_half, second_half, cmp);

	ListNode *tmp;	
	for (tmp = list->first; tmp != NULL; tmp = tmp->next) {
		list->last = tmp;
	}

	return list;
error:
	return NULL;
}
