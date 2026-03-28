#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

namespace DLinkedListDS {

struct node
{
    int data;
    node *next = nullptr;
    node *prev = nullptr;
    node(int val) : data(val) {}
    ~node()
    {
        cout << "Node with value " << data << " destroyed\n";
    }
};

class DLinkedList
{
private:
    node *head = nullptr;
    node *tail = nullptr;
    int Size = 0;
    node *delete_node(node *n)
    {
        node *after = n->next;
        if (n == head)
        {
            Pop_front();
        }
        else if (n == tail)
        {
            Pop_back();
        }
        else
        {
            link(n->prev, after);
            delete n;
            Size--;
        }
        return after;
    }
    void link(node *first, node *second)
    {
        if (first)
        {
            first->next = second;
        }
        if (second)
        {
            second->prev = first;
        }
    }

public:
    DLinkedList() {}
    DLinkedList(int _size_)
    { // O(n) time & memory
        for (int i = 0; i < _size_; i++)
        {
            Push_back(0);
        }
    }
    DLinkedList(int _size_, int val)
    { // O(n) time & memory
        for (int i = 0; i < _size_; i++)
        {
            Push_back(val);
        }
    }
    bool Check_correct()
    {
        if (Size == 0)
        {
            if (head || tail)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            if (!head || !tail)
            {
                return false;
            }
            if (Size == 1)
            {
                if (head != tail)
                {
                    return false;
                }
            }

            else
            {
                if (head == tail || head->prev || tail->next)
                {
                    return false;
                }
            }
        }
        int len = 0;
        for (node *cur = head; cur; cur = cur->next, len++)
        {
            if (len == Size - 1 && cur != tail)
            {
                return false;
            } // make sure we end at tail
        }

        if (Size != len)
        {
            return false;
        }

        len = 0;
        for (node *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == Size - 1 && cur != head) // make sure we end at head

                return false;
        }
        return true;
    }
    void Push_back(int val)
    { // O(1) time & memory
        node *n = new node(val);
        if (!head)
        {
            head = tail = n;
        }
        else
        {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        tail->next = nullptr;
        head->prev = nullptr;
        Size++;
    }
    void Push_front(int val)
    { // O(1) time & memory
        node *n = new node(val);
        if (!head)
        {
            head = tail = n;
        }
        else
        {
            n->next = head;
            head->prev = n;
            head = n;
        }
        head->prev = nullptr;
        tail->next = nullptr;
        Size++;
    }
    void Push_sorted(int val)
    { // O(n) time, O(1) memory
        node *n = new node(val), *tmp;
        for (tmp = head; tmp && tmp->data < val; tmp = tmp->next)
            ;
        if (tmp == head)
        {
            Push_front(val);
        }
        else if (!tmp)
        {
            Push_back(val);
        }
        else
        {
            link(tmp->prev, n);
            link(n, tmp);
            Size++;
        }
    }
    void Pop_back()
    { // O(1) time & memory
        if (!head)
        {
            return;
        }
        else if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        Size--;
    }
    void Pop_front()
    { // O(1) time & memory
        if (!head)
        {
            return;
        }
        else if (head == tail)
        {
            Pop_back();
        }
        else
        {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            Size--;
        }
    }
    void Pop(int index)
    { // O(n) time, O(1) memory
        if (index < 0 || index >= Size)
        {
            return;
        }
        int i = 0;
        node *tmp;
        for (tmp = head; i != index; tmp = tmp->next)
            ;
        if (tmp == head)
        {
            Pop_front();
        }
        else if (tmp == tail)
        {
            Pop_back();
        }
        else
        {
            link(tmp->prev, tmp->next);
            delete tmp;
            Size--;
        }
    }
    void Pop_item(int val)
    { // O(n) time, O(1) memory
        node *tmp;
        for (tmp = head; tmp && tmp->data != val; tmp = tmp->next)
            ;
        if (!tmp)
        {
            return;
        }
        if (tmp == head)
        {
            Pop_front();
        }
        else if (tmp == tail)
        {
            Pop_back();
        }
        else
        {
            link(tmp->prev, tmp->next);
            delete tmp;
            Size--;
        }
    }
    void Pop_items(int val)
    { // O(n) time, O(1) memory
        if (!head)
        {
            return;
        }
        for (node *tmp = head; tmp;)
        {
            if (tmp->data == val)
            {
                tmp = delete_node(tmp);
            }
            else
            {
                tmp = tmp->next;
            }
        }
    }
    int Find(int val)
    { // O(n) time, O(1) memory
        int index = 0;
        for (node *tmp = head; tmp; tmp = tmp->next, index++)
        {
            if (tmp->data == val)
            {
                return index;
            }
        }
        return -1;
    }
    int operator[](int index)
    { // O(n) time, O(1) memory
        if (index < 0 || index >= Size)
        {
            return 0;
        }
        int i = 0;
        node *tmp;
        for (tmp = head; i != index; tmp = tmp->next, i++)
            ;
        return tmp->data;
    }
    void Set(int index, int val)
    { // O(n) time, O(1) memory
        if (index < 0 || index >= Size)
        {
            return;
        }
        int i = 0;
        node *tmp;
        for (tmp = head; i != index; tmp = tmp->next, i++)
            ;
        tmp->data = val;
    }
    void Print()
    { // O(n) time, O(1) memory
        for (node *tmp = head; tmp; tmp = tmp->next)
        {
            cout << tmp->data << " ";
        }
        cout << endl;
    }
    void Print_reversed()
    { // O(n) time, O(1) memory
        for (node *tmp = tail; tmp; tmp = tmp->prev)
        {
            cout << tmp->data << " ";
        }
        cout << endl;
    }
    bool IsPalindrome()
    { // O(n) time, O(1) memory
        for (node *s = head, *e = tail; s != e && s->prev != e; s = s->next, e = e->prev)
        {
            if (s->data != e->data)
            {
                return false;
            }
        }
        return true;
    }
    int Get_middle()
    { // O(n) time, O(1) memory
        if (!head)
        {
            return 0;
        }
        for (node *slow = head, *fast = head;;)
        {
            if (fast && fast->next && fast->next->next)
            {
                fast = fast->next->next;
                slow = slow->next;
            }
            else
            {
                return slow->data;
            }
        }
    }
    void Reverse()
    { // O(n) time, O(1) memory
        if (Size <= 1)
        {
            return;
        }
        for (node *prv = head, *cur = head->next, *after = cur->next;; prv = cur, cur = after, after = after->next)
        {
            link(cur, prv);
            if (!after)
            {
                break;
            }
        }
        swap(head, tail);
        tail->next = nullptr;
        head->prev = nullptr;
    }

    ~DLinkedList()
    { // O(n) time, O(1) memory
        if (!head)
        {
            return;
        }
        for (node *tmp = head->next; head != tail; head = tmp, tmp = tmp->next)
        {
            delete head;
        }
        delete tail;
        Size = 0;
    }
};

} // namespace DLinkedListDS
