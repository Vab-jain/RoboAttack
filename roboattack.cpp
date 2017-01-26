/*
test graph:
10 6
4 6 4
6 5 4
6 1 2
5 2 5
6 7 4
1 8 3
6 0 2
8 9 10
5 3 7
2
4
9
0
7
5


		 0 1 2 3 4 5 6 7 8  9
		_____________________
	  0 |0 0 0 0 0 0 2 0 0  0
	  1 |0 0 0 0 0 0 2 0 3  0
	  2 |0 0 0 0 0 5 0 0 0  0
	  3 |0 0 0 0 0 7 0 0 0  0
G =   4 |0 0 0 0 0 0 4 0 0  0
	  5 |0 0 5 7 0 0 4 0 0  0
	  6 |2 2 0 0 4 4 0 4 0  0
	  7 |0 0 0 0 0 0 4 0 0  0
	  8 |0 3 0 0 0 0 0 0 0  10
	  9 |0 0 0 0 0 0 0 0 10 0


*/

/* Method for finding path between any two robots a and b */

int path[N] = {};	//path between any two robots
int i=0;			//counter for path[i]

void find_path(int G[N][N], int n, int a, int b)	//n = total no. of vertices		a = robo1		b = robo2
{
	if(path[i-1]!=a)
	{
		path[i] = a;
		if(a!=b)
		{
			for(int j=0; j<N; j++)
			{	
				if(G[a][j]);
				{
					i++;
					find_path(G[N][N],n,j,b);
					i--;
				}
			}
		}
	}
}