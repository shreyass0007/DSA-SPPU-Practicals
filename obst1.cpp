//Given sequence k=k1<k2 ...<kn of n sorted keys with a searh 
//probability pi for each key ki. Build the Binary Search tree 
//that has the least search cost given the accesss probabilities
//for neach key.


#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include <string>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

const int MAX = 21;
float p[MAX], q[MAX], w[MAX][MAX], c[MAX][MAX];
int r[MAX][MAX];
int n;

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string v) : val(v), left(nullptr), right(nullptr) {}
};

void constructOBST() {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        w[i][j] = w[i][i] + p[j] + q[j];
        c[i][j] = w[i][j];
        r[i][j] = j;
    }

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = FLT_MAX;
            for (int k = i + 1; k <= j; k++) {
                float cost = c[i][k - 1] + c[k][j] + w[i][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }
}

TreeNode* buildTree(int i, int j) {
    if (i >= j) return new TreeNode("null");
    int root = r[i][j];
    TreeNode* node = new TreeNode("k" + to_string(root));
    node->left = buildTree(i, root - 1);
    node->right = buildTree(root, j);
    return node;
}

int getHeight(TreeNode* root) {
    if (!root || root->val == "null") return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

void fillMatrix(TreeNode* root, vector<vector<string>>& res, int row, int left, int right) {
    if (!root || row >= res.size() || root->val == "null") return;

    int mid = (left + right) / 2;
    res[row][mid] = root->val;

    fillMatrix(root->left, res, row + 1, left, mid - 1);
    fillMatrix(root->right, res, row + 1, mid + 1, right);
}

void printPrettyTree(TreeNode* root) {
    int height = getHeight(root);
    int width = (1 << height) - 1;

    vector<vector<string>> res(height, vector<string>(width, " "));

    fillMatrix(root, res, 0, 0, width - 1);

    for (const auto& row : res) {
        for (const auto& cell : row) {
            cout << (cell.empty() ? " " : cell);
        }
        cout << "\n";
    }
}

// cleanup
void deleteTree(TreeNode* root) {
    if (!root || root->val == "null") return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "Enter number of keys (1 - 20): ";
    cin >> n;
    if (n < 1 || n > 20) {
        cout << "Invalid input." << endl;
        return 1;
    }

    cout << "\nEnter probabilities for successful searches (p[1] to p[" << n << "]):\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "] = ";
        cin >> p[i];
    }

    cout << "\nEnter probabilities for unsuccessful searches (q[0] to q[" << n << "]):\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "] = ";
        cin >> q[i];
    }

    float total = 0;
    for (int i = 1; i <= n; i++) total += p[i];
    for (int i = 0; i <= n; i++) total += q[i];
    if (fabs(total - 1.0f) > 0.001f) {
        cout << "\nError: Total probability must sum to 1. Current = " << total << endl;
        return 1;
    }

    constructOBST();
    TreeNode* root = buildTree(0, n);

    cout << "\nOptimal Binary Search Tree (OBST):\n\n";
    printPrettyTree(root);

    cout << "\nMinimum cost of OBST: " << fixed << setprecision(4) << c[0][n] << endl;

    deleteTree(root);
    return 0;
}

