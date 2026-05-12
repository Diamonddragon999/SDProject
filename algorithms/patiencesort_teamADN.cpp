#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int> mergepiles( std::vector<std::vector<int>> &mat ) {
    int minn, i, j;
    std::vector<int> ans;
    while ( mat.size() != 0 ) {
        minn = 2000000000;
        i = -1;

        for ( j = 0; j < mat.size(); j++ ) {
            if ( minn > mat[j][mat[j].size() - 1]) {
                minn = mat[j][mat[j].size() - 1];
                i = j;
            }
        }

        ans.push_back( minn );
        mat[i].pop_back();

        if ( mat[i].empty() )
            mat.erase( mat.begin() + i );
    }

    return ans;
}

void patiencesorting( std::vector<int>&v, int n ) {
    int i, j, ok;
    std::vector<std::vector<int>> pile;

    for ( i = 0; i <= n; i++ ) {
        if ( pile.empty() ) {
            std::vector<int> temp;
            temp.push_back( v[i] );
            pile.push_back( temp );
        } else {
            ok = 0;
            j = 0;
            while ( j < pile.size() && ok == 0 ) {
                if ( v[i] < pile[j][pile[j].size() - 1] ) {
                    pile[j].push_back( v[i] );
                    ok = 1;
                }

                j++;
            }

            if ( ok == 0 ) {
                std::vector<int> temp;
                temp.push_back( v[i] );
                pile.push_back( temp );
            }
        }
    }

    v = mergepiles( pile );
}

void custom_sort( std::vector<int>& v ){
    if( (int)v.size()>1 )
        patiencesorting(v,(int)v.size() - 1 );
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
