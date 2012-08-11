#include "treap.cc"
#include "testlib.cc"

#include <cstdio>
#include <ctime>
#include <set>

#define sz(v) ((int)((v).size()))
#define forn(i,n) for (int i = 0; i < (n); i++)

void test_simple_insert_contains_erase() {
    treap<int> a;
    const int n = 10;
    forn(i, n) a.insert(i);
    assert_equals(sz(a), n);
    forn(i, n) {
        assert_true(a.contains(i));
        a.insert(i);
        assert_true(a.contains(i));
        assert_equals(sz(a), n);
    }
    for (int i = 1; i < n-1; i++) {
        a.erase(i);
        assert_true(!a.contains(i));
        assert_equals(sz(a), n - i);
    }
    a.insert(1); // [0,1,n-1]
    assert_equals(sz(a), 3);
    a.erase(n-1);
    a.erase(0);
    assert_equals(sz(a), 1);
    assert_true(a.contains(1));
    a.erase(1);
    assert_true(a.empty());
}

template<typename V> double measure(int n) {
    clock_t begin = clock();
    V v;
    forn(i, n) v.insert(i);
    assert_equals(sz(v), n);
    forn(i, n) v.insert(i);
    assert_equals(sz(v), n);
    forn(i, n) v.erase(i);
    assert_equals(sz(v), 0);
    forn(i, n) v.erase(i);
    assert_equals(sz(v), 0);
    clock_t end = clock();
    return (end - begin) * 1. / CLOCKS_PER_SEC;
}

void test_performance() {
    const int n = 5000000;
    printf("  set: %.3lf\n", measure< std::set<int> >(n));
    printf("treap: %.3lf\n", measure< treap<int> >(n));
}

int main() {
    t(test_simple_insert_contains_erase);
    t(test_performance);
    return 0;
}

