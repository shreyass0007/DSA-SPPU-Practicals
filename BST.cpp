// // Beginning with an empty binary search tree, Construct binary search tree by inserting the 
// values in the order given. After constructing a binary tree -  
// i. Insert new node  
// ii. Find number of nodes in longest path from root 
// iii. Minimum data value found in the tree  
// iv. Change a tree so that the roles of the left and right pointers are swapped at every 
// node  
// v. Search a value  in the tree

#include<iostream>
#include<algorithm>
using namespace std;
class Node{
    public:
     int data=0;
        Node* left=NULL;
        Node* right=NULL;


};
class BST{
    public:
    Node* root=NULL;
    void insert(int val){

        Node* temp=new Node();
        temp->data=val;

        if(root==NULL){
            root=temp;
        }
        else{
            Node* current=root;
            Node* parent=NULL;
            while(current!=NULL){
                parent=current;
                if(val<current->data){
                    current=current->left;
                }
                else{
                    current=current->right;
                }
            }
            if(val<parent->data){
                parent->left=temp;
            }
            else{
                parent->right=temp;
            }
        }
            

    } 
    bool search(int val){
        Node* current=root;
        while(current!=NULL){
            if(current->data==val){
                return true;
            }
            else if(val<current->data){
                current=current->left;
            }
            else{
                current=current->right;
            }
        }
        return false;
    }
    int minValue(Node* root){
        Node* current=root;
        while(current->left!=NULL){
            current=current->left;
        }
        return current->data;
    }

    int maxValue(Node* root){
        Node* current=root;
        while(current->right!=NULL){
            current=current->right;
        }
        return current->data;
    }
    
    int height(Node* root){
        if(root==NULL){
            return 0;
        }
        else{
            int leftHeight=height(root->left);
            int rightHeight=height(root->right);
            return max(leftHeight,rightHeight)+1;
        }
    }
   
    void swap(Node* root){
        if(root==NULL){
            return;
        }
        swap(root->left);
        swap(root->right);
        Node* temp=root->left;
        root->left=root->right;
        root->right=temp;
    }
 
    void inorder(Node* root){
        if(root==NULL){
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }

    void prerder(Node* root){
        
        if(root==NULL){
            return;
        }
        
        cout<<root->data<<" ";
        prerder(root->left);
        prerder(root->right);
    }


    void postder(Node* root){
        
        if(root==NULL){
            return;
        }
        
        
        postder(root->left);
        postder(root->right);
        cout<<root->data<<" ";
    }
};
int main(){
   BST t;
   int choice;
   while(true){
         cout<<"1. Insert a node\n2. Find number of nodes in longest path from root\n3. Minimum data value found in the tree\n4. Change a tree so that the roles of the left and right pointers are swapped at every node\n5. Search a value  in the tree\n6. Traversal of the tree\n7. Exit\n";
         cout<<"Enter your choice:";
         cin>>choice;
         switch(choice){
              case 1:
                int val;
                cout<<"Enter value to be inserted: ";
                cin>>val;
                t.insert(val);
                break;
              case 2:
                cout<<"Number of nodes in longest path from root: "<<t.height(t.root)<<endl;
                break;
              case 3:
                cout<<"Minimum data value found in the tree: "<<t.minValue(t.root)<<endl;
                break;
              case 4:
                t.swap(t.root);
                cout<<"Tree after swapping left and right pointers at every node: ";
                t.inorder(t.root);
                cout<<endl;
                break;
              case 5:
                int searchVal;
                cout<<"Enter value to be searched: ";
                cin>>searchVal;
                if(t.search(searchVal)){
                     cout<<searchVal<<" is present in the tree."<<endl;
                }
                else{
                     cout<<searchVal<<" is not present in the tree."<<endl;
                }
                break;
              case 6:
                cout<<"Inorder Traversal of the Tree is:";
                t.inorder(t.root);
                cout<<endl;
                cout<<"Preorder Traversal of the Tree is:";
                t.prerder(t.root);
                cout<<endl;
                cout<<"Postorder Traversal of the Tree is:";
                t.postder(t.root);
                cout<<endl;
              case 7:
                exit(0);
              default:
                cout<<"Invalid choice! Please try again."<<endl;
         }

   }
}
