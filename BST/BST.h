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

public:
    
    [[nodiscard]] int size() const;
    
    [[nodiscard]] int height() const;
    
    [[nodiscard]] bool empty() const;
    
    [[nodiscard]] Node<T> *find(T x) const;
    
    Node<T> *lower_bound(T value) const;
    
    Node<T> *upper_bound(T value) const;
    
    virtual Node<T> *insert(T value);
    
    Node<T> *erase(T value);
    
    void clear();
    
    // Print all values of the BST, mode = 0 for pre-order traversal, 1 for in-order (default), or 2 for post-order.
    void print(int mode = 1) const;
    
    // Balance the BST manually.
    virtual void balance();
    
    ~BST();
    
    unique_ptr<Node<T>> *get_root();

protected:
    
    int size_ = 0;
    unique_ptr<Node<T>> root = nullptr;
    
    Node<T> *find(T value, Node<T> *u) const;
    
    Node<T> *lower_bound(T value, Node<T> *u) const;
    
    Node<T> *upper_bound(T value, Node<T> *u) const;
    
    virtual Node<T> *erase(Node<T> *u);
    
    void traverse(vector<Node<T> *> &v, Node<T> *u, int mode) const;
    
    void getPtrs(vector<Node<T> *> &v, Node<T> *u);
    
    void balance(vector<Node<T> *> &sorted, Node<T> *parent, int l, int r);
    
};


#endif //DATASTRUCTURES_BST_H
