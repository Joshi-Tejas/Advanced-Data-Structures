#include<iostream>
using namespace std;

class tree;

class node
{
	int data;
	node *left;
	node *right;
	bool lflag;
	bool rflag;
	friend class tree;
};

class tree
{
	node *root=NULL;
	node *head;
	public:
	
	node* add_node(int num)
	{
		node *temp=new node;
		temp->data=num;
		temp->left=NULL;
		temp->right=NULL;
		temp->lflag=false;
		temp->rflag=false;
		return temp;
	}
	
	void create(int num)
	{
		node *newnode=add_node(num);
		node* parent;
		if(root==NULL)
		{
			head=add_node(0);
			head->right=head;
			head->rflag=true;
			root=newnode;
			newnode->left=head;
			newnode->right=head;
			head->left=root;
			head->lflag=true;
		}
		else
		{
			parent=root;
			while(1)
			{
				if(num==parent->data)
				{
					cout<<"Duplicate node!\n";
					return;
				}
				else if(num<parent->data)
				{
					if(parent->lflag==true)
						parent=parent->left;
					else
						break;
				}
				else
				{
					if(parent->rflag==true)
						parent=parent->right;
					else
						break;
				}
			}
			if(num<parent->data)
			{
				newnode->left=parent->left;
				newnode->right=parent;
				parent->left=newnode;
				parent->lflag=true;
			}
			else
			{
				newnode->right=parent->right;
				newnode->left=parent;
				parent->right=newnode;
				parent->rflag=true;
			}
		}
	}
	
	node* in_successor(node *temp)
	{
		if(temp->rflag==false)
			return temp->right;
		else
		{
			temp=temp->right;
			while(temp->lflag==true)
				temp=temp->left;
			return temp;
		}
	}
	
	node* pre_successor(node *temp)
	{
		if(temp->lflag==true)
			return temp->left;
		else
		{
			while(temp->rflag==false)
				temp=temp->right;
			return temp->right;
		}
	}				
	
	void inorder()
	{
		node *temp=root;
		if(root->lflag==false && root->rflag==false)
			cout<<"Tree is empty.\n";
		else
		{
			while(temp->lflag==1)
				temp=temp->left;
			while(temp!=head)
			{
				cout<<temp->data<<endl;
				temp=in_successor(temp);
			}
		}
	}
	
	void preorder()
	{
		node *temp=root;
		if(root->lflag==false && root->rflag==false)
			cout<<"Tree is empty.\n";
		else
		{
			while(temp!=head)
			{
				cout<<temp->data<<endl;
				temp=pre_successor(temp);
			}
		}
	}													
};

int main()
{
	int i,num,n,choice;
	tree t1;
	cout<<"Enter initial number of nodes : ";
	cin>>n;
	cout<<"Enter data:\n";
	for(i=0;i<n;i++)
	{
		cin>>num;
		t1.create(num);
	}
	do
	{
		cout<<"Enter choice\n1. Enter data\n2. Display inorder\n3. Display Preorder\n4. Exit\n";
		cin>>choice;
		switch (choice)
		{
			case 1: cout<<"Enter data : ";
				cin>>num;
				t1.create(num);
			break;
			case 2:	cout<<"Inorder traversal:\n";
				t1.inorder();
			break;	
			case 3: cout<<"Preorder traversal:\n";	
				t1.preorder();
			break;
		}
	}while(choice!=4);
	return 0;
}				
