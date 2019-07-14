#include<iostream>
using namespace std;

class tree;

class node
{
	int data;
	node *left;
	node *right;
	friend class tree;
};

class node2
{
	int data;
	node2 *next;
	friend class stack;
};	

class stack
{
	node2 *start=NULL;
	public:
	
	bool isempty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}			
	
	void push(node *num)
	{
		node2 *temp=new node2;
		temp->data=num->data;
		temp->next=NULL;
		if(start==NULL)
			start=temp;
		else
		{
			temp->next=start;
			start=temp;
		}
	}					
	
	node *pop()
	{
		node2 *temp=start;
		start=temp->next;
		return temp;
	}
};	

class tree
{
	node *root=NULL;
	public:
	
	node* create(int num)
	{
		node *temp=new node;
		temp->data=num;
		temp->left=NULL;
		temp->right=NULL;
		return temp;
	}	
	
	void add_node(int num)
	{
		node *newnode=create(num);
		if(root==NULL)
			root=newnode;
		else
		{
			node *oldnode=root;
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
				else
				{
					if(newnode->data>oldnode->data)
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
						cout<<"Duplicate node\n";
						break;
					}
				}
			}
		}	
	}
	
	void inorder()
	{
		
		node *ptr=root;
		stack s;
		if(root==NULL)
		{
			cout<<"Tree is empty.\n";
			return;
		}
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
				k=s.pop();
				cout<<k<<endl;
				ptr=ptr->right;
			}
		}
	}					
};

int main()
{
	int i,n,num;
	tree t1;
	cout<<"Enter nodes : ";
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>num;
		t1.add_node(num);
	}
	cout<<"The in-order of this tree is :\n";
	t1.inorder();	
	return 0;
}				
