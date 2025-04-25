#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void min_heapify(vector<int>& arr, int i, int n) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) smallest = left;
    if (right < n && arr[right] < arr[smallest]) smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        min_heapify(arr, smallest, n);
    }
}

void max_heapify(vector<int>& arr, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        max_heapify(arr, largest, n);
    }
}
int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    vector<int> marks(n);
    cout << "Enter the marks obtained by students: ";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }
    vector<int> max_heap_marks = marks;
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(max_heap_marks, i, n);
    }
    cout << "Maximum marks obtained: " << max_heap_marks[0] << endl;

    vector<int> min_heap_marks = marks;
    for (int i = n / 2 - 1; i >= 0; i--) {
        min_heapify(min_heap_marks, i, n);
    }
    cout << "Minimum marks obtained: " << min_heap_marks[0] << endl;

    return 0;
}