#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void qsort( std::vector<int>&v,  int begin, int end ) {
    int aux, b = begin, e = end,
      pivot = v[(begin + end) / 2];

    while ( v[b] < pivot )
        b++;

    while ( v[e] > pivot )
        e--;

    while( b < e ) {
        aux = v[b];
        v[b] = v[e];
        v[e] = aux;

        do
            b++;
        while (v[b] < pivot);

        do
            e--;
        while (v[e] > pivot);
    }

    if ( begin < e )
        qsort( v, begin, e );
    if ( e + 1 < end )
        qsort( v, e + 1, end );
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, i;

    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) {
        std::cin >> x;
    }

    qsort( a, 0, n - 1 );

    assert(std::ranges::is_sorted(a));
    return 0;
}
