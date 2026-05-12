#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void bubblesort( std::vector<int>&v, int n ) {
    int i, j, aux;

    for ( i = 0; i < n; i++ )
        for ( j = i + 1; j < n; j++ )
            if ( v[i] > v[j] ) {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
}

void custom_sort( std::vector<int>& v ){
    if( (int)v.size()>1 )
        bubblesort(v,(int)v.size() - 1 );
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) {
        std::cin >> x;
    }

    custom_sort(a);

    assert(std::ranges::is_sorted(a));
    return 0;
}
