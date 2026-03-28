#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

namespace LinkedListDS {

struct node
{
    int data;
    node *next = nullptr;
    node(int val) : data(val)
    {
    }
    ~node()
    {
        cout << "Node with value " << data << " destroyed\n";
    }
};

class LinkedList
{
private:
    int Size{};
    node *head = nullptr;
    node *tail = nullptr;

public:
    LinkedList() {}
    LinkedList(int _size)
    { // time O(n) memory O(n)
        for (int i = 0; i < _size; i++)
        {
            Push_back(0);
        }
    }
    LinkedList(int _size, int _val)
    { // time O(n) memory O(n)
        for (int i = 0; i < _size; i++)
        {
            Push_back(_val);
        }
    }
    int Get_size() // O(1) time & memory
    {
        return Size;
    }
    node *Get_tail() // O(1) time & memory
    {
        return tail;
    }
    node *Get_head() // O(1) time & memory
    {
        return head;
    }
    int operator[](int index)
    {
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
    {
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
    node *delete_node(node *n)
    {
        node *tmp = n->next;
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
            delete n;
            Size--;
        }
        return tmp;
    }
    bool verify_good()
    {
        if (Size == 0)
        {
            if (head || tail)
            {
                return false;
            }
            return true;
        }
        else if (Size == 1)
        {
            if (head != tail || tail->next || !head || !tail)
            {
                return false;
            }
        }
        else
        {
            if (head == tail || tail->next || !head || !tail)
            {
                return false;
            }
        }
        int cnt = 0;
        for (node *tmp = head; tmp; tmp = tmp->next, cnt++)
            ;
        if (cnt != Size)
        {
            return false;
        }
        return true;
    }
    void Push_back(int val)
    { // O(1) time & memory
        node *n = new node(val);
        if (head == nullptr)
        {
            head = tail = n;
        }
        else
        {
            tail->next = n;
            tail = n;
        }
        tail->next = nullptr;
        Size++;
    }
    void Push_front(int val)
    { // O(1) time & memory
        node *n = new node(val);
        if (head == nullptr)
        {
            head = tail = n;
            tail->next = nullptr;
        }
        else
        {
            n->next = head;
            head = n;
        }
        Size++;
    }
    node *Get_node(int index)
    { // O(n) time, O(1) memory
        int i = 0;
        if (index < 0 || index >= Size)
        {
            return nullptr;
        }
        for (node *tmp = head; tmp; tmp = tmp->next, i++)
        {
            if (i == index)
            {
                return tmp;
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
    int Search(int val)
    { // O(n) time, O(1) memory
        if (val == head->data)
        {
            return 0;
        }
        int index = 1;
        for (node *prv = head, *cur = head->next; cur; cur = cur->next, prv = prv->next, index++)
        {
            if (cur->data == val)
            {
                swap(cur->data, prv->data);
                return index;
            }
        }
        return -1;
    }
    void Print()
    { // O(n) time, O(1) memory
        for (node *tmp = head; tmp; tmp = tmp->next)
        {
            cout << tmp->data << " ";
        }
    }
    void Pop(int index)
    { // O(n) time, O(1) memory
        if (index < 0 || index >= Size)
        {
            return;
        }
        else if (index == 0)
        {
            Pop_front();
        }
        else if (index == Size - 1)
        {
            Pop_back();
        }
        else
        {
            int i = 0;
            node *prv, *cur;
            for (cur = head, prv = nullptr; i != index; prv = cur, cur = cur->next, i++)
                ;
            prv->next = prv->next->next;
            delete cur;
            Size--;
        }
    }
    void Pop_item(int val)
    { // O(n) time, O(1) memory
        node *cur, *prv;
        for (cur = head, prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur->data == val)
            {
                break;
            }
        }
        if (!cur)
        {
            return;
        }
        else if (cur == head)
        {
            Pop_front();
        }
        else if (cur == tail)
        {
            Pop_back();
        }
        else
        {
            prv->next = prv->next->next;
            delete cur;
            Size--;
        }
    }
    void Pop_back()
    { // O(n) time, O(1) memory
        if (!head)
        {
            return;
        }
        if (Size == 1)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            node *tmp = nullptr;
            for (tmp = head; tmp->next != tail; tmp = tmp->next)
                ;
            delete tail;
            tail = tmp;
            tail->next = nullptr;
        }
        Size--;
    }
    void Pop_last_item(int val)
    { // O(n), O(1)  memory
        int index = -1;
        int i = 0;
        for (node *tmp = head; tmp; tmp = tmp->next, i++)
        {
            if (tmp->data == val)
            {
                index = i;
            }
        }
        Pop(index);
    }
    void Pop_front()
    { // O(1) time & memory
        if (!head)
        {
            return;
        }
        if (Size == 1)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            node *tmp = head;
            head = head->next;
            delete tmp;
        }
        Size--;
    }
    void Reverse()
    { // O(n) time, O(1) memory
        if (Size <= 1)
        {
            return;
        }
        for (node *prv = head, *cur = head->next, *after = cur->next;; prv = cur, cur = after, after = after->next)
        {
            cur->next = prv;
            if (!after)
            {
                break;
            }
        }
        swap(head, tail);
        tail->next = nullptr;
    }
    void Add(LinkedList &L)
    {
        L.Reverse();
        Reverse();
        bool carry = false;
        node *n1 = head, *n2 = L.Get_head();
        while (n1 && n2)
        {
            n1->data = n1->data + n2->data + carry;
            if (n1->data >= 10)
            {
                n1->data %= 10;
                carry = true;
            }
            else
            {
                carry = false;
            }
            n1 = n1->next;
            n2 = n2->next;
        }
        while (n2)
        {
            if (n2->data + carry >= 10)
            {
                Push_back((n2->data + carry) % 10);
                carry = true;
            }
            else
            {
                Push_back(n2->data + carry);
                carry = false;
            }
            n2 = n2->next;
        }
        while (n1)
        {
            if (carry)
            {
                n1->data += carry;
                if (n1->data >= 10)
                {
                    n1->data %= 10;
                    carry = true;
                }
                else
                {
                    carry = false;
                }
            }
            n1 = n1->next;
        }
        if (carry)
        {
            Push_back(1);
        }
        Reverse();
        L.Reverse();
    }
    void Reverse_chains(node *s, node *e)
    {
        if (s == head && e == tail)
        {
            Reverse();
        }
        else if (s == head)
        {
            node *after_end = e->next;
            for (node *tmp = s->next, *after = s->next;)
            {
            }
        }
    }

    ~LinkedList()
    { // O(n) time, O(1) memory
        while (head)
        {
            node *cur = head->next;
            delete head;
            head = cur;
        }
    }
};

LinkedList Multiply_by_int(string num, int n)
{
    LinkedList res(1, 0);
    LinkedList L;
    if (n <= 0)
    {
        return res;
    }
    for (int i = 0; i < (int)num.size(); i++)
    {
        L.Push_back(num[i] - '0');
    }
    while (n--)
    {
        res.Add(L);
    }
    return res;
}
void Multiply(string num1, string num2)
{
    if (num1.size() < num2.size())
    {
        swap(num1, num2);
    }
    int zeros = 0;
    int index = num2.size() - 1;
    LinkedList L;
    for (int i = 0; i < (int)num1.size(); i++)
    {
        L.Push_back(num1[i] - '0');
    }
    bool first_time = true;
    while (index != -1)
    {
        string num = num1;
        for (int i = 0; i < zeros; i++)
        {
            num += "0";
        }
        LinkedList tmp = Multiply_by_int(num, num2[index] - '0' - first_time);
        first_time = false;
        L.Add(tmp);
        index--;
        zeros++;
    }
    L.Print();
    cout << endl;
}

bool are_equal(LinkedList &L1, LinkedList &L2)
{
    node *tmp1, *tmp2;
    for (tmp1 = L1.Get_head(), tmp2 = L2.Get_head(); tmp1 && tmp2; tmp1 = tmp1->next, tmp2 = tmp2->next)
    {
        if (tmp1->data != tmp2->data)
        {
            return false;
        }
    }
    if (tmp1 || tmp2)
    {
        return false;
    }
    return true;
}

} // namespace LinkedListDS
