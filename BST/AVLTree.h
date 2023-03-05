//
// Created by Eddard on 2023-02-18.
//

#ifndef DATASTRUCTURES_AVLTREE_H
#define DATASTRUCTURES_AVLTREE_H

#include "AVLNode.h"
#include "BST.h"

template<typename T>
class AVLTree : public BST<T> {
public:
    
    Node<T> *insert(T value);
    
    void balance();

protected:
    
    Node<T> *erase(Node<T> *u);
    
};


#endif //DATASTRUCTURES_AVLTREE_H
