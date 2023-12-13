#include "AVLTree.cc"
#include <iostream>

int T, Q, key;
string order;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;

    while (T--) {
        cin >> Q;
        AVLTree avlTree;

        while (Q--) {
            cin >> order;
            if (order == "minimum") {
                cin >> key;
                avlTree.minimum(key);
            }
            else if (order == "maximum") {
                cin >> key;
                avlTree.maximum(key);
            }
            else if (order == "empty") {
                avlTree.empty();
            }
            else if (order == "size") {
                avlTree.size();
            }
            else if (order == "find") {
                cin >> key;
                avlTree.find(key);
            }
            else if (order == "insert") {
                cin >> key;
                avlTree.insert(key);
            }
            else if (order == "rank") {
                cin >> key;
                avlTree.rank(key);
            }
            else if (order == "erase") {
                cin >> key;
                avlTree.erase(key);
            }
        }
    }
}