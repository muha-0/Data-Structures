#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
using namespace std;

// Alternative binary tree implementation (self-referential node style)
namespace BinaryTreeV2DS {

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
        for (int i = 0; i < (int)values.size(); i++)
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

} // namespace BinaryTreeV2DS
