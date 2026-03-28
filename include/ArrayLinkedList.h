#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

// Array Linked List: used when you need to represent a large array whose values are mostly zeroes

namespace ArrayLinkedListDS {

struct node
{
    int data;
    int index;
    node *next = nullptr;
    node(int val, int indx) : data(val), index(indx) {}
};

class ArrayLinkedList
{
private:
    int length = 0;
    int capacity = 0;
    node *head = nullptr;
    node *tail = nullptr;
    void AddNode(int indx, int val)
    { // O(n) time, O(1) memory
        node *n = new node(val, indx);
        if (!head)
        {
            head = tail = n;
        }
        else if (indx < head->index)
        {
            n->next = head;
            head = n;
        }
        else if (indx > tail->index)
        {
            tail->next = n;
            tail = n;
        }
        else
        {
            for (node *prv = nullptr, *cur = head; cur; prv = cur, cur = cur->next)
            {
                if (indx < cur->index)
                {
                    prv->next = n;
                    n->next = cur;
                    break;
                }
            }
        }
        length++;
        tail->next = nullptr;
    }

public:
    ArrayLinkedList(int _size)
    { // O(1) time, O(1) memory
        capacity = _size;
    }
    void Set(int indx, int val)
    { // O(n) time, O(1) memory
        if (indx < 0 || indx >= capacity)
        {
            return;
        }
        for (node *tmp = head; tmp; tmp = tmp->next)
        {
            if (tmp->index == indx)
            {
                tmp->data = val;
                return;
            }
        }
        AddNode(indx, val);
    }
    int Get(int indx)
    { // O(n) time, O(1) memory
        for (node *tmp = head; tmp; tmp = tmp->next)
        {
            if (tmp->index == indx)
            {
                return tmp->data;
            }
        }
        return 0;
    }
    void Print()
    { // O(n) time, O(1) memory
        node *tmp = head;
        for (int i = 0; i < capacity; i++)
        {
            if (tmp && tmp->index == i)
            {
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            else
            {
                cout << 0 << " ";
            }
        }
    }
    void Print_nonzero()
    { // O(n) time, O(1) memory
        for (node *tmp = head; tmp; tmp = tmp->next)
        {
            cout << tmp->data << " ";
        }
    }
    void Add(ArrayLinkedList AL)
    {
        // O(n+m) time, O(1) memory
        node *prv = nullptr, *cur = head, *tmp = AL.head;
        while (tmp && cur)
        {
            if (cur->index == tmp->index)
            {
                cur->data += tmp->data;
                prv = cur;
                cur = cur->next;
                tmp = tmp->next;
            }
            else if (cur->index < tmp->index)
            {
                prv = cur;
                cur = cur->next;
            }
            else
            {
                node *n = new node(tmp->data, tmp->index);
                if (!prv)
                {
                    AddNode(tmp->index, tmp->data);
                }
                else
                {
                    prv->next = n;
                    n->next = cur;
                    prv = n;
                    length++;
                }
                tmp = tmp->next;
            }
        }
        while (tmp)
        {
            AddNode(tmp->index, tmp->data);
            tmp = tmp->next;
        }
        capacity = max(capacity, AL.capacity);
    }
    ~ArrayLinkedList()
    {
        // O(n) time, O(1) memory
        if (!head)
        {
            return;
        }
        for (node *tmp = head->next; head != tail; head = tmp, tmp = tmp->next)
        {
            delete head;
        }
        delete tail;
        length = 0;
    }
};

} // namespace ArrayLinkedListDS
