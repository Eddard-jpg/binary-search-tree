//
// Created by Eddard on 2023-02-24.
//

#include "RBNode.h"

template<typename T>
RBNode<T>::RBNode(T value_, Node<T> *parent_, colors color_):Node<T>(value_, parent_), color(color_) {}

template<typename T>
Node<T> *RBNode<T>::add_child(T value_, int direction) {
    Node<T>::child[direction] = make_unique<RBNode<T>>(value_, this);
    return Node<T>::child[direction].get();
}

template<typename T>
colors RBNode<T>::get_color() { return color; }

template<typename T>
void RBNode<T>::set_color(colors color_) { color = color_; }

template<typename T>
void RBNode<T>::insert_rebalance(unique_ptr<Node<T>> *root) {
    
    assert(color == red);
    
    if (!Node<T>::parent) return set_color(black);
    
    if (Node<T>::parent->get_color() == black) return;
    
    Node<T> *p = Node<T>::parent;
    
    int direction = Node<T>::get_direction();
    int p_direction = Node<T>::parent->get_direction();
    
    // g can't be nullptr as p can't be the root, the root is guaranteed to be black.
    Node<T> *g = p->parent;
    Node<T> *u = g->child[!p_direction].get();
    
    if (u && u->get_color() == red) {
        // propagate the black from g to p and u, continue rebalancing from g.
        u->set_color(black);
        p->set_color(black);
        g->set_color(red);
        g->insert_rebalance(root);
    } else {
        if (direction != p_direction) {
            p->rotate(!direction, root);
            p = this;
        }
        p->set_color(black);
        g->set_color(red);
        g->rotate(!p_direction, root);
    }
    
}

template<typename T>
void RBNode<T>::erase_rebalance(unique_ptr<Node<T>> *root) {
    
    assert(color == black);
    int direction = Node<T>::get_direction();
    
    // Just noticed I can use this->member and parent::member interchangeably, not sure if there is a difference if there are no shadowing members.
    Node<T> *p = this->parent;
    if (!p) return;
    // s can't be nullptr, since if it was, it would have less black nodes on its path to the root, which violates the RBTree rules
    Node<T> *s = p->child[!direction].get();
    assert(s);
    Node<T> *c = s->child[direction].get();
    Node<T> *d = s->child[!direction].get();
    
    if (p->get_color() == black && s->get_color() == black && (!c || c->get_color() == black) && (!d || d->get_color() == black)) {
        s->set_color(red);
        return p->erase_rebalance(root);
    }
    
    if (s->get_color() == red) {
        p->set_color(red);
        s->set_color(black);
        p->rotate(direction, root);
        s = c;
        assert(s == p->child[!direction].get());
        c = s->child[direction].get();
        d = s->child[!direction].get();
    }
    // s is now black
    
    if ((!c || c->get_color() == black) && (!d || d->get_color() == black)) { // p is red
        p->set_color(black);
        s->set_color(red);
        return;
    }
    
    if (!d || d->get_color() == black) {
        // c is not nullptr. (Otherwise: if !d, then !c && !d above would have been true.
        // if d is black, then c can't be null (for RBTree rules).)
        assert(c);
        
        // c is red. (Otherwise: d must exist (for RBTree rules),
        // so d is black, and (c and d == black) above would have been true)
        assert(c->get_color() == red);
        
        c->set_color(black);
        s->set_color(red);
        s->rotate(!direction, root);
        d = s;
        s = c;
        c = s->child[direction].get(); // Just for consistency.
        assert(d == s->child[!direction].get());
    }
    
    s->set_color(p->get_color());
    p->set_color(black);
    d->set_color(black);
    p->rotate(direction, root);
    
    
}
