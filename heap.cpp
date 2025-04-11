// Read the marks obtained by students of second year in an online examination of
// particular subject. Find out maximum and minimum marks obtained in that subject. Use
// heap data structure. Analyze the algorithm for time and space complexity.
#include<iostream>
#include<algorithm>
using namespace std;
class Heap1{
    public:

    void MAX_HEAPIFY(int arr[],int i, int n){
        int l,r,largest;
        l=2*i+1; // left child
        r=2*i+2; // right child
        if(l<n && arr[l]>arr[i]){
            largest=l;
        }
        else{
            largest=i;

        }
        if(r<n && arr[r]>arr[largest]){  // Fixed condition
            largest=r;
        }
        if(largest!=i){
            swap(arr[i],arr[largest]);
            MAX_HEAPIFY(arr,largest,n);
        }
        
    }
    void BUILD_MAX_HEAP(int arr[],int n){
        for(int i=n/2-1;i>=0;i--){
            MAX_HEAPIFY(arr,i,n);
        }
    }
    void HEAP_SORT(int arr[],int n){
        BUILD_MAX_HEAP(arr,n);
        for(int i=n-1;i>=0;i--){
            swap(arr[0],arr[i]);
            MAX_HEAPIFY(arr,0,i-1);
        }
    }

    void accept(){
        int n;
        cout<<"Enter the number of students: ";
        cin>>n;
        int arr[n];
        cout<<"Enter the marks obtained by students: ";
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        HEAP_SORT(arr,n);
        display(arr,n);
    }
    void display(int arr[],int n){
        cout<<"Marks obtained by students in sorted order: ";
        for(int i=0;i<n;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;

        cout<<"Maximum marks obtained: "<<arr[n-1]<<endl;  // Fixed index
        cout<<"Minimum marks obtained: "<<arr[0]<<endl;
    }


};
int main(){
    Heap1 h;
    h.accept();
    return 0;
}