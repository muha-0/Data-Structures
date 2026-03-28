#pragma once
#include <iostream>
#include <stack>
using namespace std;

namespace BSTDS {

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

} // namespace BSTDS
