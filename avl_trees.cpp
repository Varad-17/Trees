#include<bits/stdc++.h>

using namespace std;

class avl_node 
{
 private : 
 int height;
 avl_node* left;
 avl_node* right;
 int value;
 friend class avl_tree;
 friend int get_height(avl_node* node)
 {
  if (node == NULL) return 0 ;
  return node->height;
 }

 friend void rotate_left(avl_node* &node);
 friend void rotate_right(avl_node* &node);

 public:
 avl_node(int h, int val)
 {
    height = h;
    left = NULL;
    right = NULL;
    value = val;
 }
 
 ~avl_node()
 {
   delete left;
   delete right;
 }
};

void rotate_left(avl_node* &node)
{
   avl_node* right_child = node->right;
   avl_node* node_child = right_child->left;
   node->right = node_child;
   right_child->left = node;

   node->height = max(get_height(node->left), get_height(node->right)) + 1;
   right_child->height = max(get_height(right_child->left), get_height(right_child->right)) + 1;
   node = right_child;
 }

 void rotate_right(avl_node* &node)
 {
   avl_node* left_child = node->left;
   avl_node* node_child = left_child->right;
   node->left = node_child;
   left_child->right = node;

  node->height = max(get_height(node->left), get_height(node->right)) + 1;
  left_child->height = max(get_height(left_child->left), get_height(left_child->right)) + 1;
  node = left_child;
 }

class avl_tree
{
  public :
  avl_node* root;
  avl_tree(int value)
  {
    root = new avl_node(0, value);
  }
  
  void find(avl_node* node, int element)
  {
    if(node == NULL)
    {
     cout<<"Element "<<element<<" not found in the tree"<<endl;
     return;
    }

    else if(node->value == element)
    {
      cout<<"Element "<<element<<" found in the tree"<<endl;
      return;
    }

    else if (element  < node->value) find(node->left, element);
    else find (node -> right, element);
  }

  void insert(int element, avl_node * &TreeNode)
  {
    if(TreeNode == NULL) 
    {
        TreeNode = new avl_node(1, element);
        if (TreeNode == NULL) cout<<"Error: Tree is out of space"<<endl;
        return;
    }
      
    else if(element < TreeNode->value) insert(element, TreeNode->left);
    else if (element > TreeNode->value) insert(element, TreeNode->right);
    
    else 
    {
      cout<<"Error: The element is already in the tree"<<endl;
      return;
    }

    TreeNode->height = max(get_height(TreeNode->left), get_height(TreeNode->right)) +1;

    int balance = get_height(TreeNode->left) - get_height(TreeNode->right);

    if (balance > 1 )
    {
      if(element < (TreeNode->left)->value)
      {
        rotate_right(TreeNode);
      }

      else 
      {
        rotate_left(TreeNode->left);
        rotate_right(TreeNode);
      }
    }
    else if (balance < -1)
    {
      if(element > (TreeNode->right)->value)
      {
        rotate_left(TreeNode);
      }

      else 
      {
        rotate_right(TreeNode->right);
        rotate_left(TreeNode);
      }
    }
    
  }

    void preOrder(avl_node *root)
  {
    if(root != NULL)
    {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
  }
  
  avl_node* Find_min(avl_node* search)
  {
    while(search->left != NULL) 
    {
      search = search->left;
    }
    return search;
  }

  void delete_avl_node(avl_node* &TreeNode, int del)
  {
   if(TreeNode == NULL)
   {
    cout<<"ERROR: Element "<<del<<" not found in the tree!"<<endl;
    return;
   }
   else if(del < TreeNode->value) delete_avl_node(TreeNode->left, del);
   else if(del > TreeNode->value) delete_avl_node(TreeNode->right, del);
   else 
   {
     if(TreeNode->left == NULL && TreeNode->right == NULL) TreeNode = NULL;
     else if (TreeNode->left != NULL && TreeNode->right != NULL) 
     {
       avl_node* delete_node = Find_min(TreeNode->right);
       TreeNode->value = delete_node->value;
       delete_avl_node(TreeNode->right,delete_node->value);
     }
     else if (TreeNode->left != NULL) TreeNode = TreeNode->left;
     else TreeNode = TreeNode->right;
   }

   TreeNode->height = max(get_height(TreeNode->left), get_height(TreeNode->right)) +1;

    int balance = get_height(TreeNode->left) - get_height(TreeNode->right);

    if(balance  > 1)
    {
      avl_node* child_node = TreeNode->left;
      int new_balance = get_height(child_node->left) - get_height(child_node->right);
      if(new_balance >= 0) rotate_right(TreeNode);
      else 
      {
        rotate_left(TreeNode->left);
        rotate_right(TreeNode);
      }
    }

    else if(balance < -1)
    {
      avl_node* child_node = TreeNode->right;
      int new_balance = get_height(child_node->left) - get_height(child_node->right);
      if(new_balance <= 0 ) rotate_left(TreeNode);
      else 
      {
        rotate_right(TreeNode->right);
        rotate_left(TreeNode);
      }
    }
  }


};

int main()
{
  avl_tree myTree(9);
  avl_node* root = myTree.root;
  myTree.insert(5,root);
  myTree.insert(10,root);
  myTree.insert(0,root);
  myTree.insert(6,root);
  myTree.insert(11,root);
  myTree.insert(-1,root);
  myTree.insert(1,root);
  myTree.insert(2,root);
  myTree.find(root, 10);
  cout << "\nPreorder traversal of the constructed AVL Tree is"<<endl;
  myTree.preOrder(root);
  myTree.delete_avl_node(root, 10);
  cout << "\nPreorder traversal after"
         << " deletion of 10 \n";
  myTree.preOrder(root);
  cout<<endl;
  myTree.find(root, 10);
    return 0;
}
