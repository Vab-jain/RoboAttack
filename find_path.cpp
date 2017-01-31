#include <iostream>

using namespace std;

int path[1000];	//path between any two robots
int i=0;			//counter for path[i]
int flag = 0;   // to check whether the path is found or not
int flag1=0;
void find_path(int G[100][100], int n, int a, int b)	//n = total no. of vertices		a = robo1		b = robo2
{	
		if(path[i-2]!=a)
		{
			
			path[i] = a;
			if(a!=b)
			{
				for(int j=0; j<n; j++)
				{	
			
					if(G[a][j]>0)
					{
						if(flag1==0)
						{	i++;
					
							find_path(G,n,j,b);
							if(flag==0)
								i--;
							else 
								return;
						}
						flag1=0;
					}
				}
			}
			else 
				flag++;
		}
	}

int main()
{
	int n, k;  // n is the no of vertices and k is the no of bots 
	cin>>n;
	cin>>k;
	int RobotPosition[k];  // to store the positions of the robots in the kingdom
	int G[100][100]={ };  // adjacency matrix of the graph which stores the weight b/w the vertices
	int v1, v2, w; // (v1,v2) is an edge of the graph
	for(int j=0;j<n-1;j++)  // initializing the graph with weights 
	{
		cin>>v1>>v2>>w;  
		G[v1][v2]=w;
		G[v2][v1]=w;
	}
	for(int j=0 ;j<n;j++)
	{	for(int m=0;m<n;m++)
			cout<<G[j][m]<<" ";
		cout<<endl;
	}
	for(int j=0;j<k;j++)  //getting the position of the robots
	{	
		cin>>RobotPosition[j];
	}
	find_path(G,n,3,4);
	for (int j = 0; j <= i; ++j)
	{
		cout<<path[j]<<" ";
	}
	cout<<endl;
	return 0;
}