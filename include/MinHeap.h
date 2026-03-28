#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

namespace MinHeapDS {

// By Heap I mean MinHeap
class Heap
{
private:
    int *arr = nullptr;
    int size, capacity = 1000;
    int left(int index)
    {
        if (2 * index + 1 >= size)
        {
            return -1;
        }
        return 2 * index + 1;
    }
    int right(int index)
    {
        if (2 * index + 2 >= size)
        {
            return -1;
        }
        return 2 * index + 2;
    }
    int parent(int index)
    {
        if (index == 0)
        {
            return -1;
        }
        return floor((index - 1) / 2);
    }
    void HeapifyUp(int child_index)
    { // O( log(n) ) because the height of the complete tree is log(n)
        int p = parent(child_index);
        while (p != -1 && arr[p] > arr[child_index])
        {
            swap(arr[p], arr[child_index]);
            child_index = p;
            p = parent(child_index);
        }
    }
    // Recursive way
    void HeapifyDown(int parent_index)
    { // O( log(n) ) because the height of the complete tree is log(n)
        int l = left(parent_index), r = right(parent_index);
        if (l == -1)
        {
            return;
        }
        if (r != -1 && arr[r] < arr[l])
        {
            l = r;
        }
        if (arr[parent_index] > arr[l])
        {
            swap(arr[l], arr[parent_index]);
            HeapifyDown(l);
        }
    }
    void Heapify()
    { // O(n) not O( log(n) ) but its proof is out of our scope
        // Start from non-leaf nodes
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            HeapifyDown(i);
        }
    }
    bool IsHeap(int parent_index = 0)
    {
        int l = left(parent_index), r = right(parent_index);
        if (parent_index == -1)
        {
            return true;
        }
        if (l != -1 && arr[l] < arr[parent_index])
        {
            return false;
        }
        if (r != -1 && arr[r] < arr[parent_index])
        {
            return false;
        }
        return IsHeap(l) && IsHeap(r);
    }

public:
    Heap(int capacity = 1000) : capacity(capacity)
    {
        arr = new int[this->capacity];
        size = 0;
    }
    Heap(const vector<int> &v)
    { // O(n)
        assert(v.size() <= capacity);
        arr = new int[capacity];
        size = v.size();
        for (int i = 0; i < (int)v.size(); i++)
        {
            arr[i] = v[i];
        }
        Heapify();
    }
    int top()
    {
        assert(size);
        return arr[0];
    }
    void push(int val)
    { // O( log(n) )
        assert(size < capacity);
        arr[size] = val;
        HeapifyUp(size);
        size++;
    }
    void PrintLessthan(const int &val, int index = 0)
    {
        if (arr[index] >= val)
        {
            return;
        }
        cout << arr[index] << " ";
        int l = left(index), r = right(index);
        if (l != -1)
        {
            PrintLessthan(val, l);
        }
        if (r != -1)
        {
            PrintLessthan(val, r);
        }
    }
    bool isempty()
    {
        return size == 0;
    }
    bool IsHeapArr(int *p, int n)
    {
        pair<int *, int> original = make_pair(arr, size);
        arr = p, size = n;
        bool res = IsHeap(0);
        arr = original.first;
        size = original.second;
        return res;
    }
    void pop()
    { // O( log(n) )
        assert(size);
        arr[0] = arr[size - 1];
        HeapifyDown(0);
        size--;
    }
    void SortArr(int *p, int n)
    {
        pair<int *, int> original = make_pair(arr, size);
        arr = p;
        size = n;
        Heapify();
        while (size--)
        {
            swap(arr[0], arr[size]);
            HeapifyDown(0);
        }
        for (int i = 0; i < n / 2; i++)
        {
            swap(arr[i], arr[n - i - 1]);
        }
        arr = original.first;
        size = original.second;
    }
    ~Heap()
    {
        delete[] arr;
        arr = nullptr;
    }
};

} // namespace MinHeapDS
