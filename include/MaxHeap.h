#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

namespace MaxHeapDS {

// You can build a max heap using a min heap by multiplying elements by -1
class MaxHeap
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
    {
        int p = parent(child_index);
        if (p == -1)
        {
            return;
        }
        if (arr[p] < arr[child_index])
        {
            swap(arr[p], arr[child_index]);
            HeapifyUp(p);
        }
    }
    void HeapifyDown(int parent_index)
    {
        int l = left(parent_index), r = right(parent_index);
        if (l == -1)
        {
            return;
        }
        if (r != -1 && arr[r] > arr[l])
        {
            l = r;
        }
        if (arr[parent_index] < arr[l])
        {
            swap(arr[parent_index], arr[l]);
            HeapifyDown(l);
        }
    }
    void Heapify()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            HeapifyDown(i);
        }
    }

public:
    MaxHeap(int capacity = 1000) : capacity(capacity)
    {
        arr = new int[capacity];
        size = 0;
    }
    MaxHeap(vector<int> v)
    {
        assert(v.size() <= capacity);
        arr = new int[capacity];
        size = v.size();
        for (int i = 0; i < size; i++)
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
    {
        assert(size < capacity);
        arr[size] = val;
        HeapifyUp(size++);
    }
    void pop()
    {
        assert(size);
        arr[0] = arr[size - 1];
        HeapifyDown(0);
        size--;
    }
    bool isempty()
    {
        return size == 0;
    }

    ~MaxHeap()
    {
        delete[] arr;
        arr = nullptr;
    }
};

} // namespace MaxHeapDS
