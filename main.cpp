#include <iostream>

#include "src/AVLTree.hpp"
using namespace std;
int main() {
    AVLTree tree;
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    cout << tree.serialize()<<endl;

    tree.deleteValue(6);
    string serialized = tree.serialize();
    cout << serialized <<endl;
    AVLTree reconstruct;
    reconstruct.deserialize(serialized);

    cout << reconstruct.serialize() << endl;
}
