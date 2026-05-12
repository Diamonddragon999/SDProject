#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

void custom_sort(vector<int>& a) {
    if(a.empty()) return;
    int n=a.size();
    
    vector<unsigned int> u(n);
    vector<unsigned int> temp(n);

    for(int i=0;i<n;i++)
       u[i]=static_cast<unsigned int>(a[i])^0x80000000;
    

   
    for(int shift=0;shift<32;shift+=8)
    {
        int count[256]={0};

       for(int i=0;i<n;i++)
        {
            count[(u[i]>>shift)&0xFF]++;
        }

        for(int i=1;i<256;i++)
        {
            count[i]+=count[i-1];
        }

        for(int i=n-1;i>=0;i--)
        {
            int byte_val=(u[i]>>shift)&0xFF;
            temp[--count[byte_val]]=u[i];
        }

    u=temp;
    }

    
    for(int i=0;i<n;i++)
     a[i]=static_cast<int>(u[i]^0x80000000);
    
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