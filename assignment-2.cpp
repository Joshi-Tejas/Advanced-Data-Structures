#include<iostream>
#include<string.h>
using namespace std;

class stack2;
class stack;
class tree;

class node
{
	char data;
	node *next;
	friend class stack;
};

class node2
{
	char data;
	node2 *left;
	node2 *right;
	friend class tree;
};	

class node3
{
	node2* data;
	node3 *next;
	friend class stack2;
};

class stack2
{
	node3 *start=NULL;
	public:
	
	void push(node2 *ch)
	{
		node3 *temp=new node3;
		temp->data=ch;
		temp->next=NULL;
		if(start==NULL)
			start=temp;
		else
		{
			temp->next=start;
			start=temp;
		}
	}
	
	bool isempty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}			
	
	void pop()
	{
		if(isempty())
			cout<<"Stack underflow.\n";
		else
		{		
			node3 *temp;
			temp=start;
			start=temp->next;
			delete temp;
		}
	}
	
	node2* top()
	{
		if(isempty())
		{
			cout<<"Stack is empty.\n";
		}	
		else
			return (start->data);
	}
	
	bool operand(char a)
	{
		if(a!='+' && a!='-' && a!='*' && a!='/')
			return true;
		else
			return false;
	}
};
	
class stack
{
	node *start=NULL;
	public:
	
	void push(char ch)
	{
		node *temp=new node;
		temp->data=ch;
		temp->next=NULL;
		if(start==NULL)
			start=temp;
		else
		{
			temp->next=start;
			start=temp;
		}
	}
	
	bool isempty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}			
	
	void pop()
	{
		if(isempty())
			cout<<"Stack underflow.\n";
		else
		{		
			node *temp;
			temp=start;
			start=temp->next;
			delete temp;
		}
	}
	
	char top()
	{
		if(isempty())
		{
			cout<<"Stack is empty.\n";
		}	
		else
			return (start->data);
	}
	
	bool operand(char a)
	{
		if(a!='+' && a!='-' && a!='*' && a!='/')
			return true;
		else
			return false;
	}	
	
	int preced(char x)
	{
		if(x=='/' || x=='*')
			return 2;
		else if(x=='+' || x=='-')
			return 1;
	}			 		
	
	void postfix(char exp[],char ans[])
	{
		node *q=start;
		start=NULL;
		int i=0,m=0,j;
		while(m<strlen(exp) && exp[i]!='\0')
		{
			q=start;
			if(operand(exp[i]))
			{
				ans[m]=exp[i];
				m++;
			}	
			else
			{
				if(start==NULL)
					push(exp[i]);
				else if(preced(q->data)<preced(exp[i]))
					push(exp[i]);
				else if(preced(q->data)>=preced(exp[i]))
				{
					while(start!=NULL)
					{
						ans[m]=top();
						pop();
						m++;
					}
					push(exp[i]);
				}
			}
			i++;
		}
		while(start!=NULL)
		{
			ans[m]=top();
			pop();
			m++;
		}	
	}			
};

class tree
{
	node2 *root=NULL;
	public:
	
	node2* add_node(char ch)
	{
		node2 *temp=new node2;
		temp->data=ch;
		temp->left=NULL;
		temp->right=NULL;
		return temp;
	}
	
	node2* create(char arr[])
	{
		int i;
		stack2 s;
		node2 *ptr,*ptr1,*ptr2;
		for(i=0;i<strlen(arr);i++)
		{
			if(s.operand(arr[i]))
			{
				ptr=add_node(arr[i]);
				s.push(ptr);
			}
			else
			{
				ptr=add_node(arr[i]);
				ptr1=s.top();
				s.pop();
				ptr2=s.top();
				s.pop();
				ptr->right=ptr1;
				ptr->left=ptr2;
				s.push(ptr);
			}
		}
		ptr=s.top();
		s.pop();
		root=ptr;
		return ptr;	
	}
	
	void rec_inorder(node2 *temp)
	{
		if(temp==NULL)
		{
			return;
		}	
		else
		{
			rec_inorder(temp->left);
			cout<<temp->data;
			rec_inorder(temp->right);
		}
	}	
	
	void rec_preorder(node2 *temp)
	{
		if(temp==NULL)
		{	
			return;
		}	
		else
		{
			cout<<temp->data;
			rec_preorder(temp->left);
			rec_preorder(temp->right);
		}
	}
	
	void rec_postorder(node2 *temp)
	{
		if(temp==NULL)
		{
			return;
		}	
		else
		{
			rec_postorder(temp->left);
			rec_postorder(temp->right);
			cout<<temp->data;
		}
	}
	
	void inorder()
	{
		node2 *ptr=root;
		stack2 s;
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
				ptr=s.top();
				s.pop();
				cout<<ptr->data;
				ptr=ptr->right;
			}
		}
	}
	
	void preorder()
	{
		node2 *ptr=root;
		stack2 s;
		if(root==NULL)
			cout<<"The tree is empty.\n";
		else
		{
			while(1)
			{
				while(ptr!=NULL)
				{
					cout<<ptr->data;
					if(ptr->right!=NULL)
						s.push(ptr->right);
					ptr=ptr->left;
				}
				if(s.isempty())
				{
					break;
				}
				ptr=s.top();
				s.pop();
			}
		}
	}
	
	void postorder()
	{
		node2 * ptr=root;
		stack2 s1,s2;
		if(root==NULL)
			cout<<"Tree is empty.\n";
		else
		{
			s1.push(ptr);
			while(!s1.isempty())
			{
				ptr=s1.top();
				s1.pop();
				s2.push(ptr);
				if(ptr->left!=NULL)
					s1.push(ptr->left);
				if(ptr->right!=NULL)
					s1.push(ptr->right);	
			}
			while(!s2.isempty())
			{
				ptr=s2.top();
				s2.pop();
				cout<<ptr->data;
			}	
		}
	}						
};		

int main()
{
	int choice;
	stack s1;
	tree t1;
	node2* root;
	char exp[30],ans[30];
	do
	{
		cout<<"Enter your choice\n1. Input\n2. Inorder Traversal\n3. Preorder Traversal\n4. Postorder Traversal\n5. Recursive Inorder\n6. Recursive Preorder\n7. Recursive Postorder\n8. Exit";
		cin>>choice;
		switch (choice)
		{
			case 1: cout<<"Enter expression :\n";
				cin>>exp;
				s1.postfix(exp,ans);
				root=t1.create(ans);
			break;
			case 2: t1.inorder();
				cout<<endl;
			break;
			case 3: t1.preorder();
				cout<<endl;
			break;
			case 4: t1.postorder();
				cout<<endl;
			break;
			case 5:	t1.rec_inorder(root);
				cout<<endl;
			break;
			case 6:	t1.rec_preorder(root);
				cout<<endl;
			break;
			case 7: t1.rec_postorder(root);
				cout<<endl;
			break;
		}
	}while(choice!=8);			
	return 0;
}		
