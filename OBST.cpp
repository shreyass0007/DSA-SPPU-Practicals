#include <iostream>
using namespace std;

#define SIZE 10

class OBST {
    int p[SIZE];  // Success probabilities (probabilities with which we search for an element)
    int a[SIZE];  // Elements from which OBST is to be built
    int w[SIZE][SIZE];  // Weight 'w[i][j]' of a tree having root 'r[i][j]'
    int c[SIZE][SIZE];  // Cost 'c[i][j]' of a tree having root 'r[i][j]'
    int r[SIZE][SIZE];  // Represents root
    int n;  // Number of nodes

public:
    // Accept input data (probabilities for the success of each search)
    void get_data() {
        int i;
        cout << "\nOptimal Binary Search Tree\n";
        cout << "\nEnter the number of nodes: ";
        cin >> n;

        cout << "\nEnter the data (keys):\n";
        for (i = 1; i <= n; i++) {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }

        cout << "\nEnter the success probabilities (p[i]):\n";
        for (i = 1; i <= n; i++) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }
    }

    // Function to calculate the optimal root (the index that minimizes cost)
    int Min_Value(int i, int j) {
        int m, k;
        int minimum = 32000;  // A large number (substitute for infinity)
        for (m = r[i][j - 1]; m <= r[i + 1][j]; m++) {
            if ((c[i][m - 1] + c[m][j]) < minimum) {
                minimum = c[i][m - 1] + c[m][j];
                k = m;
            }
        }
        return k;
    }

    // Function to build the OBST DP table for cost, weights, and roots
    void build_OBST() {
        int i, j, k, m;

        // Initialize the base cases for single node trees
        for (i = 0; i <= n; i++) {
            w[i][i] = 0; //Change from p[i] to 0, because we are using 1 based indexing for p, and 0 for dummy value.
            c[i][i] = 0;  // No cost for a tree with no nodes
            r[i][i] = 0;  // No root for a tree with no nodes
        }

        // Initialize the weight for the tree with a single node
        for (i = 0; i < n; i++) {
            w[i][i + 1] = p[i + 1]; //Corrected to p[i+1]
            c[i][i + 1] = p[i + 1]; //Corrected to p[i+1]
            r[i][i + 1] = i + 1;  // Root of the tree with 2 nodes
        }

        // Calculate the weight and cost for trees of length > 2
        for (m = 2; m <= n; m++) {  // m is the length of the tree
            for (i = 0; i <= n - m; i++) {  // i is the start index
                j = i + m;  // j is the end index

                // Calculate weight w[i][j] (sum of probabilities for keys i to j)
                w[i][j] = w[i][j - 1] + p[j];

                // Find the optimal root that minimizes the cost
                k = Min_Value(i, j);
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];  // Total cost calculation
                r[i][j] = k;  // Store the root for the optimal tree
            }
        }
    }

    // Function to recursively display the tree structure
    void build_tree(int i, int j) {
        if (i > j) {
            return;  // Base case: no elements, return
        }

        int root = r[i][j];
        if (root == 0) return;  // If there is no root for this subtree, do nothing

        // Print root
        cout << "\n\t" << a[root];

        // Left child: check if there is a valid left subtree (i.e., a valid root exists)
        if (root - 1 >= i && r[i][root - 1] != 0) {
            cout << "\t\t" << a[r[i][root - 1]];
        } else {
            cout << "\t\t-"; // changed to '-' to represent null
        }

        // Right child: check if there is a valid right subtree (i.e., a valid root exists)
        if (root + 1 <= j && r[root][j] != 0) {
            cout << "\t" << a[r[root][j]];
        } else {
            cout << "\t-"; // changed to '-' to represent null
        }

        // Recursively display the left and right subtrees
        build_tree(i, root - 1);  // Left subtree
        build_tree(root, j);  // Right subtree
    }

    // Function to display the OBST
    void display_tree() {
        cout << "\nThe Optimal Binary Search Tree for the Given Node is:\n";
        cout << "The Root of this OBST is: " << a[r[0][n]] << endl;
        cout << "The Cost of this OBST is: " << c[0][n] << endl;

        cout << "\n\n\t NODE \t LEFT CHILD \t RIGHT CHILD\n";
        build_tree(0, n);  // Start recursion from the root of the whole tree
    }
};

// Main function
int main() {
    OBST obj;
    obj.get_data();  // Get input data
    obj.build_OBST();  // Build the OBST DP table
    obj.display_tree();  // Build and display the OBST structure
    return 0;
}