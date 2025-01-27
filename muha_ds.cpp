#include <iostream>
using namespace std;

// Vector
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
    // Linked List
    struct node
    {
        int data;
        node *next;
        node(int x) : data(x)
        {
        }
        ~node()
        {
            cout << "node of value " << data << " destroyed\n";
        }
    };
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
        for (int i = 0; i < num.size(); i++)
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
        for (int i = 0; i < num1.size(); i++)
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
    // Double Linked List
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
    // Array Linked List, used when you need to create a large array whose values are mostly zeroes
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
    // Sparse Matrix
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
    // Tree
    string toStr(int n)
    {
        // Convert integer to string
        ostringstream oss;
        oss << n;
        return oss.str();
    }

    struct node
    {
        int data;
        node *left = nullptr;
        node *right = nullptr;
        node(int val) : data(val) {}
        ~node()
        {
            cout << "Node with value " << data << " destroyed\n";
        }
    };
    bool ismirror(node *cur1 = nullptr, node *cur2 = nullptr)
    {
        if (!cur1 && !cur2)
        {
            return true;
        }
        if (cur1 && !cur2 || cur2 && !cur1 || cur1->data != cur2->data || cur1->left && !cur2->right || cur1->right && !cur2->left)
        {
            return false;
        }
        if (cur1->left && cur1->left->data != cur2->right->data)
        {
            return false;
        }
        if (cur1->right && cur1->right->data != cur2->left->data)
        {
            return false;
        }
        return ismirror(cur1->left, cur2->right) && ismirror(cur1->right, cur2->left);
    }
    class BinaryTree
    {
    private:
        void Clear(node *cur)
        {
            if (!cur)
                return;
            Clear(cur->left);
            Clear(cur->right);
            delete cur;
        }

    public:
        node *root = nullptr;
        BinaryTree(int root_val)
        {
            node *n = new node(root_val);
            root = n;
        }
        BinaryTree(deque<int> &preorder, deque<int> &inorder, int s = 0, int e = -1)
        {
            if (e == -1)
            {
                e = inorder.size();
            }
            node *n = nullptr;
            for (int i = 0; i < (int)preorder.size(); i++)
            {
                for (int j = s; j < e; j++)
                {
                    if (preorder[i] == inorder[j])
                    {
                        n = new node(inorder[j]);
                        preorder.erase(preorder.begin() + i);
                        n->right = (new BinaryTree(preorder, inorder, j + 1, e))->root;
                        n->left = (new BinaryTree(preorder, inorder, s, j))->root;
                        i = preorder.size();
                        break;
                    }
                }
            }
            root = n;
        }
        BinaryTree(queue<pair<int, int>> &q)
        {
            root = new node(q.front().first);
            int val = q.front().second;
            q.pop();
            if (val != 1)
            {
                root->left = (new BinaryTree(q))->root;
                root->right = (new BinaryTree(q))->root;
            }
        }
        BinaryTree(string postfix)
        {
            stack<node *> stck;
            for (int i = 0; i < postfix.size(); i++)
            {
                if (postfix[i] >= '0' && postfix[i] <= '9')
                {
                    stck.push(new node(postfix[i]));
                }
                else
                {
                    node *n = new node(postfix[i]);
                    n->right = stck.top();
                    stck.pop();
                    n->left = stck.top();
                    stck.pop();
                    stck.push(n);
                }
            }
            root = stck.top();
        }
        void Add(const vector<int> &vals, const vector<char> &dirs)
        {
            node *tmp = root;
            for (int i = 0; i < vals.size(); i++)
            {
                if (dirs[i] == 'R')
                {
                    if (tmp->right)
                    {
                        tmp->right->data = vals[i];
                    }
                    else
                    {
                        tmp->right = new node(vals[i]);
                    }
                    tmp = tmp->right;
                }
                else
                {
                    if (tmp->left)
                    {
                        tmp->left->data = vals[i];
                    }
                    else
                    {
                        tmp->left = new node(vals[i]);
                    }
                    tmp = tmp->left;
                }
            }
        }
        int Max(node *cur = nullptr, bool first_time = true)
        {
            if (first_time)
            {
                cur = root;
            }
            if (!cur)
                return INT_MIN;
            return max(max(Max(cur->right, 0), Max(cur->left, 0)), cur->data);
        }
        int Height(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
            {
                cur = root;
            }
            if (!cur)
            {
                return -1;
            }
            return max(Height(cur->right, 0), Height(cur->left, 0)) + 1;
        }
        int Diameter()
        {
            return Height(root->left, 0) + Height(root->right, 0) + 2;
        }
        int NodesNo(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
            {
                cur = root;
            }
            if (!cur)
                return 0;
            return 1 + NodesNo(cur->left, 0) + NodesNo(cur->right, 0);
        }
        int CountLeaf(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
            {
                cur = root;
            }
            if (!cur)
                return 0;
            if (cur->left || cur->right)
            {
                return CountLeaf(cur->left, 0) + CountLeaf(cur->right, 0);
            }
            return 1;
        }
        bool IsFound(int val, node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
            {
                cur = root;
            }
            if (!cur)
            {
                return false;
            }
            return cur->data == val || IsFound(val, cur->left, 0) || IsFound(val, cur->right, 0);
        }
        bool IsPerfect(int h = -1, node *cur = nullptr)
        {
            if (h == -1)
            {
                h = Height();
                cur = root;
            }
            if (!cur)
            {
                return false;
            }
            if (!cur->left && !cur->right)
            {
                return h == 0;
            }
            if (!cur->left && cur->right || cur->right && !cur->left)
            {
                return false;
            }
            return IsPerfect(h - 1, cur->left) && IsPerfect(h - 1, cur->right);
        }
        void PrintInOrder(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
                cur = root;
            if (!cur)
                return;
            PrintInOrder(cur->left, 0);
            cout << cur->data << " ";
            PrintInOrder(cur->right, 0);
        }
        void PrintPostOrder(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
                cur = root;
            if (!cur)
                return;
            PrintPostOrder(cur->left, 0);
            PrintPostOrder(cur->right, 0);
            cout << (char)cur->data;
        }
        void PrintExpression(node *prv = nullptr, node *cur = nullptr, bool first = true)
        {
            if (first)
                cur = root;
            if (!cur)
                return;
            bool bracket = false;
            if (cur->data == '+' || cur->data == '-')
            {
                if (prv && (prv->data == '*' || prv->data == '/' || prv->data == '^'))
                {
                    bracket = true;
                    cout << "(";
                }
            }
            else if (cur->data == '*' || cur->data == '/')
            {
                if (prv && prv->data == '^')
                {
                    bracket = true;
                    cout << "(";
                }
            }
            PrintExpression(cur, cur->left, 0);
            cout << (char)cur->data;
            PrintExpression(cur, cur->right, 0);
            if (bracket)
                cout << ")";
        }
        void Print_iterative()
        {
        }
        void PrintLevelOrder()
        {
            queue<node *> q;
            q.push(root);
            int level = 0, sz = 1;
            while (!q.empty())
            {
                sz = q.size();
                cout << "Level " << level << ": ";
                while (sz--)
                {
                    node *n = q.front();
                    cout << n->data << " ";
                    q.pop();
                    if (n->left)
                    {
                        q.push(n->left);
                    }
                    if (n->right)
                    {
                        q.push(n->right);
                    }
                }
                cout << "\n";
                level++;
            }
        }
        void PrintPreOrderComplete(node *cur = nullptr, bool first = true)
        {
            if (first)
            {
                cur = root;
            }
            if (!cur)
            {
                return;
            }
            cout << cur->data << " ";
            if (cur->left)
            {
                PrintPreOrderComplete(cur->left, 0);
            }
            else
            {
                cout << -1 << " ";
            }
            if (cur->right)
            {
                PrintPreOrderComplete(cur->right, 0);
            }
            else
            {
                cout << -1 << " ";
            }
        }
        void PrintLevelOrderSpiral()
        {
            deque<node *> q;
            q.push_back(root);
            int level = 0, sz = 1;
            while (!q.empty())
            {
                sz = q.size();
                cout << "Level " << level << ": ";
                while (sz--)
                {
                    node *n;
                    if (level % 2 == 0)
                    {
                        n = q.front();
                        q.pop_front();
                    }
                    else
                    {
                        n = q.back();
                        q.pop_back();
                    }
                    cout << n->data << " ";
                    if (level % 2 == 0)
                    {
                        if (n->left)
                        {
                            q.push_back(n->left);
                        }
                        if (n->right)
                        {
                            q.push_back(n->right);
                        }
                    }
                    else
                    {
                        if (n->right)
                        {
                            q.push_front(n->right);
                        }
                        if (n->left)
                        {
                            q.push_front(n->left);
                        }
                    }
                }
                level++;
                cout << "\n";
            }
        }
        string Parenthesize(node *cur = nullptr, bool first = true)
        {
            if (first)
            {
                cur = root;
            }
            if (!cur)
            {
                return "";
            }
            string res = "(" + toStr(cur->data);
            if (cur->left)
            {
                res += Parenthesize(cur->left, 0);
            }
            else
            {
                res += "()";
            }
            if (cur->right)
            {
                res += Parenthesize(cur->right, 0);
            }
            else
            {
                res += "()";
            }
            return res + ")";
        }
        string ParenthesizeCanonical(node *cur = nullptr, bool first = true)
        {
            if (first)
            {
                cur = root;
            }
            if (!cur)
            {
                return "";
            }
            string res = "(" + toStr(cur->data);
            vector<string> v;
            if (cur->left)
                v.push_back(ParenthesizeCanonical(cur->left, 0));
            else
                v.push_back("()");

            if (cur->right)
                v.push_back(ParenthesizeCanonical(cur->right, 0));
            else
                v.push_back("()");

            sort(v.begin(), v.end());
            for (int i = 0; i < (int)v.size(); ++i)
                res += v[i];

            res += ")";

            return res;
        }
        void PrintLevel(int level, node *cur = nullptr, bool first = true)
        {
            if (first)
            {
                cur = root;
            }
            if (!cur)
            {
                return;
            }
            if (level == 0)
            {
                cout << cur->data << " ";
                return;
            }
            PrintLevel(level - 1, cur->left, 0);
            PrintLevel(level - 1, cur->right, 0);
        }
        void PrintLevelOrderRecursive()
        {
            int levels = Height() + 1;
            for (int i = 0; i < levels; i++)
            {
                PrintLevel(i);
                cout << endl;
            }
        }
        bool IsComplete(node *cur = nullptr, int h = -1)
        {
            if (h == -1)
            {
                cur = root;
                h = Height();
            }
            if (!cur || h == 0)
            {
                return true;
            }
            if (h > 1)
            {
                if (!cur->left || !cur->right)
                    return false;
            }
            else if (h == 1)
            {
                if (cur->right && !cur->left)
                {
                    return false;
                }
            }
            return IsComplete(cur->left, h - 1) && IsComplete(cur->right, h - 1);
        }
        bool IsSymmetric(node *cur = nullptr, bool first = true)
        {
            if (first)
            {
                cur = root;
            }
            return ismirror(cur->left, cur->right);
        }
        void Print_left_boundary(node *cur = nullptr, bool firsttime = true)
        {
            if (firsttime)
                cur = root;
            if (!cur)
                return;
            cout << cur->data << " ";
            if (cur->left)
                Print_left_boundary(cur->left, 0);
            else
            {
                Print_left_boundary(cur->right, 0);
            }
        }
        ~BinaryTree()
        {
            Clear(root);
        }
    };
    // Max Heap
    class MaxHeap
    { // You can build a max heap using a min heap by multiplying elements by -1
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
    // Min Heap
    class Heap
    { // By heap I mean MinHeap
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
            for (int i = 0; i < v.size(); i++)
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
    // binary tree (another way of coding)
    class binary_tree
    {
    private:
        binary_tree *left = nullptr;
        int val;
        binary_tree *right = nullptr;

    public:
        binary_tree(int root_val)
        {
            val = root_val;
        }
        void add(vector<int> values, vector<char> directions)
        {
            binary_tree *n = this;
            for (int i = 0; i < values.size(); i++)
            {
                if (directions[i] == 'L')
                {
                    if (n->left)
                    {
                        left->val = values[i];
                    }
                    else
                    {
                        n->left = new binary_tree(values[i]);
                    }
                    n = n->left;
                }
                else
                {
                    if (n->right)
                    {
                        right->val = values[i];
                    }
                    else
                    {
                        n->right = new binary_tree(values[i]);
                    }
                    n = n->right;
                }
            }
        }
        void PrintInOrder()
        {
            if (left)
            {
                left->PrintInOrder();
            }
            cout << val << " ";
            if (right)
            {
                right->PrintInOrder();
            }
        }
        void PrintPostOrder()
        {
            if (left)
            {
                left->PrintPostOrder();
            }
            if (right)
            {
                right->PrintPostOrder();
            }
            cout << (char)val << " ";
        }
        int Max()
        {
            int res = val;
            if (left)
            {
                res = max(res, left->Max());
            }
            if (right)
            {
                res = max(res, right->Max());
            }
            return res;
        }
        int Height()
        {
            int res = 0;
            if (left)
            {
                res = left->Height() + 1;
            }
            if (right)
            {
                res = max(right->Height() + 1, res);
            }
            return res;
        }
        int TotalNodes()
        {
            int res = 1;
            if (left)
            {
                res += left->TotalNodes();
            }
            if (right)
            {
                res += right->TotalNodes();
            }
            return res;
        }
        int LeafNodes()
        {
            int res = 1;
            if (!left && !right)
            {
                return res;
            }
            res = 0;
            if (left)
            {
                res += left->LeafNodes();
            }
            if (right)
            {
                res += right->LeafNodes();
            }
            return res;
        }
        void clear()
        {
            if (left)
            {
                delete left;
                left = nullptr;
            }
            if (right)
            {
                delete right;
                right = nullptr;
            }
        }
        void PrintInOrder2()
        {
            stack<pair<binary_tree *, int>> stck;
            stck.push(make_pair(this, 0));
            while (!stck.empty())
            {

                if (stck.top().second == 0)
                {
                    if (stck.top().first->left)
                    {
                        stck.top().second++;
                        stck.push(make_pair(stck.top().first->left, 0));
                    }
                    else if (stck.top().first->right)
                    {
                        cout << stck.top().first->val << " ";
                        stck.top().second = 2;
                        stck.push(make_pair(stck.top().first->right, 0));
                    }
                    else
                    {
                        cout << stck.top().first->val << " ";
                        stck.pop();
                    }
                    continue;
                }
                if (stck.top().second == 2)
                {
                    stck.pop();
                    continue;
                }
                if (stck.top().second == 1)
                {
                    if (stck.top().first->right)
                    {
                        stck.top().second++;
                        cout << stck.top().first->val << " ";
                        stck.push(make_pair(stck.top().first->right, 0));
                    }
                    else
                    {
                        cout << stck.top().first->val << " ";
                        stck.pop();
                    }
                    continue;
                }
            }
        }
        void PrintInOrderExpression(bool first = true)
        {
            if (val >= '0' && val <= '9')
            {
                cout << (char)val;
                return;
            }
            if (!first)
                cout << "(";
            left->PrintInOrderExpression(0);
            cout << (char)val;
            right->PrintInOrderExpression(0);
            if (!first)
                cout << ")";
        }
        void PrintLeftBoundary()
        {
            binary_tree *n = this;
            while (n)
            {
                cout << n->val << " ";
                if (n->left)
                {
                    n = n->left;
                }
                else
                {
                    n = n->right;
                }
            }
        }
        int Diameter()
        {
            int res = 0;
            if (left)
            {
                res += 1 + left->Height();
            }
            if (right)
            {
                res += 1 + right->Height();
            }
            if (left)
            {
                res = max(res, left->Diameter());
            }
            if (right)
            {
                res = max(res, right->Diameter());
            }
            return res;
        }
        void PrintLevelOrder()
        {
            queue<binary_tree *> line;
            line.push(this);
            int level = 0, nodes = 1;
            while (!line.empty())
            {
                cout << "level " << level << " : ";
                int new_nodes = 0;
                for (int i = 0; i < nodes; i++)
                {
                    if (line.front()->left)
                    {
                        new_nodes++;
                        line.push(line.front()->left);
                    }
                    if (line.front()->right)
                    {
                        new_nodes++;
                        line.push(line.front()->right);
                    }
                    cout << line.front()->val << " ";
                    line.pop();
                }
                cout << endl;
                level++;
                nodes = new_nodes;
            }
        }
        void PrintLevelOrder2()
        {
            int h = Height();
            for (int i = 0; i <= h; i++)
            {
                cout << "level " << i << " : ";
                print_level(i);
                cout << endl;
            }
        }
        bool IsComplete()
        {
        }
        void PrintLevelOrderSpiral()
        {
            queue<binary_tree *> line;
            deque<int> tobeprinted;
            line.push(this);
            int level = 0, nodes = 1;
            while (!line.empty())
            {
                cout << "level " << level << " : ";
                int new_nodes = 0;
                for (int i = 0; i < nodes; i++)
                {
                    if (line.front()->left)
                    {
                        new_nodes++;
                        line.push(line.front()->left);
                    }
                    if (line.front()->right)
                    {
                        new_nodes++;
                        line.push(line.front()->right);
                    }
                    tobeprinted.push_back(line.front()->val);
                    line.pop();
                }
                while (!tobeprinted.empty())
                {
                    if (level % 2 == 0)
                    {
                        cout << tobeprinted.front() << " ";
                        tobeprinted.pop_front();
                    }
                    else
                    {
                        cout << tobeprinted.back() << " ";
                        tobeprinted.pop_back();
                    }
                }
                cout << endl;
                level++;
                nodes = new_nodes;
            }
        }

        void print_level(int level)
        {
            if (level == 0)
            {
                cout << val << " ";
                return;
            }
            if (left)
            {
                left->print_level(level - 1);
            }
            if (right)
            {
                right->print_level(level - 1);
            }
        }
        bool isexist(const int &target)
        {
            if (val == target)
            {
                return true;
            }
            bool found = false;
            if (left)
            {
                found = left->isexist(target);
            }
            if (found)
            {
                return true;
            }
            if (right)
            {
                found = right->isexist(target);
            }
            return found;
        }
        ~binary_tree()
        {
            clear();
        }
    };
    // Array based stack
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
    // class binary search tree
    class BST
    {
        BST *left = nullptr;
        BST *right = nullptr;
        int val{};
        BST *deleteNode(int value, BST *node)
        {
            if (!node)
            {
                return nullptr;
            }
            if (node->val < value)
            {
                node->right = deleteNode(value, node->right);
            }
            else if (value < node->val)
            {
                node->left = deleteNode(value, node->left);
            }
            else
            {
                BST *tmp = node;
                if (!node->right && !node->left)
                { // No children
                    node = nullptr;
                }
                else if (!node->left)
                { // One child
                    BST *child = node->right;
                    val = child->val;
                    left = child->left;
                    right = child->right;
                    delete child;
                    tmp = nullptr;
                }
                else if (!node->right)
                { // One child
                    BST *child = node->left;
                    val = child->val;
                    left = child->left;
                    right = child->right;
                    delete child;
                    tmp = nullptr;
                }
                else
                {
                    BST *mn = right->MinNode();
                    node->val = mn->val;
                    node->right = deleteNode(node->val, node->right);
                    tmp = nullptr;
                }
                if (tmp)
                {
                    delete tmp;
                }
            }
            return node;
        }

    public:
        BST(int val, BST *left = nullptr, BST *right = nullptr) : val(val), left(left), right(right)
        {
        }
        void PrintInOrder()
        {
            if (left)
            {
                left->PrintInOrder();
            }
            cout << val << " ";
            if (right)
            {
                right->PrintInOrder();
            }
        }
        bool search(const int &num)
        { // O(logn)
            if (num == val)
            {
                return true;
            }
            if (num < val)
            {
                return left && left->search(num);
            }
            return right && right->search(num);
        }
        BST *MinNode()
        {
            BST *n = this;
            while (n && n->left)
            {
                n = n->left;
            }
            return n;
        }
        BST *MaxNode()
        {
            BST *n = this;
            while (n && n->right)
            {
                n = n->right;
            }
            return n;
        }
        void Delete(int value)
        {
            if (value == val && !left && !right)
            {
                return;
            }
            deleteNode(value, this);
        }

        int Min()
        {
            BST *n = this;
            while (left)
            {
                n = n->left;
            }
            return n->val;
        }
        int LCA(int value1, int value2)
        {
            if (value1 < val && value2 < val)
            {
                return left->LCA(value1, value2);
            }
            if (value1 > val && value2 > val)
            {
                return right->LCA(value1, value2);
            }
            return val;
        }
        bool search2(const int &num)
        {
            BST *n = this;
            while (n)
            {
                if (n->val == num)
                {
                    return true;
                }
                if (num < n->val)
                {
                    n = n->left;
                }
                else
                {
                    n = n->right;
                }
            }
            return false;
        }
        bool isBST(int l = -INT_MAX, int r = INT_MAX)
        {
            if (!(val > l && val < r))
            {
                return false;
            }
            bool res1 = true, res2 = true;
            if (left)
            {
                res1 = left->isBST(l, val);
            }
            if (right)
            {
                res2 = right->isBST(val, r);
            }
            return res1 && res2;
        }
        int Successor(int value)
        {
            // Get path for the node with val
            stack<BST *> stck;
            BST *n = this;
            while (n->val != value)
            {
                stck.push(n);
                if (value < n->val)
                {
                    n = n->left;
                }
                else
                {
                    n = n->right;
                }
            }
            stck.push(n);
            if (n->right)
            {
                return n->right->val;
            }
            while (stck.size() > 1)
            {
                int tmp = stck.top()->val;
                stck.pop();
                if (stck.top()->left && stck.top()->left->val == tmp)
                {
                    return stck.top()->val;
                }
            }
            return -1;
        }
        void Insert(const int &num)
        { // O(logn)
            if (num < val)
            {
                if (!left)
                {
                    left = new BST(num);
                }
                else
                {
                    left->Insert(num);
                }
            }
            else if (num > val)
            {
                if (!right)
                {
                    right = new BST(num);
                }
                else
                {
                    right->Insert(num);
                }
            }
        }
        ~BST()
        {
            delete left;
            delete right;
            left = nullptr, right = nullptr;
        }
    };
