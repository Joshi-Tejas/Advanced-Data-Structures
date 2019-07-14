#include<iostream>
#define MAX 20
using namespace std;

class node
{
	int data;
	node *next;
	friend class graph;
	friend class queue;
	friend class stack;
};

class queue
{
	node *start=NULL;
	public:
	
	void insert(int num)
	{
		node *q=start;
		node *temp=new node;
		temp->data=num;
		temp->next=NULL;
		if(start==NULL)
		{
			start=temp;
		}
		else
		{
			while(q->next!=NULL)
			{
				q=q->next;
			}
			q->next=temp;
		}
	}
	
	
	bool isempty()
	{
		if(start==NULL)
			return true;
		else
			return false;
	}			
	
	void del()
	{
		if(start==NULL)
			cout<<"Queue underflow!\n";
		else
		{
			node *temp=start;
			start=temp->next;
			delete temp;
		}
	}
	
	int front()
	{
		return start->data;
	}	
};			

class stack
{
	node *start=NULL;
	public:
	
	void push(int num)
	{
		node *temp=new node;
		temp->data=num;
		temp->next=NULL;
		if(start==NULL)
		{
			start=temp;
		}
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
		if(start==NULL)
			cout<<"Queue underflow!\n";
		else
		{
			node *temp=start;
			start=temp->next;
			delete temp;
		}
	}
	
	int top()
	{
		return start->data;
	}	
};			

class graph
{
	int matrix[MAX][MAX];
	int edge,vert,matcnt,adjcnt;
	node *adjlist[MAX];
	bool visit[MAX];
	public:
	
	graph()
	{
		for(int i=0;i<MAX;i++)
		{
			adjlist[i]=NULL;
			for(int j=0;j<MAX;j++)
			{
				matrix[i][j]=0;
			}
		}
		matcnt=0;
		adjcnt=0;
	}
	
	node* create_node(int pos,int x)
	{
		node *temp=new node;
		temp->data=x;
		temp->next=NULL;
		if(adjlist[pos]==NULL)
		{
			adjlist[pos]=temp;
		}
		else
		{
			node *q=adjlist[pos];
			while(q->next!=NULL)
			{
				q=q->next;
			}
			q->next=temp;
		}			
	}			
	
	void getdata()
	{
		int i,j,var1,var2;
		cout<<"Enter number of vertices : ";
		cin>>vert;
		cout<<"Let, the vertices be : ";
		for(i=0;i<vert;i++)
		{
			cout<<i<<"  ";
		}
		cout<<endl<<"Enter number of edges : ";
		cin>>edge;
		cout<<"Enter edges in the form of (u,v) :\n";
		for(i=0;i<edge;i++)
		{
			cout<<"Enter edge "<<i+1<<" : ";
			cin>>var1>>var2;
			matrix[var1][var2]=1;
			matrix[var2][var1]=1;
			create_node(var1,var2);
			create_node(var2,var1);
		}
	}
	
	int disp_matrix()
	{
		cout<<"Matrix representation of this graph :\n";
		for(int i=0;i<vert;i++)
		{
			for(int j=0;j<vert;j++)
			{
				cout<<matrix[i][j]<<"  ";
				matcnt++;
			}
			cout<<endl;
		}
		return matcnt;
	}
	
	int disp_adjlist()
	{
		cout<<"Adjacency List representation of this matrix :\n";
		for(int i=0;i<vert;i++)
		{
			node *q=adjlist[i];
			cout<<i<<"-->";
			while(q!=NULL)
			{
				cout<<q->data;
				if(q->next!=NULL)
					cout<<"-->";	
				q=q->next;
				adjcnt++;
			}
			cout<<endl;
		}
		return adjcnt;
	}		
	
	void bfs_nonrec(int source)
	{
		queue q1;
		int i,get;
		node *temp;
		for(i=0;i<MAX;i++)
		{
			visit[i]=false;
		}	
		q1.insert(source);
		visit[source]=true;
		while(!q1.isempty())
		{
			get=q1.front();
			q1.del();
			temp=adjlist[get];
			cout<<get<<endl;
			while(temp!=NULL)
			{
				if(visit[temp->data]==false)
				{
					q1.insert(temp->data);
					visit[temp->data]=true;
				}
				temp=temp->next;
			}
		}
	}
	
	void dfs_nonrec(int source)
	{
		stack s1;
		node *temp;
		int i,get;
		for(i=0;i<MAX;i++)
		{
			visit[i]=false;
		}
		s1.push(source);
		visit[source]=true;
		while(!s1.isempty())
		{
			get=s1.top();
			s1.pop();
			cout<<get<<endl;
			temp=adjlist[get];
			while(temp!=NULL)
			{
				if(visit[temp->data]==false)
				{
					s1.push(temp->data);
					visit[temp->data]=true;
				}
				temp=temp->next;
			}			
		}
	}
	
	void dfs_util(int source)
	{
		node *temp=adjlist[source];
		cout<<source<<endl;
		visit[source]=true;
		while(temp!=NULL)
		{
			if(visit[temp->data]==false)
				dfs_util(temp->data);
			temp=temp->next;
		}
	}			
	
	void dfs_rec(int source)
	{
		for(int i=0;i<MAX;i++)
		{
			visit[i]=false;
		}
		
		dfs_util(source);
	}
	
	void bfs_util(queue q2)
	{
		if(q2.isempty())
			return;
		int get=q2.front();
		cout<<get<<endl;
		node *temp=adjlist[get];
		q2.del();
		while(temp!=NULL)
		{
			if(visit[temp->data]==false)
			{
				visit[temp->data]=true;
				q2.insert(temp->data);
			}
			temp=temp->next;
		}
		bfs_util(q2);
	}			
	
	void bfs_rec()
	{
		queue q2;
		for(int i=0;i<MAX;i++)
		{
			visit[i]=false;
		}
		for(int i=0;i<vert;i++)
		{
			if(visit[i]==false)
			{
				visit[i]=true;
				q2.insert(i);
				bfs_util(q2);
			}
		}		
	}	
};

int main()
{
	int count1,count2;
	graph g1;
	g1.getdata();
	count1=g1.disp_matrix();
	count2=g1.disp_adjlist();
	cout<<count1<<endl<<count2<<endl;
	cout<<"BFS non rec:\n";
	g1.bfs_nonrec(0);
	cout<<"DFS non rec:\n";
	g1.dfs_nonrec(0);
	cout<<"DFS rec :\n";
	g1.dfs_rec(0);
	cout<<"BFS rec :\n";
	g1.bfs_rec();
	return 0;
}				
