#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <climits>
#include <sstream>
#include <string>
using namespace std;

namespace BinaryTreeDS {

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
        for (int i = 0; i < (int)postfix.size(); i++)
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
        for (int i = 0; i < (int)vals.size(); i++)
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

} // namespace BinaryTreeDS
