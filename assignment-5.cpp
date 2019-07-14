#include<iostream>
#define MAX 20
#define INFINITY 10000
using namespace std;

class node
{
	int data;
	float dist;
	node *next;
	friend class graph;
};

class graph
{
	node *adjlist[MAX];
	string city[MAX];
	int numb,edge;
	public:
	
	graph()
	{
		for(int i=0;i<MAX;i++)
		{
			adjlist[i]=NULL;
		}
	}		
	
	void add_node(int pos,int num,float weight)
	{
		node *q=adjlist[pos];
		node *temp=new node;
		temp->data=num;
		temp->dist=weight;
		temp->next=NULL;
		if(adjlist[pos]==NULL)
		{
			adjlist[pos]=temp;
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
	
	void getdata()
	{
		float wt;
		int i,var1,var2;
		cout<<"Enter number of cities : ";
		cin>>numb;
		cout<<"Enter names of cities one by one :\n";
		for(i=0;i<numb;i++)
		{
			cout<<"Enter city "<<i+1<<" : ";
			cin>>city[i];
		}
		cout<<"Let, following numbers be representives of cities :\n";
		for(i=0;i<numb;i++)
		{
			cout<<city[i]<<" :\t"<<i<<endl;
		}
		cout<<"Enter number of connectivities : ";
		cin>>edge;
		cout<<"Enter edges and their weights according to numbers of city representatives :\n";
		for(i=0;i<edge;i++)
		{
			cout<<"Edge "<<i+1<<" : ";
			cin>>var1>>var2;
			cout<<"Weight "<<i+1<<" : ";
			cin>>wt;
			add_node(var1,var2,wt);
			add_node(var2,var1,wt);
		}	
	}
	
	void display()
	{
		int i;
		node *temp;
		for(i=0;i<numb;i++)
		{
			cout<<city[i]<<"-->";
			temp=adjlist[i];
			while(temp!=NULL)
			{
				cout<<city[temp->data]<<"("<<temp->dist<<")";
				if(temp->next!=NULL)
					cout<<"-->";
				temp=temp->next;
			}
			cout<<endl;
		}
	}
	
	float prim()
	{
		int i,j,edge_n,u,v=0;
		node *temp;
		graph spanning;
		spanning.numb=numb;
		for(i=0;i<numb;i++)
		{
			spanning.city[i]=city[i];
		}	
		int visited[MAX],from[MAX];
		float distance[MAX],min_span,min_dist;
		min_span=0;
		edge_n=numb-1;
		for(i=0;i<numb;i++)
		{
			visited[i]=0;
			from[i]=0;
			distance[i]=INFINITY;
		}
		temp=adjlist[0];
		distance[0]=0;
		visited[0]=1;
		while(temp!=NULL)
		{
			distance[temp->data]=temp->dist;
			temp=temp->next;
		}
		while(edge_n>0)
		{
			min_dist=INFINITY;
			for(i=1;i<numb;i++)
			{
				if(visited[i]==0 && distance[i]<min_dist)
				{
					v=i;
					min_dist=distance[i];
				}
			}
			u=from[v];
			spanning.add_node(u,v,distance[v]);
			spanning.add_node(v,u,distance[v]);
			min_span=min_span+distance[v];
			edge_n--;
			visited[v]=1;
			temp=adjlist[v];
			while(temp!=NULL)
			{
				if(visited[temp->data]==0 && temp->dist<distance[temp->data])
				{
					distance[temp->data]=temp->dist;
					from[temp->data]=v;
				}
				temp=temp->next;
			}
		}
		cout<<"The spanning tree is :\n";
		spanning.display();
		cout<<"Minimum span is : "<<min_span<<endl;			
	}
};

int main()
{
	graph g1;
	g1.getdata();
	g1.display();
	g1.prim();
	return 0;
}		
