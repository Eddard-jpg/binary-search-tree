#include <bits/stdc++.h>
#include "Node.cpp"
#include "BST.cpp"
#include "AVLNode.cpp"
#include "AVLTree.cpp"

using namespace std;

int main() {
    
    unique_ptr<BST<int>> ptr(new AVLTree<int>);
    
    int n, e, q, l, r;
    cin >> n >> e >> q >> l >> r;
    
    for (int i = 0; i < n; ++i) {
        int x = i + 1;
        //cin >> x;
        ptr->insert(x);
    }
    
    for (int i = 0; i < e; ++i) {
        int x = i + 1;
        cin >> x;
        ptr->erase(x);
    }
    
    cout << "Pre-order Traversal: ";
    ptr->print(0);
    
    cout << "In-order Traversal: ";
    ptr->print(1);
    
    cout << "Post-order Traversal: ";
    ptr->print(2);
    
    
    for (int i = 0; i < q; ++i) {
        int x = i + 1;
        cin >> x;
        cout << (ptr->find(x) != nullptr) << endl;
    }
    
    for (int i = 0; i < l; ++i) {
        int x = i + 1;
        cin >> x;
        auto nodePtr = ptr->lower_bound(x);
        cout << (nodePtr ? nodePtr->value : -1) << endl;
    }
    
    for (int i = 0; i < r; ++i) {
        int x = i + 1;
        cin >> x;
        auto nodePtr = ptr->upper_bound(x);
        cout << (nodePtr ? nodePtr->value : -1) << endl;
    }
    
    if (*ptr->get_root()) {
        cout << (*ptr->get_root())->get_height() << endl;
    }
    
    return 0;
}
