#include<iostream>
#include<iomanip>
using namespace std;

class tree;
class stack;

class node
{
	int data;
	node *left;
	node *right;
	friend class tree;
};

class node2
{
	node* data;
	node2 *next;
	friend class stack;
};

class stack
{
	node2 *start=NULL;
	public:
	
	void push(node *num)
	{
		node2 *temp=new node2;
		temp->data=num;
		temp->next=NULL;
		if(start==NULL)
			start=temp;
		else
		{
			temp->next=start;
			start=temp;
		}
	}
	
	node* pop()
	{
		node2 *temp=start;
		node *num=temp->data;
		start=temp->next;
		delete temp;
		return num;
	}
	
	bool isempty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}						
};
class tree
{
	node *root=NULL;
	public:
	
	node* add_node(int num)
	{
		node *temp=new node;
		temp->data=num;
		temp->left=NULL;
		temp->right=NULL;
		return temp;
	}
	
	void create(int num)
	{
		node *newnode=add_node(num);
		node *oldnode;
		if(root==NULL)
			root=newnode;
		else
		{
			oldnode=root;
			while(1)
			{
				if(newnode->data<oldnode->data)
				{
					if(oldnode->left==NULL)
					{
						oldnode->left=newnode;
						break;
					}
					else
						oldnode=oldnode->left;
				}		
				else if(newnode->data>oldnode->data)
				{
					if(oldnode->right==NULL)
					{
						oldnode->right=newnode;
						break;
					}
					else
						oldnode=oldnode->right;
				}
				else
				{
					cout<<"Duplicate node.\n";
					break;
				}	
			}
		}
	}
	
	void inorder()
	{
		node *ptr=root;
		stack s;
		if(root==NULL)
			cout<<"The tree is empty.\n";
		else
		{
			while(1)
			{
				while(ptr!=NULL)
				{
					s.push(ptr);
					ptr=ptr->left;
				}
				if(s.isempty())
				{
					break;
				}
				ptr=s.pop();
				cout<<ptr->data<<endl;
				ptr=ptr->right;
			}
		}
	}
	
	void rec_inorder(node *temp)
	{
		if(temp==NULL)
			return;
		else
		{
			rec_inorder(temp->left);
			cout<<temp->data<<endl;
			rec_inorder(temp->right);
		}
	}
	
	void rec_preorder(node *temp)
	{
		if(temp==NULL)
			return;
		else
		{
			cout<<temp->data<<endl;
			rec_inorder(temp->left);
			rec_inorder(temp->right);
		}
	}
	
	void rec_postorder(node *temp)
	{
		if(temp==NULL)
			return;
		else
		{
			rec_inorder(temp->left);
			rec_inorder(temp->right);
			cout<<temp->data<<endl;
		}
	}		
	
	void search(int num)
	{
		int flag=0;
		node *ptr=root;
		if(root==NULL)
			cout<<"Tree is empty.\n";
		else
		{
			while(ptr!=NULL)
			{
				if(ptr->data==num)
				{
					cout<<"FOUND\n";
					flag=1;
					break;
				}
				else if(num<ptr->data)
					ptr=ptr->left;
				else if(num>ptr->data)
					ptr=ptr->right;
			}
			if(flag==0)
				cout<<"NOT FOUND\n";
		}
	}
	
	node* ret()
	{
		return root;
	}	
	
	void mirror(node *ptr)
	{
		if(ptr==NULL)
			return;
		else
		{	
			mirror(ptr->left);
			mirror(ptr->right);
			node *temp=ptr->left;
			ptr->left=ptr->right;
			ptr->right=temp;
		}		
	}
	
	int path(node *ptr)
	{
		if(ptr==NULL)
			return 0;
		int ldepth=path(ptr->left);
		int rdepth=path(ptr->right);
		if(ldepth>=rdepth)
			return (ldepth+1);
		else
			return (rdepth+1);
	}		
};

int main()
{
	node *root;
	int i,n,num,d,choice;
	tree t1;
	cout<<"Enter initial number of nodes : ";
	cin>>n;
	cout<<"Enter data :\n";
	for(i=0;i<n;i++)
	{
		cin>>num;
		t1.create(num);
	}
	root=t1.ret();
	do
	{
		cout<<"\nEnter choice\n1. Input\n2. Inorder traversal\n3. Recursive Inorder\n4. Recursive Preorder\n5. Recursive Postorder\n6. Search\n7. Mirror tree\n8. Display depth\n0. Exit\n";
		cin>>choice;
		switch (choice)
		{
			case 1: cout<<"Enter data :\n";
				cin>>num;
				t1.create(num);
				root=t1.ret();
			break;
			case 2:	cout<<"Inorder traversal is :\n";
				t1.inorder();
			break;
			case 3: cout<<"Inorder traversal is :\n";
				t1.rec_inorder(root);
			break;
			case 4: cout<<"Preorder traversal is :\n";
				t1.rec_preorder(root);
			break;
			case 5: cout<<"Postorder traversal is :\n";
				t1.rec_postorder(root);
			break;	
			case 6: cout<<"Enter a number to search : ";
				cin>>num;
				t1.search(num);
			break;	
			case 7:	
				t1.mirror(root);
			break;
			case 8: d=t1.path(root);
				cout<<"Number of nodes in longest path : "<<d<<endl;
			break;
		}
	}while(choice!=0);			 	
	return 0;
}		
