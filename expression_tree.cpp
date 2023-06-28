#include <bits/stdc++.h>
using   namespace std;

class tree_node
{
  public:
  tree_node* child_1;
  tree_node* child_2;
  char value;
  
  tree_node(char symbol)
  {
    child_1 = NULL;
    child_2 = NULL;
    value = symbol;
  }

  tree_node(tree_node* children1,tree_node* children2, char symbol)
  {
    child_1 = children1;
    child_2 = children2;
    value = symbol;
  }
};

class expression_tree
{
   private:
   stack <tree_node*> create_tree;
   tree_node* head;

   public:
   expression_tree()
   {
    head = NULL;
   }

   void create_expression_tree(string postfix_expression)
   {
     for(int i = 0 ; i < postfix_expression.size();i++)
     {
       char character = postfix_expression[i];
       tree_node* new_node  = NULL;
       if (int(character) >= int('a') && int (character) <= int('z')) new_node = new  tree_node(character);

       else
       {
         tree_node* hold_1 = NULL;
         tree_node* hold_2 = NULL;
         if(create_tree.size() < 2) 
         {
            cout<<"There are not sufficient number of operands for the operator."<<endl;
            return;
         }
         hold_1 = create_tree.top();
         create_tree.pop();
         hold_2 = create_tree.top();
         create_tree.pop();
         new_node = new tree_node(hold_1,hold_2,character);
       }
       create_tree.push(new_node);
     }
     if(create_tree.size() != 1) cout<<"The expression is incomplete."<<endl;
     else head = create_tree.top();
   }

   void print_tree()
   {
    queue <tree_node*> print_nodes;
    print_nodes.push(head);
    while(print_nodes.size() > 0)
    {
        int count = print_nodes.size();
      for(int j = 0; j < count; j++)
      {
        tree_node* element = print_nodes.front();
        if (element->child_1 != NULL) print_nodes.push(element->child_1);
        if (element->child_2 != NULL) print_nodes.push(element->child_2);
        cout<<element->value<<"    ";
        print_nodes.pop();
      }
      cout<<endl;
    }
   }
};

int main()
{
  expression_tree random_name;
  random_name.create_expression_tree("ab+cde+**");
  random_name.print_tree();

  return 0;
}