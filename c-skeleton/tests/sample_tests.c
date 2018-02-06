#include "minunit.h"

/**
 *
 * This is the template for writing unit test
 * replace with your unit test cases name and contents
 *
 **/

char *test_1()
{
	// write your test case here
	return NULL;
}

char *test_2()
{	
	// write your test case here
	return NULL;
}

char *test_3()
{
	// write your test case here	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_1);
	mu_run_test(test_2);
	mu_run_test(test_3);

	return NULL;
}

RUN_TESTS(all_tests);
