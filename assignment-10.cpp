#include<iostream>
#include<fstream>
using namespace std;
class student
{
	public:	
	int rollno;
	char name[50],div,add[50];
	void getdata()
	{
		cout<<"Enter rollno : ";
		cin>>rollno;
		cout<<"Enter name : ";
		cin>>name;
		cout<<"Enter division : ";
		cin>>div;
		cout<<"Enter address :\n";
		cin>>add;
	}
	void putdata()
	{
		cout<<"roll no : "<<rollno<<"\n"<<"Name : "<<name<<"\n"<<"Division : "<<div<<"\n"<<"Address : "<<add<<endl;
	}
};

class Database
{
	char fname[30];
	int n;
	public:	
	Database()
	{
		cout<<"Enter name of file to be opened : ";
		cin>>fname;
	}
	void changefile();
	void create();
	void display();
	void addrec();
	void search(int);
	void modify(int);
	void del(int);
	void menu();
};

void Database::changefile()
{
	ifstream fin;
	student s;
	int ans;
	fin.open(fname);
	if(fin)
	{
		cout<<"File Already Exist\n";
		cout<<"Contents of File :\n";
		while(fin.read((char *)&s,sizeof(s)))
		{
			s.putdata();
		}
		cout<<"\nWould you like to\n1.add records\n2. overwrite them\n3.change file\n4.Continue\n";
		cin>>ans;
		switch(ans)
		{
			case 1:	addrec();
				break;
			case 2:	create();
				break;
			case 3:	cout<<"Enter new file name : ";
				cin>>fname;
				break;
			case 4:	break;
		}
	}
	else
	{
		cout<<"File Does Not Exist\n";
		create();
	}
	fin.close();
}
void Database::create()
{
	ofstream fout;
	student s;
	fout.open(fname);
	if(fout.fail())
	{
		cout<<"Error Opening File\n";
	}
	else
	{
		cout<<"Enter number of records : ";
		cin>>n;
		for(int i=0;i<n;i++)
		{
			s.getdata();
			fout.write((char *)&s,sizeof(s));
		}
	}
	fout.close();
}
void Database::display()
{
	ifstream fin;
	student s;
	fin.open(fname);
	if(fin.fail())
	{
		cout<<"Error Opening File\n";
	}
	else
	{
		while(fin.read((char *)&s,sizeof(s)))
		{
			s.putdata();
		}
	}
	fin.close();
}
void Database::addrec()
{
	ofstream fout;
	student s;
	fout.open(fname,ios::app);
	if(fout.fail())
	{
		cout<<"Error Opening File";
	}
	else
	{
		cout<<"Enter number of records to be added : ";
		cin>>n;
		for(int i=0;i<n;i++)
		{
			s.getdata();
			fout.write((char *)&s,sizeof(s));
		}
	}
	fout.close();
}
void Database::search(int a)
{
	int flag=0;
	ifstream fin;
	student s;
	fin.open(fname);
	if(fin.fail())
	{
		cout<<"Error Opening File\n";
	}
	else
	{
		while(fin.read((char *)&s,sizeof(s)))
		{
			if(a==s.rollno)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
			s.putdata();
		else
			cout<<"Record Not Found\n";
	}
	fin.close();
}
void Database::modify(int r)
{
	int flag=0,ch,pos=0;
	fstream finout;
	student s;
	finout.open(fname,ios::in|ios::out|ios::binary);
	if(finout.fail())
	{
		cout<<"Error Opening File\n";
	}
	else
	{
		while(finout.read((char *)&s,sizeof(s)))
		{
			if(r==s.rollno)
			{
				flag=1;
				break;
			}
			else
			{
				pos++;
			}
		}
		if(flag==1)
		{
			cout<<"Enter what to be modified\n1.Rollno\n2.Name\n3.Div\n4.Address\n";
			cin>>ch;
			switch(ch)
			{
				case 1:	cout<<"Enter new rollno : ";
					cin>>s.rollno;
					finout.seekp(pos*sizeof(s),ios::beg);
					finout.write((char *)&s,sizeof(s));
					break;
				case 2:	cout<<"Enter new name : ";
					cin>>s.name;
					finout.seekp(pos*sizeof(s),ios::beg);
					finout.write((char *)&s,sizeof(s));
					break;
				case 3:	cout<<"Enter new divison : ";
					cin>>s.div;
					finout.seekp(pos*sizeof(s),ios::beg);
					finout.write((char *)&s,sizeof(s));
					break;
				case 4:	cout<<"Enter new address : ";
					cin>>s.add;
					finout.seekp(pos*sizeof(s),ios::beg);
					finout.write((char *)&s,sizeof(s));
					break;
			}
		}
		else
		{
			cout<<"Record Not Found\n";
		}
	}
	finout.close();
}
void Database::del(int a)
{
	int flag=0;
	fstream fin,fout;
	student s;	
	fin.open(fname,ios::in|ios::binary);
	fout.open("temp",ios::out|ios::binary);
	if(fin.fail() || fout.fail())
	{
		cout<<"Error Opening File\n";
	}
	else
	{
		while(fin.read((char *)&s,sizeof(s)))
		{
			if(a!=s.rollno)
			{
				fout.write((char*)&s,sizeof(s));
			}
			else
			{
				flag=1;
			}
		}
		if(flag==1)
		{
			fin.close();
			fout.close();

			remove(fname);
			rename("temp",fname);
			cout<<"Record Deleted\n";
		}
		else
		{
			cout<<"Record Not Found\n";
		}
	}
}
void Database::menu()
{
	int choice,r,m,srno;
	do
	{
		cout<<"Enter your choice\n1.Create\n2.Display\n3.Addrec\n4.Search\n5.Modify\n6.Delete\n7.Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:	changefile();
				break;
			case 2:	display();
				break;
			case 3:	addrec();
				break;
			case 4:	cout<<"Enter roll number to be searched : ";
				cin>>r;
				search(r);
				break;
			case 5:	cout<<"Enter roll number to be modified : ";
				cin>>m;
				modify(m);
				break;
			case 6:	cout<<"Enter rollnumber to be deleted : ";
				cin>>srno;
				del(srno);
				break;
		}
	}while(choice!=7);
}
int main()
{
	Database obj;
	obj.menu();
}
