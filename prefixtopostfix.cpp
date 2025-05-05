#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};

class ExpressionConverter {
private:
    Node* root;

    Node* buildTree(string& prefix) {
        if (prefix.empty()) return nullptr;
        
        char ch = prefix[0];
        prefix = prefix.substr(1);
        Node* node = new Node(ch);

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            node->left = buildTree(prefix);
            node->right = buildTree(prefix);
        }
        return node;
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);    // Process left
            postorder(node->right);   // Process right
            cout << node->data;       // Print current node
        }
    }

    void cleanup(Node* node) {
        if (node) {
            cleanup(node->left);
            cleanup(node->right);
            delete node;
        }
    }

public:
    ExpressionConverter() : root(nullptr) {}
    ~ExpressionConverter() { cleanup(root); }

    void convert(string prefix) {
        if (prefix.empty()) {
            cout << "Empty expression!" << endl;
            return;
        }

        root = buildTree(prefix);
        cout << "Postfix expression: ";
        postorder(root);
        cout << endl;
    }
};

int main() {
    string prefix;
    cout << "Enter prefix expression: ";
    cin >> prefix;
    ExpressionConverter converter;
    converter.convert(prefix);
    return 0;
}
