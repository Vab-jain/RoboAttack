#include <iostream>

using namespace std;

//#define N 1000

int path[1000] = {};	//path between any two robots
int i=0;			//counter for path[i]
int flag = 0;   // to check whether the path is found or not

void find_path(int G[100][100], int n, int a, int b)	//n = total no. of vertices		a = robo1		b = robo2
{	
	/*ERROR HANDLING*/
	if(i>n)
		{	return;	}
	cout<<"\nfind path entering...\n";
	if(i!=0)
	{
		if(path[i-1]!=a)
		{
			cout<<"\nparent path checked...\n";
			path[i] = a;
			if(a!=b)
			{
				for(int j=0; j<n; j++)
				{	
					cout<<"\nentered in loop...\n";
					if(G[a][j]);
					{
						i++;
						cout<<"\ncalling recurtion....\n";
						find_path(G,n,j,b);
						if(flag==0)
							i--;
						else 
							break;
					}
				}
			}
			else 
				flag++;
		}
	}
	else
	{
		path[i]=a;
		for(int j=0; j<n; j++)
		{	cout<<"\nentered other else...\n";
			if(G[a][j]);
			{
				i++;
				find_path(G,n,j,b);
				if(flag==0)
					i--;
				else 
					break;
			}
		}	
	}
}

/* function to delete the minimum cost edge in the given path and delete if*/
int DELETE_MIN(int Path[], int PathSize, int G[100][100])
{
	int v1 = Path[0], v2 = Path[1], w = G[Path[0]][Path[1]]; // (v1,v2) is an edge in the path corresponding to the minimum weight in the path
	for(int i=0 ; i<PathSize-1 ; i++)  
	{
		if (G[Path[i]][Path[i+1]]<w)  // traving the path and checking if any weight in the path is smaller than the weight w which is the smallest path
		{
			// if the weight is smaller than w then updating v1 and v2 to be the edge vertices corresponding to that edge and w to be the weight of that edge
			// as (v1,v2) is the edge corresponding to the smallest weight

			v1 = Path[i];   	
			v2 = Path[i+1];
			w = G[Path[i]][Path[i+1]];
		}
	}
	G[v1][v2] = 0;  // destroying the lowest weighted edge in the path
	return w;  // returning the smallest weight in the path
}
/**/

/*function for finding the minimum edge in the for all the paths b/w the robot positions and delete the edges 
and return the minimum time required to delete all the edges*/
int MIN_EDGE_CUTTING_TIME(int G[100][100], int k, int RobotPosition[], int no_of_vertex)
{
	cout<<"\nEntering MIN_EDGE_CUTTING_TIME function\n";
	int MinTime=0;  // variable to store the time taken for destroying the all edges to save kingdom

	for(int l=0;l<k-1;l++)  // loops to find all the possible paths to other robot located cities from the city
	{ 						// at ith position of the RobotPosition array in which other robot is located
		for(int j=l+1;j<k;j++)
		{	//int PathSize = 0;  // variable to store the size of the path array below
			cout<<"\ncalling find_path in MIN_EDGE_CUTTING_TIME\n";
			find_path(G,no_of_vertex,RobotPosition[l],RobotPosition[j]);  // getting the path of robot at i index of RobotPosition array and
			cout<<"\nsuccessfully computed find_path in MIN_EDGE_CUTTING_TIME\n";						// at j index of RobotPosition array
			cout<<"\ncalling DELETE_MIN...\n";
			MinTime += DELETE_MIN(path,i+1,G);   // function to delete the minimun cost edge in the path traced above
			cout<<"\nsuccessfully completed DELETE_MIN in MIN_EDGE_CUTTING_TIME\n";
			i=0;		// reset i to 0 for path[i] in find_path
		}
	}	
	return MinTime;
}

int main()
{
	cout<<"\nEnter no. of vertices:\n";
	int n, k;  // n is the no of vertices and k is the no of bots 
	cin>>n;
	cout<<"\nEnter no. of robots\n";
	cin>>k;
	int RobotPosition[k];  // to store the positions of the robots in the kingdom
	int G[100][100]={ };  // adjacency matrix of the graph which stores the weight b/w the vertices
	int v1, v2, w; // (v1,v2) is an edge of the graph
	cout<<"\nEnter edges\n";
	for(int j=0;j<n-1;j++)  // initializing the graph with weights 
	{
		cin>>v1>>v2>>w;  
		G[v1][v2]=w;
		G[v2][v1]=w;
	}
	cout<<"\nEnter robot positions:\n";
	for(int j=0;j<k;j++)  //getting the position of the robots
	{	
		cin>>RobotPosition[j];
	}
	int time;
	cout<<"Callinng MIN_EDGE_CUTTING_TIME function";
	time = MIN_EDGE_CUTTING_TIME(G,k,RobotPosition,n);
	cout<<time;
	//system("pause");
	return 0;
}
