#ifndef UT_UTIL_H
#define UT_UTIL_H

#include <stdint.h>
#include <string.h>

#define MAX_TEST_NAME_LEN	32
#define MAX_TEST_CNT		100

#define MAKE_TEST_FUNC_STR(func_name, size)	\
int test_##func_name(char *text) {			\
	char s[size + size];					\
	int len;								\
											\
	if (func_name(s) == 0) {				\
		len = strlen(s);					\
											\
		if (len == 0 || len > (size)) {		\
			sprintf(text, "*%s*", s);		\
			return UT_FAIL;					\
		}									\
											\
		strcpy(text, s);					\
		return UT_PASS;						\
	}										\
											\
	return UT_NOT_SUPPORT;					\
}

#define MAKE_TEST_FUNC_INT(func_name, min, max)					\
int test_##func_name(char *text) {								\
	int value;													\
																\
	if (func_name(&value) == 0) {		 						\
		if (value < (min) || value > (max)) {	   				\
			sprintf(text, "*%d*", value);						\
			return UT_FAIL;			 							\
		}					   									\
																\
		sprintf(text, "%d", value);								\
		return UT_PASS;											\
	}					   										\
																\
	return UT_NOT_SUPPORT;										\
}

#define MAKE_TEST_FUNC_UINT64(func_name, min, max)				\
int test_##func_name(char *text) {								\
	uint64_t value;												\
																\
	if (func_name(&value) == 0) {		 						\
		if (value < (min) || value > (max)) {	   				\
			sprintf(text, "*%llu*", (unsigned long long)value);	\
			return UT_FAIL;			 							\
		}					   									\
																\
		sprintf(text, "%llu", (unsigned long long)value);		\
		return UT_PASS;											\
	}					   										\
																\
	return UT_NOT_SUPPORT;										\
}

#define TEST_COMMON						\
	int type;							\
	char name[MAX_TEST_NAME_LEN + 1];	\
	int loop_cnt;

enum {
	UT_TEST,
	UT_TEST_SUITE
};

enum {
	UT_PASS,
	UT_FAIL,
	UT_NOT_SUPPORT
};

#pragma pack(1)

struct test {
	TEST_COMMON
	int (*p_func)(char *);
};

struct test_suite {
	TEST_COMMON
	int test_cnt;
	struct test *p_tests[MAX_TEST_CNT];
};

#pragma pack()

struct test_suite *create_test_suite(const char *name, int loop_cnt);
int add_test(struct test_suite *p_suite, const char *name, int loop_cnt, int (*p_func)(char *));
int add_test_suite(struct test_suite *p_parent, const struct test_suite *p_child);
int run_test_suite(const struct test_suite *p_suite);
void delete_test_suite(struct test_suite *p_suite);

#endif

