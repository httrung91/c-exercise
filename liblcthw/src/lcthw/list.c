#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <string.h>

List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
	LIST_FOREACH(list, first, next, cur) {
		if (cur->prev) {
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);
}

void List_clear(List * list)
{
	if (!list) {
		return;
	}

	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{
	if (!list) {
		return;
	}	

	log_info("Before loop clear destroy.");	
	LIST_FOREACH(list, first, next, cur) {
		log_info("Prepare to free: %s.", cur->value);
		free(cur->value);
		log_info("After free cur->value.");
		if (cur->prev) {
			log_info("Before free cur->prev.");
			free(cur->prev);
			log_info("After free cur->prev.");
		}
	}
	log_info("After loop clear destroy.");
	free(list->last);
	log_info("Free list.");
	free(list);
}

void List_push(List * list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->last == NULL) {
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;

error:
	return;
}

void *List_pop(List * list)
{
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List * list, void *value)
{
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if (list->first == NULL) {
		list->first = node;
		list->last = node;
	} else {
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}

	list->count++;

error:
	return;
}

void *List_shift(List * list)
{
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List * list, ListNode * node)
{
	void *result = NULL;

	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL.");

	if (node == list->first && node == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else if (node == list->first) {
		list->first = node->next;
		check(list->first != NULL, "Invalide list, somehow a first in list is NULL.");
		list->first->prev = NULL;
	} else if (node == list->last) {
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, somehow a last in list is NULL.");
		list->last->next = NULL;
	} else {
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	list->count--;
	result = node->value;
	free(node);

error:
	return result;
}

char *List_to_string(List *list)
{
	char *res = NULL;
	
	if (!list) {
		return NULL;
	} else {

		int valLength = 2;
		int i = 0;

		LIST_FOREACH(list, first, next, cur) {
			valLength += strlen(cur->value);
		}
		
		valLength += List_count(list)*2;
		res = calloc(valLength, sizeof(char));
		
		strcat(res, "[");
		for (cur = list->first; cur != NULL; cur = cur->next) {
			strcat(res, cur->value);
			strcat(res, ", ");
		}
		strcat(res, "]");
	}

	return res;
}

void List_swap(List * list, ListNode * node1, ListNode * node2)
{
	if (!node1 || !node2) {
		return;
	}

	node1->next = node2->next;
	node2->prev = node1->prev;
	node1->prev = node2;
	node2->next = node1;
	
	if (node1->next != NULL) {
		node1->next->prev = node1;
	} else {
		list->last = node1;
	}

	if (node2->prev != NULL) {
		node2->prev->next = node2;
	} else {
		list->first = node2;
	}

}

ListNode *List_find_position(List * list, int position)
{
	check(((position >= 0) && (position < List_count(list))), "Position is out of range.");
	

	ListNode *re = list->first;
	int i;
	for (i = 0; i < position; i++) {
		re = re->next;
	}

	return re;

error:
	return NULL;	
}

List *List_split(List * list, ListNode * node)
{
	check(node != NULL, "Node is NULL");

	List *new_list = List_create();
	
	if (node->prev) {
		node->prev->next = NULL;
		node->prev = NULL;	
	}

	int count = 0;
	ListNode *current;

	new_list->first = node;
	for (current = node; current != NULL; current = current->next) {
		count++;
		if (current->next == NULL) {
			new_list->last = current;
		}
	}
	new_list->count = count;

	return list;

error:
	return NULL;
}
	
