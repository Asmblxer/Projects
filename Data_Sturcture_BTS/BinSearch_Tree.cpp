#include <bits/stdc++.h>
using namespace std;

struct node {
     int data;
     node *left, *right;

     node(int info = 0) {
          this -> data = info;
          left = right = nullptr;
     }
};

struct BST {

     // Insert New node

     node* Insert(node* root, int val){
          if(!root) return new node(val);
          if(val > root -> data)
               root -> right = Insert(root -> right, val);
          else
               root -> left = Insert(root -> left, val);
          return root;
     }

     // Inorder Traverse

     void Inorder(node* root){
          if(!root) return;
          Inorder(root -> left);
          cout << root -> data << " ";
          Inorder(root -> right);
     }

     // Preorde Traverse

     void Preorder(node* root){
          if(!root) return;
          cout << root -> data << " ";
          Preorder(root -> left);
          Preorder(root -> right);
     }

     // Postorder Traverse 

     void Postorder(node* root){
          if(!root) return;
          Postorder(root -> left);
          Postorder(root -> right);
          cout << root -> data << " ";
     }

     // Search on a node

     bool Search(node* root, int val){
        if(!root) return false;
        if(root -> data == val) return true;
        if(val > root -> data) return Search(root -> right, val);
        else return Search(root -> left, val);
     }

     // Get minimum node in BST

     node* minValueNode(node* Node){
          node* current = Node;
          while (current && current -> left != nullptr) current = current -> left;
          return current;
     }

     // Get maximum node in BST

     node* maxValueNode(node* Node){
        node* current = Node;
        while (current && current -> right != nullptr) current = current -> right;
        return current;
     }

     // Delete Node

     node* Delete_Node(node* root, int key){
          if(!root) return root;
          if(key < root -> data)
               root -> left = Delete_Node(root -> left, key);
          else if(key > root -> data)
               root -> right = Delete_Node(root -> right, key);
          else {
               if(!root -> left && !root -> right) return nullptr;
               else if(!root -> left){
                    node* temp = root -> right;
                    free(root);
                    return temp;
               }else if(!root -> right){
                    node* temp = root -> left;
                    free(root);
                    return temp;
               }
               node* temp = minValueNode(root -> right);
               root -> data = temp -> data;
               root -> right = Delete_Node(root -> right, temp -> data);
          }
          return root;
     }
};

int main() {
     BST tree;
     node *root;
     cout <<"Welecome to my binery search tree \n";
     while (true) {
          cout <<"\n\nNow you can do the next operations\n\n"
          <<"1 : insert a new node to the tree\n"
          <<"2 : search on a node in the tree\n"
          <<"3 : delete a node in the tree\n"
          <<"4 : get the biggest node on the tree\n"
          <<"5 : get the smallest node on the tree\n"
          <<"6 : inorder traverse\n"
          <<"7 : preorder traverse\n"
          <<"8 : postorder traverse\n"
          <<"To quit enter 0\n\n"
          <<"Enter you option : ";
          int op;   cin >> op;
          if (op == 1) {
               cout <<"\nEnter value to insert : ";
               int tmp;  cin >> tmp;
               root = tree.Insert(root, tmp);
          }
          else if (op == 2) {
               cout <<"\nEnter value to search : ";
               int tmp;  cin >> tmp;
               cout <<(tree.Search(root, tmp) ? "\nFound":"\nNot Found");
          }
          else if (op == 3) {
               cout <<"\nEnter value to delete : ";
               int tmp;  cin >> tmp;
               root = tree.Delete_Node(root, tmp);
          }
          else if (op == 4) {
               cout <<"\n The Biggest value in the tree is : "
               << tree.maxValueNode(root)-> data;
          }
          else if (op == 5) {
               cout <<"\n The Biggest value in the tree is : "
               << tree.minValueNode(root)-> data;
          }
          else if (op == 6) {
               cout <<"\ninorder traverse : ";
               tree.Inorder(root);
          }
          else if (op == 7) {
               cout <<"\npreorder traverse : ";
               tree.Preorder(root);
          }
          else if (op == 8) {
               cout <<"\npostorder traverse : ";
               tree.Postorder(root);
          }
          else break;
          cout <<"\n\nDo you want to do another operation (y/n) : ";
          string s; cin >> s;
          if(s != "y") break; 
     }
     return 0;
}
