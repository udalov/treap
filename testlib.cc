#include <cstdio>
#include <exception>

class test_failure : public std::exception { };

const char* __t_res[2] = {
    "Fail",
    "OK",
};

#define t(f) { \
    int res = 0; \
    try { \
        f(); \
        res = 1; \
    } catch (test_failure e) { } \
    printf("%s %s\n", #f, __t_res[res]); }

#define assert_equal(x, y) { \
    if (!((x) == (y))) { \
        printf("  assertion failed: assert_equal(%s, %s)\n", #x, #y); \
        throw test_failure(); \
    } }

#define assert_true(x) { \
    if (!(x)) { \
        printf("  assertion failed: assert_true(%s)\n", #x); \
        throw test_failure(); \
    } }

