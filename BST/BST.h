//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

template<typename T>
class BST {
protected:
    
    unique_ptr<Node<T>> root = nullptr;
    
    bool find(T x, Node<T> *u) const;
    
    void traverse(vector<Node<T> *> &v, Node<T> *u, int mode) const;
    
    void getPtrs(vector<Node<T> *> &v, Node<T> *u);
    
    void balance(vector<Node<T> *> &sorted, Node<T> *parent, unique_ptr<Node<T>> &myPtr, int l, int r);

public:
    
    unique_ptr<Node<T>> *get_root();
    
    void add(T value);
    
    [[nodiscard]] bool find(T x) const;
    
    // Print all values of the BST, mode = 0 for pre-order traversal, 1 for in-order (default), or 2 for post-order.
    void print(int mode = 1) const;
    
    // Balance the BST manually.
    void balance();
    
    ~BST();
    
    
};


#endif //DATASTRUCTURES_BST_H
