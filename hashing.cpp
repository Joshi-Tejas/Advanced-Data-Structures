#include<iostream>
#include<string.h>
#define MAX 50
using namespace std;

class dictionary
{
	string array[MAX];
	int count;
	public:
	
	dictionary()
	{
		count=26;
		for(int i=0;i<count;i++)
			array[i]="z";
	}
	
	int hash(string arr)
	{
		return arr[0]-97;
	}	
	
	void insert(string str)
	{
		int i,pos;
		pos=hash(str);
		if(array[pos]=="z")
		{
			array[pos]=str;
			return;
		}
		else
		{
			for(i=pos+1;i<count;i++)
			{
				if(array[i]=="z")
				{
					array[i]=str;
					return;
				}
			}
			for(i=0;i<pos;i++)
			{
				if(array[i]=="z")
				{
					array[i]=str;
					return;
				}
			}
			cout<<"Hash table is full!\n";
		}
	}
	
	void search(string str)
	{
		for(int i=0;i<count;i++)
		{
			if(array[i]==str)
			{
				cout<<"FOUND :\n"<<array[i]<<endl;
				return;
			}
		}
		cout<<"NOT FOUND\n";
	}
	
	void del(string str)
	{
		for(int i=0;i<count;i++)
		{
			if(array[i]==str)
			{
				array[i]="z";
				cout<<"Deleted Successfully\n";
				return;
			}
		}
		cout<<"Element not present\n";
	}	
	
	void display()
	{
		cout<<"KEY\tELEMENT\n";
		for(int i=0;i<count;i++)
		{
			cout<<(char)(i+97)<<"\t";
			if(array[i]!="z")
				cout<<array[i];
			cout<<endl;
		}
	}			
};

int main()
{
	string str;
	dictionary dict;
	int choice;
	do
	{
		cout<<"Enter choice\n1. Insert\n2. Display\n3. Delete\n4. Search\n0. Exit\n";
		cin>>choice;
		switch (choice)
		{
			case 1: cout<<"Enter element : \n";
				cin>>str;
				dict.insert(str);
			break;
			case 2: dict.display();
			break;
			case 3: cout<<"Enter element : \n";
				cin>>str;
				dict.del(str);
			break;
			case 4: cout<<"Enter element : \n";
				cin>>str;
				dict.search(str);
			break;
		}
	}while(choice!=0);			
	return 0;
}
