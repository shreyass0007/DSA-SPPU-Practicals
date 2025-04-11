// Construct an expression tree from the given prefix expression eg. +--a*bc/def and 
// traverse it using postordertraversal(non recursive) and then delete the entire tree. 


#include <iostream>
#include <string>
#include <cctype> // For isalpha

using namespace std;

// Node structure for the expression tree
struct Node {
    char data;
    Node* left;
    Node* right;
    
    // Constructor to initialize the node
    Node(char c) : data(c), left(nullptr), right(nullptr) {}
};

// Custom stack implementation for Node pointers
class CustomStack {
    static const int MAX_SIZE = 50; // Maximum capacity for the stack
    Node* data[MAX_SIZE];
    int top;
    
public:
    CustomStack() : top(-1) {}
    
    // Check if the stack is empty
    bool empty() const {
        return top == -1;
    }
    
    // Check if the stack is full
    bool full() const {
        return top == MAX_SIZE - 1;
    }
    
    // Push a node pointer onto the stack
    void push(Node* ptr) {
        if (!ptr) {
            cout << "Cannot push null pointer!" << endl;
            return;
        }
        if (full()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        data[++top] = ptr;
    }
    
    // Pop a node pointer from the stack
    Node* pop() {
        if (empty()) {
            cout << "Stack Underflow! Returning nullptr." << endl;
            return nullptr;
        }
        return data[top--];
    }
};

// Class to handle the expression tree and its traversals
class ExpressionTree {
public:
    Node* root;

    ExpressionTree() : root(nullptr) {}

    // Function to construct the tree from a prefix expression using a custom stack
    void buildTree(const string& prefix) {
        if (prefix.empty()) {
            cout << "Empty expression!" << endl;
            return;
        }
        CustomStack stack;
        
        // Process the expression from right to left.
        for (int i = prefix.size() - 1; i >= 0; --i) {
            char ch = prefix[i];
            Node* newNode = new Node(ch);
            
            // If the character is an operand, push it onto the stack.
            if (isalpha(ch)) {
                stack.push(newNode);
            }
            // If the character is an operator, pop two operands.
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                Node* leftChild = stack.pop();
                Node* rightChild = stack.pop();
                newNode->left = leftChild;
                newNode->right = rightChild;
                stack.push(newNode);
            }
        }
        
        // The remaining node in the stack is the root of the tree.
        root = stack.pop();
    }

    // Recursive preorder traversal (root, left, right)
    void preorder(Node* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    // Recursive inorder traversal (left, root, right)
    void inorder(Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    // Non-recursive postorder traversal using two custom stacks
    void nonRecursivePostorder() {
        if (!root) return;
        
        CustomStack s1, s2;
        s1.push(root);
        
        while (!s1.empty()) {
            Node* current = s1.pop();
            s2.push(current);
            
            // Push left and right children if they exist
            if (current->left)
                s1.push(current->left);
            if (current->right)
                s1.push(current->right);
        }
        
        cout << "\nPostorder Traversal: ";
        while (!s2.empty()) {
            cout << s2.pop()->data << " ";
        }
        cout << endl;
    }

    // Recursively delete the tree to free memory
    void deleteTree(Node*& node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        cout << "Deleting node: " << node->data << endl;
        delete node;
        node = nullptr;
    }

    // Add this function in the ExpressionTree class
    void displayTree(Node* root, int level = 0, char prefix = ' ') {
        if (root == nullptr) return;
        
        // Display right subtree
        displayTree(root->right, level + 1, '/');
        
        // Display current node
        for (int i = 0; i < level; i++) {
            cout << "   ";
        }
        cout << prefix << "--" << root->data << endl;
        
        // Display left subtree
        displayTree(root->left, level + 1, '\\');
    }

    // Destructor to ensure that allocated memory is freed
    ~ExpressionTree() {
        deleteTree(root);
    }
};

int main() {
    ExpressionTree exprTree;
    int choice;
    string expression;
    
    do {
        cout << "\nMenu:";
        cout << "\n1. Enter Prefix Expression";
        cout << "\n2. Construct Expression Tree";
        cout << "\n3. Display Tree (Preorder & Inorder)";
        cout << "\n4. Non-recursive Postorder Traversal";
        cout << "\n5. Delete Tree";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter prefix expression (without spaces): ";
                cin >> expression;
                break;
            case 2:
                exprTree.buildTree(expression);
                cout << "Expression tree constructed successfully!" << endl;
                break;
            case 3:
                if (exprTree.root) {
                    cout << "\nTree Structure:\n";
                    exprTree.displayTree(exprTree.root);
                    cout << "\nPreorder Traversal: ";
                    exprTree.preorder(exprTree.root);
                    cout << "\nInorder Traversal: ";
                    exprTree.inorder(exprTree.root);
                    cout << "\n";
                } else {
                    cout << "Tree does not exist!" << endl;
                }
                break;
            case 4:
                exprTree.nonRecursivePostorder();
                break;
            case 5:
                exprTree.deleteTree(exprTree.root);
                cout << "Tree deleted successfully!" << endl;
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);
    
    return 0;
}
