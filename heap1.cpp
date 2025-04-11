// Read the marks obtained by students of second year in an online examination of 
// particular subject. Find out maximum and minimum marks obtained in that subject. Use 
// heap data structure. Analyze the algorithm.

#include<iostream>
using namespace std;
//min Heap
void min_insert(int arr[],int i){
    int parent=(i-1)/2;
    int cur=i;
    while (parent>=0 && arr[parent]>arr[cur]){
        swap(arr[parent],arr[cur]);
        cur=parent;
        parent=(cur-1)/2;
    }
}
//max heap
void max_insert(int arr[],int i){
    int parent=(i-1)/2;
    int cur=i;
    while (parent>=0 && arr[parent]<arr[cur]){
        swap(arr[parent],arr[cur]);
        cur=parent;
        parent=(cur-1)/2;
    }       
}
int main(){
    int n;
    cout<<"Enter the number of students: ";
    cin>>n;
    int arr[n];
    
    cout<<"Enter the marks obtained by students: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<n;i++){
        max_insert(arr,i);  
     }
     cout<<"Max heap: "<<arr[0]<<endl;
     for(int i=0;i<n;i++){
         cout<<arr[i]<<" ";
      }
      cout<<endl;

      for(int i=1;i<n;i++){
        min_insert(arr,i);
        
     }
     cout<<"Min heap: "<<arr[0]<<endl;
     for(int i=0;i<n;i++){
         cout<<arr[i]<<" ";
      }
      cout<<endl;
    cout<<"Maximum marks obtained: "<<arr[n-1]<<endl;  // Fixed index
    cout<<"Minimum marks obtained: "<<arr[0]<<endl;
}


