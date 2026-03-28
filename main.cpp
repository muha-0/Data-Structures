#include <iostream>

#include "include/LinkedList.h"
#include "include/DLinkedList.h"
#include "include/ArrayLinkedList.h"
#include "include/SparseMatrix.h"
#include "include/BinaryTree.h"
#include "include/MaxHeap.h"
#include "include/MinHeap.h"
#include "include/BinaryTreeV2.h"
#include "include/ArrayStack.h"
#include "include/BST.h"

int main()
{
    // --- Singly Linked List ---
    {
        LinkedListDS::LinkedList list;
        list.Push_back(1);
        list.Push_back(2);
        list.Push_back(3);
        list.Push_front(0);
        list.Print();   // 0 1 2 3
        std::cout << "\n";
    }

    // --- Doubly Linked List ---
    {
        DLinkedListDS::DLinkedList dlist;
        dlist.Push_back(10);
        dlist.Push_back(20);
        dlist.Push_sorted(15);
        dlist.Print();           // 10 15 20
        dlist.Print_reversed();  // 20 15 10
    }

    // --- Array Linked List (sparse array) ---
    {
        ArrayLinkedListDS::ArrayLinkedList arr(10);
        arr.Set(0, 5);
        arr.Set(4, 7);
        arr.Set(9, 3);
        arr.Print();  // 5 0 0 0 7 0 0 0 0 3
        std::cout << "\n";
    }

    // --- Sparse Matrix ---
    {
        SparseMatrixDS::SparseMatrix mat(4, 4);
        mat.Set(0, 0, 1);
        mat.Set(1, 2, 5);
        mat.Set(3, 3, 9);
        mat.Print();
    }

    // --- Binary Tree ---
    {
        BinaryTreeDS::BinaryTree tree(1);
        tree.Add({2, 4}, {'L', 'L'});
        tree.Add({3, 5}, {'R', 'R'});
        tree.PrintLevelOrder();
        std::cout << "Height: " << tree.Height() << "\n";
    }

    // --- Max Heap ---
    {
        MaxHeapDS::MaxHeap maxh;
        maxh.push(3);
        maxh.push(1);
        maxh.push(7);
        maxh.push(5);
        std::cout << "MaxHeap top: " << maxh.top() << "\n";  // 7
    }

    // --- Min Heap ---
    {
        MinHeapDS::Heap minh;
        minh.push(3);
        minh.push(1);
        minh.push(7);
        minh.push(5);
        std::cout << "MinHeap top: " << minh.top() << "\n";  // 1
    }

    // --- Binary Tree V2 ---
    {
        BinaryTreeV2DS::binary_tree bt(1);
        bt.add({2, 3}, {'L', 'R'});
        bt.PrintInOrder();  // 2 1 3
        std::cout << "\n";
    }

    // --- Array Stack ---
    {
        ArrayStackDS::ArrayStack stk(10);
        stk.push(1);
        stk.push(2);
        stk.push(3);
        std::cout << "Stack top: " << stk.Top() << "\n";  // 3
        stk.Reverse();
        std::cout << "Stack top after reverse: " << stk.Top() << "\n";  // 1
    }

    // --- BST ---
    {
        BSTDS::BST bst(10);
        bst.Insert(5);
        bst.Insert(15);
        bst.Insert(3);
        bst.PrintInOrder();  // 3 5 10 15
        std::cout << "\n";
        std::cout << "Search 5: " << bst.search(5) << "\n";   // 1
        std::cout << "Search 99: " << bst.search(99) << "\n"; // 0
    }

    return 0;
}
