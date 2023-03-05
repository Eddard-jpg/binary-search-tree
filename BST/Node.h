//
// Created by Eddard on 2023-02-17.
//

#ifndef DATASTRUCTURES_NODE_H
#define DATASTRUCTURES_NODE_H

#include <bits/stdc++.h>
using namespace std;


enum colors {
    red = 0, black = 1
};

template<typename T>
class Node {
public:
    T value;
    Node *parent = nullptr;
    unique_ptr<Node> child[2];
    
    bool operator<(const Node &other) const;
    bool operator<=(const Node &other) const;
    bool operator==(const Node &other) const;
    bool operator>=(const Node &other) const;
    bool operator>(const Node &other) const;
    
    bool operator<(const T &other) const;
    bool operator<=(const T &other) const;
    bool operator==(const T &other) const;
    bool operator>=(const T &other) const;
    bool operator>(const T &other) const;
    
    Node() = default;
    
    explicit Node(T value_, Node *parent_ = nullptr);
    
    virtual Node<T> *add_child(T value_, int direction);
    
    void attach_child(Node *node, int direction);
    
    void attach_to(Node *parent_);
    
    unique_ptr<Node> *get_ptr();
    
    int get_direction();
    
    void rotate(int direction, unique_ptr<Node<T>> *root);
    
    ~Node();
    
    [[nodiscard]] virtual int get_height() const;
    
    virtual void update_height() {}
    
    virtual int balance_factor() { return 0; }
    
    virtual colors get_color() { return red; }
    
    virtual void set_color(colors color) {}
    
    virtual void insert_rebalance(unique_ptr<Node<T>> *root) {}
    
    virtual void erase_rebalance(unique_ptr<Node<T>> *root) {}
    
};

#endif //DATASTRUCTURES_NODE_H
