#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void merge_arrays(vector<int>& a, int l, int mid, int r, vector<int>& temp) {
    int i=l;
    int j=mid+1;
    int k=l;

    while(i<=mid && j<=r)
    { 
        if(a[i]<=a[j])
        {
            temp[k++]=a[i++];
        }
        else
        {
            temp[k++]=a[j++];
        }
    }

    while(i<=mid)
     temp[k++]=a[i++];
    

    while(j<=r)
      temp[k++]=a[j++];
    

    for(int p=l;p<=r;p++)
    { 
        a[p]=temp[p];
    }
}

void merge_sort(vector<int>& a, int l, int r, vector<int>& temp) {
    if(l>=r) return;

    int mid=l+(r-l)/2;

    merge_sort(a, l, mid, temp);
    merge_sort(a, mid+1, r, temp);

    
    if(a[mid]<=a[mid+1]) return;

    merge_arrays(a, l, mid, r, temp);
}

void custom_sort(vector<int>& a) {
    if(a.empty()) return;
    vector<int> temp(a.size());
    merge_sort(a, 0, a.size()-1, temp);
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