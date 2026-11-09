#include "AVLTree.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

AVLTree::Node::Node(int value)
: value(value), height(1), left(nullptr), right(nullptr) {}
//helper functions

int AVLTree::getHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}
int AVLTree::getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) -
        getHeight(node->right);
}
void AVLTree::updateHeight(Node* node) {
    if (!node) return;
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
}
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* subtree = x->right;

    x->right = y;
    y->left = subtree;

    updateHeight(y);
    updateHeight(x);

    return x;
}
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* subtree = y->left;

    y->left = x;
    x->right = subtree;

    updateHeight(x);
    updateHeight(y);

    return y;
}
AVLTree::Node* AVLTree::findMin(Node* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}
AVLTree::Node* AVLTree::rebalance(Node* node) {
    if (!node) return nullptr;
    updateHeight(node);
    int balance = getBalance(node);
    // Left heavy
    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Right-heavy
    if (balance < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}
AVLTree::Node* AVLTree::insertNode(Node* node, int value) {
    if (!node) {
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    }
    else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    else {
        return node;
    }

    return rebalance(node);
}

AVLTree::Node* AVLTree::deleteNode(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    }
    else {
        if (!node->left || !node->right) {
            Node* child = node->left ? node->left : node->right;
            delete node;
            return child;
        }
        //to get the successor
        Node* replacement = findMin(node->right);

        node->value = replacement->value;

        node->right = deleteNode(
            node->right,
            replacement->value
        );
    }

    return rebalance(node);
}
void AVLTree::serializeNode(Node* node, stringstream& output) {
    if (!node) {
        output << "#,";
        return;
    }
    output << node->value << ",";
    serializeNode(node->left, output);
    serializeNode(node->right, output);
}
AVLTree::Node* AVLTree::deserializeNode(const vector<string>& ser,size_t& index) {
    if (ser[index] == "#") {
        index++;
        return nullptr;
    }

    Node* node = new Node(stoi(ser[index]));
    index++;
    node->left = deserializeNode(ser, index);
    node->right = deserializeNode(ser, index);

    updateHeight(node);

    return node;
}
void AVLTree::insert(int value) {
    root = insertNode(root, value);
}
void AVLTree::deleteValue(int value) {
    root = deleteNode(root, value);
}
string AVLTree::serialize() {
    stringstream output;
    serializeNode(root, output);
    string result = output.str();
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}
void AVLTree::deserialize(string str) {
    vector<string> sers;
    stringstream input(str);
    string ser;

    while (getline(input, ser, ',')) {
        sers.push_back(ser);
    }

    size_t index = 0;

    root = deserializeNode(sers, index);
}
