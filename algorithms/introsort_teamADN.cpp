#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int medianofthree(int a, int b, int c) {
    if(a<b && b<c) return b;
    if(a<c && c<=b) return c;
    if(b<=a && a<c) return a;
    if(b<c && c<=a) return c;
    if(c<=a && a<b) return a;
    if(c<=b && b<=a) return b;
    return a;
}

void insertionsort(vector<int>& v, int begin, int end) {
    for(int i=begin+1;i<=end;i++)
    {
        int key=v[i];
        int j=i-1;

        while(j>=begin && v[j]>key)
        {
            v[j+1]=v[j];
            j=j-1;
        }

        v[j+1]=key;
    }
}

void push_down(vector<int>& a, int begin, int end, int i) {
    int largest=i;
    int left=begin+2*(i-begin)+1;
    int right=begin+2*(i-begin)+2;

    if(left<=end && a[left]>a[largest])
    {
        largest=left;
    }

    if(right<=end && a[right]>a[largest])
    {
        largest=right;
    }

    if(largest!=i)
    {
        swap(a[i], a[largest]);
        push_down(a, begin, end, largest);
    }
}

void heapsort_range(vector<int>& a, int begin, int end) {
    int n=end-begin+1;

    for(int i=begin+n/2-1;i>=begin;i--)
    {
        push_down(a, begin, end, i);
    }

    for(int i=end;i>begin;i--)
    {
        swap(a[begin], a[i]);
        push_down(a, begin, i-1, begin);
    }
}

void introsort_logic(vector<int>& v, int begin, int end, int depth_limit) {
    int size=end-begin+1;

    if(size<16)
    {
        insertionsort(v, begin, end);
        return;
    }

    if(depth_limit==0)
    {
        heapsort_range(v, begin, end);
        return;
    }

    int pivot=medianofthree(v[begin], v[begin+size/2], v[end]);
    int b=begin;
    int e=end;

    while(b<=e)
    {
        while(v[b]<pivot) b++;
        while(v[e]>pivot) e--;

        if(b<=e)
        {
            swap(v[b], v[e]);
            b++;
            e--;
        }
    }

    if(begin<e) introsort_logic(v, begin, e, depth_limit-1);
    if(b<end) introsort_logic(v, b, end, depth_limit-1);
}

void custom_sort(vector<int>& a) {
    if(a.empty()) return;
    int depth_limit=2*log2(a.size());
    introsort_logic(a, 0, a.size()-1, depth_limit);
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