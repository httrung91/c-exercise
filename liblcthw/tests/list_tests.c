#include <assert.h>
#include <lcthw/list.h>
#include <string.h>
#include "minunit.h"

//static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *total = "[test1 data, test2 data, test3 data, ]";

List *create_list()
{
	List *list = List_create();
	return list;
}

void populate_list(List * list)
{
	List_push(list, test1);
	List_push(list, test2);
	List_push(list, test3);
}

char *test_create()
{
	List *list = create_list();
	mu_assert(list != NULL, "Failed to create list.");	
	
	List_destroy(list);
	return NULL;
}

char *test_destroy()
{
	List *list = List_create();;
	populate_list(list);

	List_destroy(list);
	mu_assert(list != NULL, "Failed to destroy list.");

	return NULL;
}

char *test_push_pop()
{
	List *list = create_list();

	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last value.");

	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last value.");

	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last value.");	
	mu_assert(List_count(list) == 3, "Wrong count on push.");

	char *val = List_pop(list);
	mu_assert(val == test3, "Wrong value on pop.");

	val = List_pop(list);
	mu_assert(val == test2, "Wrong value on pop.");

	val = List_pop(list);
	mu_assert(val == test1, "Wrong value on pop.");
	mu_assert(List_count(list) == 0, "Wrong count after pop.");

	List_destroy(list);
	return NULL;
}

char *test_unshift()
{
	List * list = create_list();

	List_unshift(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first value.");

	List_unshift(list, test2);
	mu_assert(List_first(list) == test2, "wrong first value.");

	List_unshift(list, test3);
	mu_assert(List_first(list) == test3, "Wrong first valur.");
	mu_assert(List_count(list) == 3, "Wrong count on unshift.");

	List_destroy(list);
	return NULL;
}

char *test_remove()
{
	// we only need to test the middle remove case since push/shift 
    // already tests the other cases
	List *list = create_list();
	populate_list(list);

	char *val = List_remove(list, list->first->next);
	mu_assert(val == test2, "Wrong removed element.");
	mu_assert(List_count(list) == 2, "Wrong count after remove.");
	mu_assert(List_first(list) == test1, "Wrong first after remove.");
	mu_assert(List_last(list) == test3, "Wrong last after remove.");

	List_destroy(list);
	return NULL;
}

char *test_shift()
{
	List *list = create_list();
	populate_list(list);

	mu_assert(List_count(list) != 0, "Wrong count before shift.");

	char *val = List_shift(list);
	mu_assert(val == test1, "Wrong value on shift.");

	val = List_shift(list);
	mu_assert(val == test2, "Wrong value on shift.");
	mu_assert(List_count(list) == 1, "Wrong count after shift.");

	List_destroy(list);
	return NULL;
}

char *test_find_position()
{
	List *list = create_list();
	populate_list(list);

	ListNode *re = List_find_position(list, -1);
	mu_assert(re == NULL, "Position is out of range (negative). Should return NULL.");

	re = List_find_position(list, 3);
	mu_assert(re == NULL, "Position is out of range (on boundary). Should return NULL.");

	re = List_find_position(list, 4);
	mu_assert(re == NULL, "Position is out of range (greater). Should return NULL.");

	re = List_find_position(list, 1);
	mu_assert(re->value == test2, "Wrong Item when find position.");

	return NULL;
}

char *test_to_string()
{
	char *re = List_to_string(NULL);
	mu_assert(re == NULL, "Result should be NULL");

	List *list = create_list();
	populate_list(list);
	
	re = List_to_string(list);	
	mu_assert(!strcmp(re, total), "To Strind data not match.");	

	return NULL;
}

char *all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_destroy);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_find_position);
	mu_run_test(test_to_string);

	return NULL;
}

RUN_TESTS(all_tests); 
