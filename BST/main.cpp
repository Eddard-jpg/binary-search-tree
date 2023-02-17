#include <bits/stdc++.h>
#include "BST.h"
#include "BST.cpp"
#include "Node.cpp"

using namespace std;

int main() {
    
    BST<int> bst;
    
    int n, q;
    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        int x = i + 1;
        
        bst.add(x);
    }
    
    
    cout << "Pre-order Traversal: ";
    bst.print(0);
    
    cout << "In-order Traversal: ";
    bst.print(1);
    
    cout << "Post-order Traversal: ";
    bst.print(2);
    
    bst.balance();
    cout << "\nBalanced:\n";
    
    
    cout << "Pre-order Traversal: ";
    bst.print(0);
    
    cout << "In-order Traversal: ";
    bst.print(1);
    
    cout << "Post-order Traversal: ";
    bst.print(2);
    
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        
        cout << bst.find(x) << endl;
    }
    
    return 0;
}