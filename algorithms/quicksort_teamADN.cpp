#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int* medianofthree(int* a, int* b, int* c)
{
    if (*a < *b && *b < *c)
        return (b);

    if (*a < *c && *c <= *b)
        return (c);

    if (*b <= *a && *a < *c)
        return (a);

    if (*b < *c && *c <= *a)
        return (c);

    if (*c <= *a && *a < *b)
        return (a);

    if (*c <= *b && *b <= *a)
        return (b);
}

void qsort( std::vector<int>&v,  int begin, int end ) {
    int aux, b = begin, e = end;
    int* pivot = medianofthree(begin, begin + (end - begin) / 2, end);

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
void custom_sort( std::vector<int>& v ){
    if( (int)v.size() > 1 )
        qsort(v,0,(int)v.size()-1 );
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

    custom_sort( a );

    assert(std::ranges::is_sorted(a));
    return 0;
}
