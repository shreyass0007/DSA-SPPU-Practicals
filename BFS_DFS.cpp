// Represent a given graph using adjacency matrix/list to perform DFS and using adjacency 
// list to perform BFS. Use the map of the area around the college as the graph. Identify the 
// prominent land marks as nodes and perform DFS and BFS on that.

#include <iostream>
using namespace std;

const int MAX = 10;
int graph[MAX][MAX]; // Adjacency matrix
int visited[MAX];

void dfs(int start, int v) {
    int stack[MAX], top = -1;
    for (int i = 0; i < v; i++) visited[i] = 0;

    stack[++top] = start;

    while (top != -1) {
        int node = stack[top--];

        if (!visited[node]) {
            cout << node << " ";
            visited[node] = 1;

            for (int i = v - 1; i >= 0; i--) {
                if (graph[node][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
}

void bfs(int start, int v) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 0; i < v; i++) visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int node = queue[front++];
        cout << node << " ";

        for (int i = 0; i < v; i++) {
            if (graph[node][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int v, e;
    cout << "Enter number of nodes: ";
    cin >> v;

    cout << "Enter number of edges: ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        int a, b;
        cout << "Enter edge (a b): ";
        cin >> a >> b;
        graph[a][b] = 1;
        graph[b][a] = 1; // undirected
    }

    int start;
    cout << "Enter starting node (0 to " << v - 1 << "): ";
    cin >> start;

    cout << "\nDFS: ";
    dfs(start, v);

    cout << "\nBFS: ";
    bfs(start, v);

    return 0;
}
