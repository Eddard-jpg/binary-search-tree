#include <bits/stdc++.h>
#include "BST.h"

using namespace std;

int main() {
    
    BST bst;
    
    int n, q;
    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        
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