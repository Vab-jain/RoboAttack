#include <iostream>
#include <vector>

using namespace std;

//#define N 1000

vector < vector<int>> G;  // adjacency matrix of the graph which stores the weight b/w the vertices
vector<int> path;	//path between any two robots
int i=0;			//counter for path[i]
int flag = 0;   // to check whether the path is found or not

void find_path(int n, int a, int b)	//n = total no. of vertices		a = robo1		b = robo2
{	
	if(i>=2)
	{	if(path[i-2]!=a)
		{
			
			path[i] = a;
			if(a!=b)
			{
				for(int j=0; j<n; j++)
				{	
			
					if(G[a][j]>0)
					{
					//	if(flag1==0)
							i++;
					
							find_path(n,j,b);
							if(flag==0)
								i--;
							else 
								return;
					//	}
					//	flag1=0;
					}
				}
			}
			else 
				flag++;
		}
	}
	else{
		path[i]=a;
		if(a!=b){
			for(int j=0; j<n; j++)
				{	
			
					if(G[a][j]>0)
					{
					//	if(flag1==0)
							i++;
					
							find_path(n,j,b);
							if(flag==0)
								i--;
							else 
								return;
					//	}
					//	flag1=0;
					}
				}
		}
		else
			flag++;
	}
}


/* function to delete the minimum cost edge in the given path and delete if*/
int DELETE_MIN(vector<int> &Path, int PathSize)
{
	int v1 = Path[0], v2 = Path[1], w = G[Path[0]][Path[1]]; // (v1,v2) is an edge in the path corresponding to the minimum weight in the path
	for(int c=0 ; c<PathSize-1 ; c++)  
	{
		if (G[Path[c]][Path[c+1]]<w)  // traving the path and checking if any weight in the path is smaller than the weight w which is the smallest path
		{
			// if the weight is smaller than w then updating v1 and v2 to be the edge vertices corresponding to that edge and w to be the weight of that edge
			// as (v1,v2) is the edge corresponding to the smallest weight

			v1 = Path[c];   	
			v2 = Path[c+1];
			w = G[Path[c]][Path[c+1]];
		}
	}
	G[v1][v2] = 0;  // destroying the lowest weighted edge in the path
	G[v2][v1] = 0;
	return w;  // returning the smallest weight in the path
}
/**/

/*function for finding the minimum edge in the for all the paths b/w the robot positions and delete the edges 
and return the minimum time required to delete all the edges*/
int MIN_EDGE_CUTTING_TIME(int k, vector<int> RobotPosition, int no_of_vertex)
{
	//cout<<"\nEntering MIN_EDGE_CUTTING_TIME function\n";
	int MinTime=0;  // variable to store the time taken for destroying the all edges to save kingdom

	for(int l=0;l<k-1;l++)  // loops to find all the possible paths to other robot located cities from the city
	{ 						// at ith position of the RobotPosition array in which other robot is located
		for(int q=l+1;q<k;q++)
		{	//int PathSize = 0;  // variable to store the size of the path array below
			//cout<<"\ncalling find_path in MIN_EDGE_CUTTING_TIME\n";
			find_path(no_of_vertex,RobotPosition[l],RobotPosition[q]);  // getting the path of robot at i index of RobotPosition array and
			//cout<<"\nsuccessfully computed find_path in MIN_EDGE_CUTTING_TIME\n";						// at j index of RobotPosition array
			//cout<<"\ncalling DELETE_MIN...\n";
			if(i>0)
				MinTime += DELETE_MIN(path,i+1);   // function to delete the minimun cost edge in the path traced above
			//cout<<"\nsuccessfully completed DELETE_MIN in MIN_EDGE_CUTTING_TIME\n";
			i=0;		// reset i to 0 for path[i] in find_path
			flag=0;
		}
	}	
	return MinTime;
}

int main()
{
	//cout<<"\nEnter no. of vertices:\n";
	long n, k;  // n is the no of vertices and k is the no of bots 
	cin>>n;
	//cout<<"\nEnter no. of robots\n";
	cin>>k;

	vector<int> RobotPosition;  // to store the positions of the robots in the kingdom
	//set size if G, RobotPosition, Path
	G.resize(n);
    for(int i=0; i<n;i++)
    {
        G[i].resize(n);
    }
	path.resize(n);
    RobotPosition.resize(k);

	int v1, v2, w, r; // (v1,v2) is an edge of the graph
	//cout<<"\nEnter edges\n";
	for(int j=0;j<n-1;j++)  // initializing the graph with weights 
	{
		cin>>v1>>v2>>w;  
		G[v1][v2]=w;
		G[v2][v1]=w;
	}
	//cout<<"\nEnter robot positions:\n";
	for(int j=0;j<k;j++)  //getting the position of the robots
	{	
		cin>>RobotPosition[j];
	}
	int time;
	//cout<<"Callinng MIN_EDGE_CUTTING_TIME function";
	time = MIN_EDGE_CUTTING_TIME(k,RobotPosition,n);
	cout<<time;
	//system("pause");
	return 0;
}
