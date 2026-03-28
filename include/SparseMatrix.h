#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

namespace SparseMatrixDS {

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

public:
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
    ArrayLinkedList() {}
    ArrayLinkedList(int _size)
    { // O(1) time, O(1) memory
        capacity = _size;
    }
    void Set_capacity(int _capacity)
    { // O(1) time & memory
        capacity = _capacity;
    }
    node *Get_head()
    { // O(1) time & memory
        return head;
    }
    void Add(ArrayLinkedList &AL)
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

struct listnode
{
    ArrayLinkedList List;
    int index;
    listnode *next;
    listnode(int _index, int _size)
    {
        List.Set_capacity(_size);
        index = _index;
    }
};

class SparseMatrix
{
private:
    listnode *head = nullptr;
    listnode *tail = nullptr;
    int rows = 0;
    int cols = 0;
    int length = 0;
    void AddListNode(int _index, int _capacity)
    {
        // O(n) time, O(1) memory
        listnode *n = new listnode(_index, _capacity);
        if (!head)
        {
            head = tail = n;
        }
        else if (_index < head->index)
        {
            n->next = head;
            head = n;
        }
        else if (_index > tail->index)
        {
            tail->next = n;
            tail = n;
        }
        else
        {
            for (listnode *prv = nullptr, *cur = head; cur; prv = cur, cur = cur->next)
            {
                if (_index < cur->index)
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
    SparseMatrix(int _rows, int _cols)
    { // O(1) time & memory
        rows = _rows;
        cols = _cols;
    }
    void Set(int row, int col, int val)
    {
        // O(n^2) time, O(1) memory
        if (row < 0 || row >= rows || col < 0 || col >= cols)
        {
            return;
        }
        for (listnode *ni = head; ni; ni = ni->next)
        {
            if (ni->index == row)
            {
                for (node *nj = ni->List.Get_head(); nj; nj = nj->next)
                {
                    if (nj->index == col)
                    {
                        nj->data = val;
                        return;
                    }
                }
                ni->List.AddNode(col, val);
                return;
            }
        }
        AddListNode(row, cols);
        for (listnode *ni = head; ni; ni = ni->next)
        {
            if (ni->index == row)
            {
                ni->List.AddNode(col, val);
            }
        }
    }
    int Get(int row, int col)
    {
        // O(n^2) time, O(1) memory
        for (listnode *ni = head; ni; ni = ni->next)
        {
            if (ni->index == row)
            {
                for (node *nj = ni->List.Get_head(); nj; nj = nj->next)
                {
                    if (nj->index == col)
                    {
                        return nj->data;
                    }
                }
            }
        }
        return 0;
    }
    void Print()
    {
        // O(n^2) time, O(1) memory
        listnode *ni = head;
        node *nj = ni->List.Get_head();
        for (int i = 0; i < rows; i++)
        {
            if (ni && ni->index == i)
            {
                nj = ni->List.Get_head();
                for (int j = 0; j < cols; j++)
                {
                    if (nj && nj->index == j)
                    {
                        cout << nj->data << " ";
                        nj = nj->next;
                    }
                    else
                    {
                        cout << "0 ";
                    }
                }
                ni = ni->next;
            }
            else
            {
                for (int j = 0; j < cols; j++)
                {
                    cout << "0 ";
                }
            }
            cout << "\n";
        }
    }
    void PrintNonZero()
    {
        // O(n^2) time, O(1) memory
        for (listnode *ni = head; ni; ni = ni->next)
        {
            for (node *nj = ni->List.Get_head(); nj; nj = nj->next)
            {
                cout << nj->data << " ";
            }
            cout << "\n";
        }
    }
    void AddMatrix(SparseMatrix &other)
    {
        // O(n+m) time, O(1) memory
        listnode *prv = nullptr, *cur = head, *tmp = other.head;
        while (tmp && cur)
        {
            if (cur->index == tmp->index)
            {
                cur->List.Add(tmp->List);
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
                listnode *n = new listnode(tmp->index, other.cols);
                n->List.Add(tmp->List);
                if (!prv)
                {
                    n->next = head;
                    head = n;
                    length++;
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
            listnode *n = new listnode(tmp->index, other.cols);
            n->List.Add(tmp->List);
            tail->next = n;
            tail = n;
            tail->next = nullptr;
            length++;
            tmp = tmp->next;
        }
        rows = max(rows, other.rows);
        cols = max(cols, other.cols);
    }
    ~SparseMatrix()
    {
        // O(n) time, O(1) memory
        if (!head)
        {
            return;
        }
        for (listnode *tmp = head->next; head != tail; head = tmp, tmp = tmp->next)
        {
            delete head;
        }
        delete tail;
        length = 0;
    }
};

} // namespace SparseMatrixDS
