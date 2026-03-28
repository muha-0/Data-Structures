#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

namespace VectorDS {

class Vector
{

private:
    int *arr = nullptr;
    int Size;
    int capacity;

public:
    Vector(int x) : Size(x), capacity(Size * 2)
    {
        arr = new int[capacity];
    }
    void expand()
    {
        capacity += capacity;
        int *arr2 = new int[capacity];
        for (int i = 0; i < Size; i++)
        {
            arr2[i] = arr[i];
        }
        swap(arr, arr2);
        delete[] arr2;
    }
    int Find(int val)
    {
        for (int i = 0; i < Size; i++)
        {
            if (arr[i] == val)
            {
                if (i != 0)
                {
                    return i;
                }
            }
            return -1;
        }
        void Print()
        {
            for (int i = 0; i < Size; i++)
            {
                cout << arr[i] << "\n";
            }
        }
        int Get(int indx)
        {
            if (indx < 0 || indx >= Size)
            {
                cout << "Index Error\n";
                return -1;
            }
            return arr[indx];
        }
        void Set(int index, int val)
        {
            if (index < 0 || index >= Size)
            {
                cout << "Index Error\n";
            }
            else
            {
                arr[index] = val;
            }
        }
        int Get_size()
        {
            return Size;
        }
        void Pushback(int val)
        {
            if (Size == capacity)
            {
                expand();
            }
            arr[Size] = val;
            Size++;
        }
        void Pushfront(int val)
        {
            if (Size == capacity)
            {
                expand();
            }
            for (int i = Size; i > 0; i--)
            {
                arr[i] = arr[i - 1];
            }
            arr[0] = val;
            Size++;
        }
        void Insert(int index, int val)
        {
            if (Size == capacity)
            {
                expand();
            }
            for (int i = Size - 1; i >= index; i--)
            {
                arr[i + 1] = arr[i];
            }
            arr[index] = val;
            Size++;
        }
        void Right_rotate()
        {
            int first = arr[Size - 1];
            for (int i = Size - 2; i >= 0; i--)
            {
                arr[i + 1] = arr[i];
            }
            arr[0] = first;
        }
        void Right_rotate(int times)
        {
            times = times % Size;
            for (int i = 0; i < times; i++)
            {
                Right_rotate();
            }
        }
        void Left_rotate()
        {
            int last = arr[0];
            for (int i = 0; i < Size - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            arr[Size - 1] = last;
        }
        int Pop(int index)
        {
            int val = arr[index];
            for (int i = index; i < Size - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            Size--;
            return val;
        }
        ~Vector()
        {
            delete[] arr;
            arr = nullptr;
        }
    };

} // namespace VectorDS
