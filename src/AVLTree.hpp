#include <vector>
#include <string>
#include <sstream>

class AVLTree {
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;

        Node(int value);
    };

    Node* root = nullptr;

    int getHeight(Node* node);
    int getBalance(Node* node);
    void updateHeight(Node* node);

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* findMin(Node* node);
    Node* rebalance(Node* node);

    Node* insertNode(Node* node, int value);
    Node* deleteNode(Node* node, int value);

    void serializeNode(Node* node, std::stringstream& output);
    Node* deserializeNode(const std::vector<std::string>& ser, size_t& index);
public:
    void insert(int value);
    void deleteValue(int value);
    std::string serialize();
    void deserialize(std::string str);
};
