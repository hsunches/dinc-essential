#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <sys/time.h>
#include "ut_util.h"

#define PRINT_LOG(s, ...)   print_indent(); printf(s, __VA_ARGS__)

static const int g_indent_width = 4;
static int g_indent_lv;

static double get_ms_time(void) {
	struct timeval time;

	gettimeofday(&time, NULL);
	return (double)time.tv_sec * 1000.0 + (double)time.tv_usec / 1000.0;
}

static struct test *create_test(int type, const char *name, int loop_cnt, int (*p_func)(char *)) {
	struct test *p_test;

	if (name == NULL || loop_cnt <= 0) {
		return NULL;
	}

	if (type == UT_TEST && p_func == NULL) {
		return NULL;
	}

	p_test = (struct test *)calloc(1, sizeof(struct test_suite));

	if (p_test != NULL) {
		strncpy(p_test->name, name, MAX_TEST_NAME_LEN);
		p_test->type = type;
		p_test->loop_cnt = loop_cnt;

		if (type == UT_TEST) {
			p_test->p_func = p_func;
		}
	}

	return p_test;
}

struct test_suite *create_test_suite(const char *name, int loop_cnt) {
	return (struct test_suite *)create_test(UT_TEST_SUITE, name, loop_cnt, NULL);
}

int add_test(struct test_suite *p_suite, const char *name, int loop_cnt, int (*p_func)(char *)) {
	struct test *p_test;

	if (p_suite == NULL || p_suite->test_cnt == MAX_TEST_CNT) {
		return -1;
	}

	p_test = create_test(UT_TEST, name, loop_cnt, p_func);

	if (p_test == NULL) {
		return -1;
	}

	p_suite->p_tests[p_suite->test_cnt++] = p_test;
	return 0;
}

int add_test_suite(struct test_suite *p_parent, const struct test_suite *p_child) {
	if (p_parent == NULL || p_child == NULL || p_parent->test_cnt == MAX_TEST_CNT) {
		return -1;
	}

	p_parent->p_tests[p_parent->test_cnt++] = (struct test *)p_child;
	return 0;
}

static void print_indent(void) {
	static int is_init = 0;
	static char indent[80];

	if (!is_init) {
		memset(indent, ' ', sizeof(indent));
		is_init = 1;
	}

	indent[g_indent_lv * g_indent_width] = 0;
	fputs(indent, stdout);
	indent[g_indent_lv * g_indent_width] = ' ';
}

#define BUF_SIZE	4096

int run_test(const struct test *p_test) {
	struct test_suite *p_suite;
	int i, j;
	int result, sub_result;
	double start_time, end_time;
	double run_time;
	double run_time_sum;
	double run_time_min, run_time_max, run_time_avg;
	char text[BUF_SIZE];

	if (p_test != NULL) {
		p_suite = (struct test_suite *)p_test;
		result = UT_PASS;
		run_time_sum = 0.0;
		run_time_min = DBL_MAX;
		run_time_max = -DBL_MAX;

		PRINT_LOG("[ %s ]\n", p_test->name);
		PRINT_LOG("%s\n", "----------------------------------------");

		for (i = 1; i <= p_test->loop_cnt; i++) {
			start_time = get_ms_time();

			if (p_test->type == UT_TEST) {
				sub_result = (*p_test->p_func)(text);

				switch (sub_result) {
				case UT_PASS:
				case UT_FAIL:
					PRINT_LOG(" #%d: %s\n", i, sub_result == UT_FAIL ? "*FAIL*" : "PASS");

					{
						char *token;

						token = strtok(text, "\n");

						while (token) {
							PRINT_LOG(" %s\n", token);
							token = strtok(NULL, "\n");
						}
					}

					break;

				default:
					PRINT_LOG(" #%d: NOT SUPPORT\n", i);

					break;
				}
			} else {
				sub_result = UT_PASS;

				for (j = 0; j < p_suite->test_cnt; j++) {
					g_indent_lv++;

					if (run_test(p_suite->p_tests[j]) == UT_FAIL) {
						sub_result = UT_FAIL;
					}

					g_indent_lv--;
				}
			}

			if (sub_result != UT_PASS) {
				result = sub_result;
			}

			end_time = get_ms_time();
			run_time = end_time - start_time;
			
			if (run_time < 0.0) {
				run_time = 0.0;
			} else {
				run_time_sum += run_time;
			}

			if (run_time < run_time_min) {
				run_time_min = run_time;
			}

			if (run_time > run_time_max) {
				run_time_max = run_time;
			}
		}

		run_time_avg = run_time_sum / p_test->loop_cnt;

		PRINT_LOG("%s\n", "----------------------------------------");
		PRINT_LOG(" Result           : %s\n", result == UT_PASS ? "PASS" : (result == UT_FAIL ? "*FAIL*" : "NOT SUPPORT"));

		if (p_test->loop_cnt == 1) {
			PRINT_LOG(" Run Time         : %.3lf ms\n", run_time_sum);
		} else {
			PRINT_LOG(" Rounds           : %d\n", p_test->loop_cnt);
			PRINT_LOG(" Run Time (max)   : %.3lf ms\n", run_time_max);
			PRINT_LOG(" Run Time (min)   : %.3lf ms\n", run_time_min);
			PRINT_LOG(" Run Time (avg)   : %.3lf ms\n", run_time_avg);
			PRINT_LOG(" Run Time (total) : %.3lf ms\n", run_time_sum);
		}

		PRINT_LOG("%s\n\n", "----------------------------------------");

		return result;
	}

	return UT_FAIL;
}

int run_test_suite(const struct test_suite *p_suite) {
	return run_test((const struct test *)p_suite);
}

void delete_test_suite(struct test_suite *p_suite) {
	int i;

	if (p_suite != NULL) {
		for (i = 0; i < p_suite->test_cnt; i++) {
			if (p_suite->p_tests[i]->type == UT_TEST) {
				free(p_suite->p_tests[i]);
			} else {
				delete_test_suite((struct test_suite *)p_suite->p_tests[i]);
			}
		}

		free(p_suite);
	}
}

