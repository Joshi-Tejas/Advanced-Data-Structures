#include<iostream>
#include<string.h>
using namespace std;

class str_node
{
	string name,div,branch;
	int roll;
	str_node *next;
	friend class table;
	friend class node;
};

class node
{
	char data;
	str_node *next;
	node *down;
	friend class table;
};

class table
{
	node *start=NULL;
	public:
	
	table()
	{
		node *temp,*q;
		for(char i='a';i<='z';i++)
		{
			temp=new node;
			temp->data=i;
			temp->down=NULL;
			temp->next=NULL;
			if(start==NULL)
			{
				start=temp;
				q=temp;
			}
			else
			{
				q->down=temp;
				q=temp;
			}
		}
	}
	
	void display()
	{
		node *q=start;
		str_node *itr=q->next;
		while(q!=NULL)
		{
			itr=q->next;
			cout<<q->data;
			if(q->next!=NULL)
				cout<<"->";
			while(itr!=NULL)
			{
				cout<<itr->name;
				if(itr->next!=NULL)
					cout<<"->";
				itr=itr->next;
			}
			cout<<endl;
			q=q->down;
		}			
	}
	
	char hash(string str)
	{
		return str[0];
	}
	
	void insert(string str1)
	{
		char ch;
		node *q=start;
		str_node *itr;
		ch=hash(str1);
		while(q!=NULL)
		{
			itr=q->next;
			if(ch==q->data)
			{
				str_node *temp=new str_node;
				temp->name=str1;
				cout<<"Enter roll number : ";
				cin>>temp->roll;
				cout<<"Enter division : ";
				cin>>temp->div;
				cout<<"Enter branch : ";
				cin>>temp->branch;
				temp->next=NULL;
				if(q->next==NULL)
				{
					q->next=temp;
				}
				else
				{
					while(itr->next!=NULL)
						itr=itr->next;
					itr->next=temp;
				}
				return;
			}
			q=q->down;	
		}
		cout<<"Invalid input!\n";
	}
	
	void search(string str)
	{
		char ch;
		node *q=start;
		str_node *itr;
		ch=hash(str);
		while(q!=NULL)
		{
			itr=q->next;
			if(ch==q->data)
			{
				if(q->next==NULL)
				{
					break;
				}
				else
				{
					while(itr!=NULL)
					{
						if(itr->name==str)
						{
							cout<<"FOUND!\n";
							cout<<"Name : "<<itr->name<<endl;
							cout<<"Roll Number : "<<itr->roll<<endl;
							cout<<"Division : "<<itr->div<<endl;
							cout<<"Branch : "<<itr->branch<<endl;
							return;
						}	
						itr=itr->next;
					}	
				}
			}
			q=q->down;	
		}
		cout<<"NOT FOUND!\n";
	}
	
	void modify(string str)
	{
		char ch;
		node *q=start;
		str_node *itr;
		ch=hash(str);
		while(q!=NULL)
		{
			itr=q->next;
			if(ch==q->data)
			{
				if(q->next==NULL)
				{
					break;
				}
				else
				{
					while(itr!=NULL)
					{
						if(itr->name==str)
						{
							cout<<"Enter name : ";
							cin>>itr->name;
							cout<<"Enter roll number : ";
							cin>>itr->roll;
							cout<<"Enter division : ";
							cin>>itr->div;
							cout<<"Enter branch : ";
							cin>>itr->branch;
							cout<<"Modification successfull\n";
							return;
						}	
						itr=itr->next;
					}	
				}
			}
			q=q->down;	
		}
		cout<<"NOT FOUND!\n";
	}	
	
	void del(string str)
	{
		char ch;
		node *q=start;
		str_node *itr,*p;
		ch=hash(str);
		while(q!=NULL)
		{
			itr=q->next;
			if(ch==q->data)
			{
				if(q->next==NULL)
				{
					break;
				}
				else if(itr->name==str)
				{
					q->next=itr->next;
					delete itr;
					return;
				}	
				else
				{
					p=itr;
					itr=itr->next;
					while(itr!=NULL)
					{
						if(itr->name==str)
						{
							p->next=itr->next;
							delete itr;
							return;
						}	
						itr=itr->next;
						p=p->next;
					}	
				}
			}
			q=q->down;	
		}
		cout<<"Element not Found\n";
	}		
};

int main()
{
	table t1;
	string s;
	int choice;
	do
	{
		cout<<"Enter choice\n1. Insert\n2. Display\n3. Search\n4. Delete\n5. Modify\n0. Exit\n";
		cin>>choice;
		switch (choice)
		{
			case 1: cout<<"Enter name : ";
				cin>>s;
				t1.insert(s);
			break;
			case 2: t1.display();
			break;
			case 3: cout<<"Enter name to search : ";
				cin>>s;
				t1.search(s);
			break;
			case 4: cout<<"Enter name : ";
				cin>>s;
				t1.del(s);
			break;
			case 5: cout<<"Enter name : ";
				cin>>s;
				t1.modify(s);
			break;
		}
	}while(choice!=0);		
	return 0;
}		
