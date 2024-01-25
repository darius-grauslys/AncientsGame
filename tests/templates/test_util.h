#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <munit.h>

#define TEST_NAME(name) \
    MunitTestFunc_ ## name
#define TEST_NAME__SETUP(name) \
    setup__MunitTestFunc_ ## name
#define TEST_NAME__CLEAN_UP(name) \
    clean_up__MunitTestFunc_ ## name

#define TEST_FUNCTION(name) \
    MunitResult TEST_NAME(name) (\
            const MunitParameter params[], \
            void* user_data_or_fixture) 

#define SETUP_TEST(name) \
void* TEST_NAME__SETUP(name) (\
        const MunitParameter params[], \
        void* user_data)

#define CLEAN_UP_TEST(name) \
void TEST_NAME__CLEAN_UP(name) (void* fixture)

#define INCLUDE_TEST(name, options, parameters) \
{ \
    #name, \
    TEST_NAME(name), \
    TEST_NAME__SETUP(name), \
    TEST_NAME__CLEAN_UP(name), \
    options, \
    parameters \
}

#define INCLUDE_TEST__NO_PARAMETERS(name, options) \
    INCLUDE_TEST(name, options, NULL)

#define INCLUDE_TEST__BASIC(name) \
    INCLUDE_TEST(name, MUNIT_TEST_OPTION_NONE, NULL)

#define INCLUDE_TEST__STATELESS(name) \
{ \
    #name, \
    TEST_NAME(name), \
    NULL, \
    NULL, \
    MUNIT_TEST_OPTION_NONE, \
    NULL \
}

#define END_SUITES \
(MunitSuite) { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE }

#define END_TESTS \
(MunitTest) { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

typedef void (*f_test_suite_includer)(MunitSuite *test_suite);

#define DECLARE_SUITE(name) \
void include_test_suite__ ## name(\
        MunitSuite *test_suite);

#define INCLUDE_SUITE(name) \
include_test_suite__ ## name

// args leading from name are tests.
#define DEFINE_SUITE(name, ...) \
char *test_suite_ ## name ## __prefix = #name "_" ;\
\
MunitTest test_suite_ ## name ## __tests[] = { \
    __VA_ARGS__, \
    END_TESTS \
}; \
\
void include_test_suite__ ## name ( \
        MunitSuite *test_suite) { \
    test_suite->prefix = \
        test_suite_ ## name ## __prefix; \
    test_suite->tests = \
        test_suite_ ## name ## __tests; \
    test_suite->iterations = 1; \
    test_suite->options = MUNIT_SUITE_OPTION_NONE; \
    test_suite->suites = NULL; \
}

#define INCLUDE_SUB_SUITES(name, count, ...) \
MunitSuite test_suite_ ## name ## __sub_suites[count]; \
void include_sub_suites_for__ ## name (MunitSuite *test_suite) { \
    f_test_suite_includer test_suite_includers[] = { \
        __VA_ARGS__ \
    }; \
    for (int i=0;i<count;i++) { \
        if (!test_suite_includers[i]) { \
            break; \
        } \
        test_suite_includers[i](&test_suite_ ## name ## __sub_suites[i]); \
    } \
    test_suite->suites = test_suite_ ## name ## __sub_suites; \
}

// args leading from name are tests.
#define DEFINE_SUITE_WITH__SUB_SUITES(name, ...) \
char *test_suite_ ## name ## __prefix = #name "_"; \
\
MunitTest test_suite_ ## name ## __tests[] = { \
    __VA_ARGS__, \
    END_TESTS \
}; \
\
void include_test_suite__ ## name( \
        MunitSuite *test_suite) { \
    test_suite->prefix = \
        test_suite_ ## name ## __prefix; \
    test_suite->tests = \
        test_suite_ ## name ## __tests; \
    test_suite->iterations = 1; \
    test_suite->options = MUNIT_SUITE_OPTION_NONE; \
    include_sub_suites_for__ ## name (test_suite); \
}

#endif
