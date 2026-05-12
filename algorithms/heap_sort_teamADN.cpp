#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

void push_down(vector<int>& a, int n, int i) {
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;

    if(left<n && a[left]>a[largest])
       largest=left;
    
if(right<n && a[right]>a[largest])
    
        largest=right;
    
if(largest!=i)
    {
        swap(a[i], a[largest]);
        push_down(a, n, largest);
    }
}

void custom_sort(vector<int>& a) {
    if(a.empty()) return;
    int n=a.size();

    for(int i=n/2-1;i>=0;i--)
       push_down(a, n, i);
    
  for(int i=n-1;i>0;i--)
    {
        swap(a[0], a[i]);
        push_down(a, i, 0);
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