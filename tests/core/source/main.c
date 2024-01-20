
#include <munit.h>
#include <defines.h>

// static MunitResult
// test_compare(const MunitParameter params[], void* data) {
//   /* We'll use these later */
//   const unsigned char val_uchar = 'b';
//   const short val_short = 1729;
//   double pi = 3.141592654;
//   char* stewardesses = "stewardesses";
//   char* most_fun_word_to_type;
// 
//   /* These are just to silence compiler warnings about the parameters
//    * being unused. */
//   (void) params;
//   (void) data;
// 
//   /* Let's start with the basics. */
//   munit_assert(0 != 1);
// 
//   /* There is also the more verbose, though slightly more descriptive
//      munit_assert_true/false: */
//   munit_assert_false(0);
// 
//   /* You can also call munit_error and munit_errorf yourself.  We
//    * won't do it is used to indicate a failure, but here is what it
//    * would look like: */
//   /* munit_error("FAIL"); */
//   /* munit_errorf("Goodbye, cruel %s", "world"); */
// 
//   /* There are macros for comparing lots of types. */
//   munit_assert_char('a', ==, 'a');
// 
//   /* Sure, you could just assert('a' == 'a'), but if you did that, a
//    * failed assertion would just say something like "assertion failed:
//    * val_uchar == 'b'".  µnit will tell you the actual values, so a
//    * failure here would result in something like "assertion failed:
//    * val_uchar == 'b' ('X' == 'b')." */
//   munit_assert_uchar(val_uchar, ==, 'b');
// 
//   /* Obviously we can handle values larger than 'char' and 'uchar'.
//    * There are versions for char, short, int, long, long long,
//    * int8/16/32/64_t, as well as the unsigned versions of them all. */
//   munit_assert_short(42, <, val_short);
// 
//   /* There is also support for size_t.
//    *
//    * The longest word in English without repeating any letters is
//    * "uncopyrightables", which has uncopyrightable (and
//    * dermatoglyphics, which is the study of fingerprints) beat by a
//    * character */
//   munit_assert_size(strlen("uncopyrightables"), >, strlen("dermatoglyphics"));
// 
//   /* Of course there is also support for doubles and floats. */
//   munit_assert_double(pi, ==, 3.141592654);
// 
//   /* If you want to compare two doubles for equality, you might want
//    * to consider using munit_assert_double_equal.  It compares two
//    * doubles for equality within a precison of 1.0 x 10^-(precision).
//    * Note that precision (the third argument to the macro) needs to be
//    * fully evaluated to an integer by the preprocessor so µnit doesn't
//    * have to depend pow, which is often in libm not libc. */
//   munit_assert_double_equal(3.141592654, 3.141592653589793, 9);
// 
//   /* And if you want to check strings for equality (or inequality),
//    * there is munit_assert_string_equal/not_equal.
//    *
//    * "stewardesses" is the longest word you can type on a QWERTY
//    * keyboard with only one hand, which makes it loads of fun to type.
//    * If I'm going to have to type a string repeatedly, let's make it a
//    * good one! */
//   munit_assert_string_equal(stewardesses, "stewardesses");
// 
//   /* A personal favorite macro which is fantastic if you're working
//    * with binary data, is the one which naïvely checks two blobs of
//    * memory for equality.  If this fails it will tell you the offset
//    * of the first differing byte. */
//   munit_assert_memory_equal(7, stewardesses, "steward");
// 
//   /* You can also make sure that two blobs differ *somewhere*: */
//   munit_assert_memory_not_equal(8, stewardesses, "steward");
// 
//   /* There are equal/not_equal macros for pointers, too: */
//   most_fun_word_to_type = stewardesses;
//   munit_assert_ptr_equal(most_fun_word_to_type, stewardesses);
// 
//   /* And null/not_null */
//   munit_assert_null(NULL);
//   munit_assert_not_null(most_fun_word_to_type);
// 
//   /* Lets verify that the data parameter is what we expected.  We'll
//    * see where this comes from in a bit.
//    *
//    * Note that the casting isn't usually required; if you give this
//    * function a real pointer (instead of a number like 0xdeadbeef) it
//    * would work as expected. */
//   munit_assert_ptr_equal(data, (void*)(uintptr_t)0xdeadbeef);
// 
//   return MUNIT_OK;
// }

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
  {
    /* The name is just a unique human-readable way to identify the
     * test. You can use it to run a specific test if you want, but
     * usually it's mostly decorative. */
    (char*) "/example/compare",
    /* You probably won't be surprised to learn that the tests are
     * functions. */
    test_compare,
    /* If you want, you can supply a function to set up a fixture.  If
     * you supply NULL, the user_data parameter from munit_suite_main
     * will be used directly.  If, however, you provide a callback
     * here the user_data parameter will be passed to this callback,
     * and the return value from this callback will be passed to the
     * test function.
     *
     * For our example we don't really need a fixture, but lets
     * provide one anyways. */
    test_compare_setup,
    /* If you passed a callback for the fixture setup function, you
     * may want to pass a corresponding callback here to reverse the
     * operation. */
    test_compare_tear_down,
    /* Finally, there is a bitmask for options you can pass here.  You
     * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
     * defaults. */
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  /* Usually this is written in a much more compact format; all these
   * comments kind of ruin that, though.  Here is how you'll usually
   * see entries written: */
  { (char*) "/example/rand", test_rand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  /* To tell the test runner when the array is over, just add a NULL
   * entry at the end. */
  { (char*) "/example/parameters", test_parameters, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* If you wanted to have your test suite run other test suites you
 * could declare an array of them.  Of course each sub-suite can
 * contain more suites, etc. */
/* static const MunitSuite other_suites[] = { */
/*   { "/second", test_suite_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE }, */
/*   { NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE } */
/* }; */

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
  /* This string will be prepended to all test names in this suite;
   * for example, "/example/rand" will become "/µnit/example/rand".
   * Note that, while it doesn't really matter for the top-level
   * suite, NULL signal the end of an array of tests; you should use
   * an empty string ("") instead. */
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
  /* In addition to containing test cases, suites can contain other
   * test suites.  This isn't necessary in this example, but it can be
   * a great help to projects with lots of tests by making it easier
   * to spread the tests across many files.  This is where you would
   * put "other_suites" (which is commented out above). */
  NULL,
  /* An interesting feature of µnit is that it supports automatically
   * running multiple iterations of the tests.  This is usually only
   * interesting if you make use of the PRNG to randomize your tests
   * cases a bit, or if you are doing performance testing and want to
   * average multiple runs.  0 is an alias for 1. */
  1,
  /* Just like MUNIT_TEST_OPTION_NONE, you can provide
   * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
  MUNIT_SUITE_OPTION_NONE
};

/* This is only necessary for EXIT_SUCCESS and EXIT_FAILURE, which you
 * *should* be using but probably aren't (no, zero and non-zero don't
 * always mean success and failure).  I guess my point is that nothing
 * about µnit requires it. */
#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */
    return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}
