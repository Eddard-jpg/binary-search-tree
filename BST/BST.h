//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

class BST {

protected:
    
    unique_ptr<Node> root = nullptr;
    
    bool find(int x, Node *u) const {
        if (u == nullptr) return false;
        if (u->value == x) return true;
        return find(x, u->child[u->value < x].get());
    }
    
    void traverse(vector<Node *> &v, Node *u, int mode) const {
        if (u == nullptr) return;
        
        if (mode == 0) v.push_back(u);
        traverse(v, u->child[0].get(), mode);
        if (mode == 1) v.push_back(u);
        traverse(v, u->child[1].get(), mode);
        if (mode == 2) v.push_back(u);
    }
    
    void getPtrs(vector<Node*> &v, Node *u) {
        if (u == nullptr) return;
        
        getPtrs(v, u->child[0].get());
        v.push_back(u->myPtr->release());
        getPtrs(v, u->child[1].get());
    }
    
    void balance(vector<Node*> &sorted, Node *parent, unique_ptr<Node> &myPtr, int l, int r) {
        if (r - l == 0) return;
        
        int mid = (l + r) / 2;
        sorted[mid]->attach_to(parent, myPtr);
        
        balance(sorted, myPtr.get(), myPtr->child[0], l, mid);
        balance(sorted, myPtr.get(), myPtr->child[1], mid + 1, r);
    }

public:
    
    void add(int value) {
        if (root == nullptr) {
            root = make_unique<Node>(value, nullptr, root);
            return;
        }
        
        Node *current = root.get(), *parent = root.get();
        
        while (current != nullptr) {
            if (value == current->value) return;
            parent = current;
            current = current->child[value > current->value].get();
        }
    
        parent->add_child(value, value > parent->value);
    }
    
    [[nodiscard]] bool find(int x) const { return find(x, root.get()); }
    
    // Print all values of the BST, mode = 0 for pre-order traversal, 1 for in-order (default), or 2 for post-order.
    void print(int mode = 1) const {
        if (mode < 0 || mode > 2) throw invalid_argument("print mode must belong to {0, 1, 2}");
        
        vector<Node *> ptrs;
        traverse(ptrs, root.get(), mode);
        
        for (auto ptr: ptrs) cout << *ptr << " ";
        cout << endl;
    }
    
    // Balance the BST manually.
    void balance() {
        vector<Node*> sorted;
        getPtrs(sorted, root.get());
        balance(sorted, nullptr, root, 0, (int) sorted.size());
    }
    
    ~BST() {
        cout << "BST Destroyed" << endl;
    }
    
};


#endif //DATASTRUCTURES_BST_H
