#include <iostream>
#include <climits> // Fix for INT_MAX

using namespace std;

class Graph {
private:
    int n; // Number of cities
    int **cost; // Adjacency matrix
    bool *visited; // Visited nodes

public:
    Graph(int nodes) {
        n = nodes;
        cost = new int*[n];
        visited = new bool[n];
        for (int i = 0; i < n; i++) {
            cost[i] = new int[n];
            visited[i] = false;
            for (int j = 0; j < n; j++) {
                cost[i][j] = -1;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < n; i++) {
            delete[] cost[i];
        }
        delete[] cost;
        delete[] visited;
    }

    void addEdge(int u, int v, int weight) {
        cost[u][v] = weight;
        cost[v][u] = weight;
    }

    void primMST() {
        visited[0] = true;
        int mincost = 0;

        cout << "\nEdges in MST:\n";

        for (int k = 0; k < n - 1; k++) {
            int min = INT_MAX; // Fix 1: Declare INT_MAX
            int row = -1, col = -1; // Fix 2: Declare row and col before loops
            
            for (int i = 0; i < n; i++) {
                if (visited[i]) {
                    for (int j = 0; j < n; j++) {
                        if (!visited[j] && cost[i][j] != -1 && cost[i][j] < min) {
                            min = cost[i][j];
                            row = i;
                            col = j;
                        }
                    }
                }
            }
            
            if (row != -1 && col != -1) {
                visited[col] = true;
                mincost += min;
                cout << row + 1 << " -> " << col + 1 << " (Weight: " << min << ")\n";
            }
        }
        cout << "\nMinimum Cost: " << mincost << "\n";
    }
};

int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;
    
    Graph g(n);
    
    char op;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Do you want a connection between city " << i + 1 << " and city " << j + 1 << "? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y') {
                int weight;
                cout << "Enter weight: ";
                cin >> weight;
                g.addEdge(i, j, weight);
            }
        }
    }
    
    g.primMST();
    return 0;
}