#include "treap.cc"

#include <cassert>
#include <cstdio>
#include <ctime>
#include <set>

#define sz(v) ((int)((v).size()))
#define forn(i,n) for (int i = 0; i < (n); i++)

template<typename V> double measure(int n) {
    clock_t begin = clock();
    V v;
    forn(i, n) v.insert(i);
    assert(sz(v) == n);
    forn(i, n) v.insert(i);
    assert(sz(v) == n);
    forn(i, n) v.erase(i);
    assert(sz(v) == 0);
    forn(i, n) v.erase(i);
    assert(sz(v) == 0);
    clock_t end = clock();
    return (end - begin) * 1. / CLOCKS_PER_SEC;
}

void test_performance() {
    const int n = 5000000;
    printf("  set: %.3lf\n", measure< std::set<int> >(n));
    printf("treap: %.3lf\n", measure< treap<int> >(n));
}

int main() {
    test_performance();
    return 0;
}

