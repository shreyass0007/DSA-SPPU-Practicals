#include <iostream>
#include <string>
#include <limits>   // For numeric_limits
using namespace std;

// Helper function to get a validated integer input.
int getValidatedInteger(const string &prompt) {
    int number;
    while (true) {
        cout << prompt;
        if (cin >> number) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the newline
            break;  // Valid integer was entered
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();  // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    return number;
}

struct Node {
    string label;         // Label for the node (chapter, section, or subsection)
    int childCount;       // Current count of child nodes
    Node* children[10];   // Fixed-size array to hold child nodes (max 10 per node)

    // Constructor: optionally initialize with a label
    Node(const string& lbl = "") : label(lbl), childCount(0) {
        for (int i = 0; i < 10; ++i)
            children[i] = nullptr;
    }

    // Destructor: Recursively delete all child nodes
    ~Node() {
        for (int i = 0; i < childCount; ++i)
            delete children[i];
    }
};

class BookTree {
public:
    Node* root;

    // Constructor: Create the root node with a label "Book"
    BookTree() {
        root = new Node("Book");
    }

    // Destructor: Delete the root node, which recursively deletes the entire tree.
    ~BookTree() {
        delete root;
    }

    // Adds a chapter node under the root.
    void addChapter(const string& chapterLabel) {
        if (root->childCount >= 10) {
            cout << "Maximum chapters reached!" << endl;
            return;
        }
        Node* chapterNode = new Node(chapterLabel);
        root->children[root->childCount++] = chapterNode;
    }

    // Adds a section node under the given chapter node.
    void addSection(Node* chapterNode, const string& sectionLabel) {
        if (chapterNode == nullptr || chapterNode->childCount >= 10) {
            cout << "Cannot add more sections to chapter \"" 
                 << (chapterNode ? chapterNode->label : "Unknown") << "\"!" << endl;
            return;
        }
        Node* sectionNode = new Node(sectionLabel);
        chapterNode->children[chapterNode->childCount++] = sectionNode;
    }

    // Adds a subsection node under the given section node.
    void addSubsection(Node* sectionNode, const string& subsectionLabel) {
        if (sectionNode == nullptr || sectionNode->childCount >= 10) {
            cout << "Cannot add more subsections to section \"" 
                 << (sectionNode ? sectionNode->label : "Unknown") << "\"!" << endl;
            return;
        }
        Node* subsectionNode = new Node(subsectionLabel);
        sectionNode->children[sectionNode->childCount++] = subsectionNode;
    }

    // Recursively prints the tree with indentation representing hierarchy.
    void printTree(Node* node, int level = 0) const {
        if (node == nullptr)
            return;
        for (int i = 0; i < level; ++i)
            cout << "  ";
        cout << node->label << endl;
        for (int i = 0; i < node->childCount; ++i)
            printTree(node->children[i], level + 1);
    }
};

int main(){
    BookTree* book = nullptr;  // Pointer to BookTree to allow re-creation
    int choice;

    while (true) {
        cout << "\n1. Create\n2. Display\n3. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush the newline

        if (choice == 1) {
            // Clear existing tree if it exists.
            if (book != nullptr) {
                delete book;
                book = nullptr;
            }
            book = new BookTree();

            int numChapters = getValidatedInteger("Enter number of chapters: ");
            for (int i = 0; i < numChapters; i++) {
                string chapterLabel;
                cout << "\nEnter label for chapter " << i + 1 << ": ";
                getline(cin, chapterLabel);
                book->addChapter(chapterLabel);

                int numSections = getValidatedInteger("Enter number of sections for chapter \"" + chapterLabel + "\": ");
                // Pointer to the chapter just added.
                Node* chapterNode = book->root->children[book->root->childCount - 1];

                for (int j = 0; j < numSections; j++) {
                    string sectionLabel;
                    cout << "\n  Enter label for section " << j + 1 << " in chapter \"" << chapterLabel << "\": ";
                    getline(cin, sectionLabel);
                    book->addSection(chapterNode, sectionLabel);

                    int numSubsections = getValidatedInteger("  Enter number of subsections for section \"" + sectionLabel + "\": ");
                    // Pointer to the section just added.
                    Node* sectionNode = chapterNode->children[chapterNode->childCount - 1];

                    for (int k = 0; k < numSubsections; k++){
                        string subsectionLabel;
                        cout << "    Enter label for subsection " << k + 1 << " in section \"" << sectionLabel << "\": ";
                        getline(cin, subsectionLabel);
                        book->addSubsection(sectionNode, subsectionLabel);
                    }
                }
            }
            
        } else if (choice == 2) {
            if (book == nullptr) {
                cout << "No book created yet. Please choose 'Create' first." << endl;
            } else {
                cout << "\nBook Tree Structure:" << endl;
                book->printTree(book->root);
            }
        } else if (choice == 3) {
            // Clean up the allocated book tree before exiting.
            if (book != nullptr) {
                delete book;
                book = nullptr;
            }
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
