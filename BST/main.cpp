#include <bits/stdc++.h>
#include "Node.cpp"
#include "BST.cpp"
#include "AVLNode.cpp"
#include "AVLTree.cpp"
#include "RBNode.cpp"
#include "RBTree.cpp"
#include <chrono>
#include <memory>

using namespace std;
using namespace chrono;

mt19937 rnd(time(nullptr));

void retry() { cout << "Whoops! Try again." << endl; }

int main() {
    
    unique_ptr<BST<int>> ptr;
    
    int type;
    cout << "Choose the type of BST (1: Red-Black Tree, 2: AVL Tree, Other: Normal BST): ";
    cin >> type;
    
    if (type == 1) ptr = make_unique<RBTree<int>>();
    else if (type == 2) ptr = make_unique<AVLTree<int>>();
    else ptr = make_unique<BST<int>>();
    
    cout << "Enter operations (case-sensitive, all integers in range [-2^31, 2^31 - 1]):\n"
            "'insert x': inserts value x into the tree if it doesn't exist, does nothing otherwise.\n"
            "'erase x': erases value x from the tree if it exists, does nothing otherwise.\n"
            "'erase_all l r' (l <= r): erases all values from l to r from the tree.\n"
            "'find x': prints 1 if value x exists in the tree, prints 0 otherwise.\n"
            "'empty': prints 1 if the tree is empty, prints 0 otherwise.\n"
            "'size': prints the current size of the tree\n"
            "'height': prints the current height of the tree\n"
            "'clear': clears the tree.\n"
            "'lower_bound x': prints the smallest value in the tree greater than or equal to x, prints -1 if no such value exists.\n"
            "'upper_bound x': prints the smallest value in the tree greater than x, prints -1 if no such value exists.\n"
            "'seed x l r' (l <= r): inserts x random values from l to r into the tree. Could cause collisions, inserting less nodes than entered.\n"
            "Could exceed memory limit with high enough x.\n"
            "'print x': prints the nodes in the tree in order of type x (1: pre-order, 2: in-order, 3: post-order, other values default to in-order).\n"
            "Could take some time to output if the tree size is large.\n"
            "'exit': terminates the program." << endl;
    
    while (true) {
        string s;
        cin >> s;
        long long a = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if (s == "insert") {
            int x;
            cin >> x;
            ptr->insert(x);
        } else if (s == "erase") {
            int x;
            cin >> x;
            ptr->erase(x);
        } else if (s == "erase_all") {
            int l, r;
            cin >> l >> r;
            for (int i = l; i <= r; ++i) ptr->erase(i);
        } else if (s == "find") {
            int x;
            cin >> x;
            cout << (ptr->find(x) != nullptr) << endl;
        } else if (s == "empty") {
            cout << ptr->empty() << endl;
        } else if (s == "size") {
            cout << ptr->size() << endl;
        } else if (s == "height") {
            cout << ptr->height() << endl;
        } else if (s == "clear") {
            ptr->clear();
        } else if (s == "lower_bound") {
            int x;
            cin >> x;
            cout << *ptr->lower_bound(x) << endl;
        } else if (s == "upper_bound") {
            int x;
            cin >> x;
            cout << *ptr->upper_bound(x) << endl;
        } else if (s == "seed") {
            int x, l, r;
            cin >> x >> l >> r;
            if (l <= r)
                while (x--) ptr->insert(max(0, (int) rnd()) % (r - l + 1) + l);
            else
                retry();
        } else if (s == "print") {
            int x;
            cin >> x;
            ptr->print(x);
        } else if (s == "exit") {
            break;
        } else {
            retry();
        }
        long long b = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout << "That took " << b - a << " ms." << endl;
    }
    
    
    return 0;
}
