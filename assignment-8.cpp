#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

class node
{
	char key[20];
	char mean[50];
	node *left,*right;
	int height;
	friend class dictionary;
	public:
	
	node()
	{
		left=NULL;
		right=NULL;
		strcpy(mean,"");
		strcpy(key,"-1");
		height=1;
	}
	
	node(char key[],char meaning[])
	{
		strcpy(this->key,key);
		strcpy(mean,meaning);
		left=NULL;
		right=NULL;
		height=1;
	}
};

class dictionary
{
	node *root=NULL;
	node *loc,*parent;
	int count=1;
	public:
	
	node* leftRotate(node *x)
	{
		node *t1=x->right;
		node *t2=t1->left;
		t1->left=x;
		x->right=t2;
		x->height=max(getheight(x->left),getheight(x->right))+1;
		t1->height=max(getheight(t1->left),getheight(t1->right))+1;
		return t1;
	}
	
	node* rightRotate(node *x)
	{
		node *t1=x->left;
		node *t2=t1->right;
		t1->right=x;
		x->left=t2;
		x->height=max(getheight(x->left),getheight(x->right))+1;
		t1->height=max(getheight(t1->left),getheight(t1->right))+1;
		return t1;
	}	
	
	node* insert(node *root_node,node *temp)
	{
		if(root_node==NULL)
			return temp;
		if(strcmp(temp->key,root_node->key)<0)
			root_node->left=insert(root_node->left,temp);
		else if(strcmp(temp->key,root_node->key)>0)
			root_node->right=insert(root_node->right,temp);
		else
			return root_node;
		
		root_node->height=1+max(getheight(root_node->left),getheight(root_node->right));
		int balance=getbalance(root_node);
		
		if(balance>1 && strcmp(temp->key,root_node->left->key)<0)
			return rightRotate(root_node);
		if(balance<-1 && strcmp(temp->key,root_node->right->key)>0)
			return leftRotate(root_node);
		if(balance>1 && strcmp(temp->key,root_node->left->key)>0)
		{
			root_node->left=leftRotate(root_node->left);
			return rightRotate(root_node);
		}	 
		if(balance<-1 && strcmp(temp->key,root_node->right->key)<0)
		{
			root_node->right=rightRotate(root_node->right);
			return leftRotate(root_node);
		}
		return root_node;	
	}
	
	void search(char x[])
	{
		search1(root,x);
	}
	
	node* search1(node *temp,char x[])
	{
		if(temp==NULL)
	    	{
	      		return temp;
	    	}
	    	if (!strcmp(temp->key,x))
	    	{
		      cout<<"found :\n"<<temp->mean<<endl;
		      loc=temp;
		      cout<<"Number of comparisons : "<<count<<endl;
		      return temp;
	    	}
	    	parent=root;
		if(strcmp(temp->key,x)>0)
		{
		     parent=temp;
		     count++;
		     search1(temp->left,x);
	    	}
		else
		{
			parent=temp;
			count++;
			search1(temp->right,x);
		}
	}
	
	void update(char x[])
	{
		search(x);
		cout<<"Enter the meaning :\n";
		cin>>loc->mean;
		cout<<"Information updated\n";
	}
	
	int del(char x[])
	{
		int k;
		search(x);
		if(loc==NULL)
		{
			cout<<"\nitem is not present.";
			return 0;
		}
		if(loc->right!=NULL && loc->left!=NULL)
			k=remove1(loc,parent);
		else
			remove2(loc,parent);
		return k;	
	}
	int remove1(node *l,node *p)
	{
		node *ptr,*save,*suc,*psuc;
		ptr=l->right;
		save=l;
		while(ptr->left!=NULL)
			{
			save=ptr;
			ptr=ptr->left;
			}
		suc=ptr;
		psuc=save;
		remove2(suc,psuc);
		if(p!=NULL)
		{
			if(l==p->left)
				p->left=suc;
			else
				p->right=suc;
		}		
		else
			root=l;
		suc->left=l->left;
		suc->right=l->right;
		return 1;
	}
	void remove2(node *s,node *p)
	{
		node *child;
		if(s->left==NULL && s->right==NULL)
			child=NULL;
		else if(s->left!=NULL)
			child=s->left;
		else
			child=s->right;
		if(p!=NULL)
		{
			if(s==p->left)
				p->left=child;
			else
			p->right=child;
		}	
		else
		root=child;
	}
	
	void getdata()
	{
		node *temp=new node;
		cout<<"Enter the word : ";
		cin>>temp->key;
		cout<<"Enter the meaning : ";
		cin>>temp->mean;
		root=insert(root,temp);
	}
	
	int max(int a,int b)
	{
		return (a>b)?a:b;
	}
	
	int getheight(node *temp)
	{
		if(temp==NULL)
			return 0;
		else
			return temp->height;
	}
	
	int getbalance(node *temp)
	{
		if(temp==NULL)
			return 0;
		else
			return (getheight(temp->left)-getheight(temp->right));
	}
	
	void inorder()
	{
		rec_inorder(root);
	}
	
	void preorder()
	{
		rec_preorder(root);
	}
	
	void postorder()
	{
		rec_postorder(root);
	}
	
	void rec_preorder(node *n)
	{
		if(n!=NULL)
		{
			cout<<endl<<setw(10)<<n->key<<setw(10)<<n->mean<<endl;
			rec_preorder(n->left);
			rec_preorder(n->right);
		}
	}

	void rec_inorder(node *n)
	{
		if(n)
		{
			rec_inorder(n->left);
			cout<<endl<<setw(10)<<n->key<<setw(10)<<n->mean<<endl;
			rec_inorder(n->right);
		}
	}

	void rec_postorder(node *n)
	{
		if(n!=NULL)
		{
			rec_postorder(n->left);
			rec_postorder(n->right);
			cout<<endl<<setw(10)<<n->key<<setw(10)<<n->mean<<endl;
		}
	}
};

int main()
{
	dictionary dict;
	int choice,k;
	char input[20];
	do
	{
		cout<<"Enter choice\n1. Enter element\n2. Display\n3. Preorder\n4. Postorder\n5. Search element\n6. Update\n7. Delete\n0. Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1: dict.getdata();
			break;
			case 2: dict.inorder();
			break;
			case 3: dict.preorder();
			break;
			case 4: dict.postorder();
			break;
			case 5: cout<<"Enter element to search ; ";
				cin>>input;
				dict.search(input);
			break;
			case 6: cout<<"Enter element to update : ";
				cin>>input;
				dict.update(input);
			break;
			case 7: cout<<"Enter element to delete : ";
				cin>>input;
				k=dict.del(input);	
				if(k==1)
					cout<<"Item deleted\n";
			break;
		}			
	}while(choice!=0);
	return 0;
}			
