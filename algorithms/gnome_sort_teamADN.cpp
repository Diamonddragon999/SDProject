#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

void custom_sort(vector<int>& a) {
    if(a.empty()) return;
    
    int n = a.size();
    int index = 0;

    while(index < n)
    {
        if(index == 0)
          index++;
        
        if(a[index] >= a[index - 1])
          index++;
    
    else
        {
            swap(a[index], a[index - 1]);
            index--;
        }
    }
}

int main() {
    std::ios::sync_with_stdio (false);
    std::cin.tie (nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x: a) {
        std::cin >> x;
    }

    custom_sort(a);

    assert(std::is_sorted(a.begin(), a.end()));
    return 0;
}