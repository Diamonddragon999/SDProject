#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void insertionsort( std::vector<int>&v, int n ) {
    int i, j, key;

    for ( i = 1; i <= n; i++ ) {
        key = v[i];
        j = i - 1;

        while ( j >= 0 && v[j] > key ) {
            v[j + 1] = v[j];
            j = j - 1;
        }

        v[j + 1] = key;
    }
}

void custom_sort( std::vector<int>& v ){
    if( (int)v.size()>1 )
        insertionsort(v,(int)v.size() - 1 );
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
