#pragma once
#include <cassert>

namespace ArrayStackDS {

class ArrayStack
{
    int *arr{};
    int capacity{};
    int top{};

public:
    ArrayStack(int size) : capacity(size)
    {
        top = -1;
        arr = new int[capacity];
    }
    bool isFull()
    {
        return top >= (capacity - 1);
    }
    bool isEmpty()
    {
        return top < 0;
    }
    void push(int val)
    {
        assert(!isFull());
        arr[++top] = val;
    }
    int pop()
    {
        assert(!isEmpty());
        return arr[top--];
    }
    int Top()
    {
        return arr[top];
    }
    void PushBottom(const int &val)
    {
        if (isEmpty())
        {
            push(val);
            return;
        }
        int tmp = pop();
        PushBottom(val);
        push(tmp);
    }
    void Reverse()
    {
        if (top <= 0)
        {
            return;
        }
        int tmp = pop();
        Reverse();
        PushBottom(tmp);
    }
    ~ArrayStack()
    {
        delete[] arr;
        arr = nullptr;
    }
};

} // namespace ArrayStackDS
