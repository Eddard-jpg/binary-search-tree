//
// Created by Eddard on 2023-02-24.
//

#ifndef DATASTRUCTURES_RBNODE_H
#define DATASTRUCTURES_RBNODE_H

#include "Node.h"


template<typename T>
class RBNode : public Node<T> {
public:
    // red = false, black = true
    colors color = red;
    
    RBNode() = default;
    
    explicit RBNode(T value_, Node<T> *parent_ = nullptr, colors color_ = red);
    
    Node<T> *add_child(T value_, int direction);
    
    colors get_color();
    
    void set_color(colors color);
    
    void insert_rebalance(unique_ptr<Node<T>> *root);
    
    void erase_rebalance(unique_ptr<Node<T>> *root);
    
};


#endif //DATASTRUCTURES_RBNODE_H
