#include <iostream>

using namespace std;

int minTime = 0;
struct SET
{	
	int data;
	int rank;
	int weight;
	SET *parent;
	SET *p;
};

SET* MAKE_SET(int v)  // function to make every vertex into a set
{
	SET *ptr=new SET;
	ptr->data=v;
	ptr->rank=0;
	ptr->weight=0;
	ptr->parent=ptr;
	ptr->p=ptr;
	return ptr;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

// A recursive binary search function. It returns location of x in
// given array arr[l..r] is present, otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;

        // If the element is present at the middle itself
        if (arr[mid] == x)  return mid;

        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present in right subarray
        return binarySearch(arr, mid+1, r, x);
   }

   // We reach here when element is not present in array
   return -1;
}


int FIND_SET(int vertex, SET *Sets[])  // to find the representative element of the set
{
	SET *ptr=Sets[vertex];
	while(ptr->p!=ptr)
		ptr=ptr->p;
	return ptr->data;
}


void UNITE(SET *Sets[], int u, int v, int w, int p) {
	int weight, weight1 = w;
	SET *ptr1 = Sets[u];
	SET *ptr = Sets[v];
	SET *temp;
	while(ptr != ptr1)
	{
		temp = ptr->parent;
		weight = weight1;
		weight1	= ptr->weight;
		ptr->parent = ptr1;
		ptr->p=Sets[p];
		ptr->weight = weight;
		ptr1 = ptr;
		ptr = temp;
	}
}


bool CHECKROBOT(int v, int RobotPosition[], int k, SET *Sets[]) {
	if(Sets[v]->rank>0)
		return 1;
	else {
		/*for(int i=0;i<k;i++)
			if(RobotPosition[i] == v)
			{		
				return 1;
			}*/
		if(binarySearch(RobotPosition,0,k-1,v)!=-1)
		{	Sets[v]->rank+=1;
			return 1;
		}
	}
	return 0;	
}

int FIND_MIN(int u, int v, int w, SET *Sets[], int p1, int p2) {
	int min = w, data;
	SET *ptr1, *ptr2;
	ptr1 = Sets[u];
	ptr2 = Sets[v];
	int j=0;
	while(ptr1->parent != ptr1)
	{
		if(ptr1->weight<min) {
			min = ptr1->weight;
			data = ptr1->data;
		}
		ptr1 = ptr1->parent;
	}
	while(ptr2->parent != ptr2)
	{
		if(ptr2->weight<min) {
			min = ptr2->weight;
			data = ptr2->data;
			j++;
		}
		ptr2 = ptr2->parent;
	}
	if(min == w)
		return w;
	else {
		Sets[data]->parent = Sets[data];
		Sets[data]->weight = 0;
		if(j>0)	
			UNITE(Sets,u,v,w,p1);
		else
			UNITE(Sets,v,u,w,p2);
	}
	return min;
}

void UNION(int u, int v, SET *Sets[], int EDGES[][3], int w, int RobotPosition[], int k) {
	int p1 = FIND_SET(u,Sets);
	int p2 = FIND_SET(v,Sets);
	bool c1 = CHECKROBOT(p1,RobotPosition,k,Sets);
	bool c2 = CHECKROBOT(p2,RobotPosition,k,Sets); 
	if(c1 && c2) {
		minTime += FIND_MIN(u,v,w,Sets,p1,p2);
	}
	else if(c1) {
		UNITE(Sets,u,v,w,p1);
	}
		 else {
			UNITE(Sets,v,u,w,p2);
		 }
}


void DIVIDE(int n, int EDGES[][3], int RobotPosition[], int k) {
	SET *Sets[n];
	for(int i=0;i<n;i++)
		Sets[i] = MAKE_SET(i);
	int u, v, w;   // u, v is an edge of the graph
	for(int i=0;i<n-1;i++)
	{
		u = EDGES[i][0];
		v = EDGES[i][1];
		w = EDGES[i][2];
		UNION(u,v,Sets,EDGES,w,RobotPosition,k);
	}	
}

int main() {
	int n, k;    // n is the no of vertices and k is the no of robots
	cin>>n>>k;
	int v1, v2, w;   // (v1,v2) is an edge of the graph and w is the weight of the edge
	int EDGES[n-1][3];
	for(int i=0;i<n-1;i++) {
		cin>>v1>>v2>>w;  // inserting edges into a 2-D array along with weights to store the graph
		EDGES[i][0] = v1;
		EDGES[i][1] = v2;
		EDGES[i][2] = w;
	}
	int RobotPosition[k];
	for(int i=0;i<k;i++)
		cin>>RobotPosition[i];
	mergeSort(RobotPosition,0,k-1);
	DIVIDE(n,EDGES,RobotPosition,k);
	cout<<minTime;
	return 0;
}#include <iostream>

using namespace std;

int minTime = 0;
struct SET
{	
	int data;
	int rank;
	int weight;
	SET *parent;
	SET *p;
};

SET* MAKE_SET(int v)  // function to make every vertex into a set
{
	SET *ptr=new SET;
	ptr->data=v;
	ptr->rank=0;
	ptr->weight=0;
	ptr->parent=ptr;
	ptr->p=ptr;
	return ptr;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

// A recursive binary search function. It returns location of x in
// given array arr[l..r] is present, otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;

        // If the element is present at the middle itself
        if (arr[mid] == x)  return mid;

        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        // Else the element can only be present in right subarray
        return binarySearch(arr, mid+1, r, x);
   }

   // We reach here when element is not present in array
   return -1;
}


int FIND_SET(int vertex, SET *Sets[])  // to find the representative element of the set
{
	SET *ptr=Sets[vertex];
	while(ptr->p!=ptr)
		ptr=ptr->p;
	return ptr->data;
}


void UNITE(SET *Sets[], int u, int v, int w, int p) {
	int weight, weight1 = w;
	SET *ptr1 = Sets[u];
	SET *ptr = Sets[v];
	SET *temp;
	while(ptr != ptr1)
	{
		temp = ptr->parent;
		weight = weight1;
		weight1	= ptr->weight;
		ptr->parent = ptr1;
		ptr->p=Sets[p];
		ptr->weight = weight;
		ptr1 = ptr;
		ptr = temp;
	}
}


bool CHECKROBOT(int v, int RobotPosition[], int k, SET *Sets[]) {
	if(Sets[v]->rank>0)
		return 1;
	else {
		/*for(int i=0;i<k;i++)
			if(RobotPosition[i] == v)
			{		
				return 1;
			}*/
		if(binarySearch(RobotPosition,0,k-1,v)!=-1)
		{	Sets[v]->rank+=1;
			return 1;
		}
	}
	return 0;	
}

int FIND_MIN(int u, int v, int w, SET *Sets[], int p1, int p2) {
	int min = w, data;
	SET *ptr1, *ptr2;
	ptr1 = Sets[u];
	ptr2 = Sets[v];
	int j=0;
	while(ptr1->parent != ptr1)
	{
		if(ptr1->weight<min) {
			min = ptr1->weight;
			data = ptr1->data;
		}
		ptr1 = ptr1->parent;
	}
	while(ptr2->parent != ptr2)
	{
		if(ptr2->weight<min) {
			min = ptr2->weight;
			data = ptr2->data;
			j++;
		}
		ptr2 = ptr2->parent;
	}
	if(min == w)
		return w;
	else {
		Sets[data]->parent = Sets[data];
		Sets[data]->weight = 0;
		if(j>0)	
			UNITE(Sets,u,v,w,p1);
		else
			UNITE(Sets,v,u,w,p2);
	}
	return min;
}

void UNION(int u, int v, SET *Sets[], int EDGES[][3], int w, int RobotPosition[], int k) {
	int p1 = FIND_SET(u,Sets);
	int p2 = FIND_SET(v,Sets);
	bool c1 = CHECKROBOT(p1,RobotPosition,k,Sets);
	bool c2 = CHECKROBOT(p2,RobotPosition,k,Sets); 
	if(c1 && c2) {
		minTime += FIND_MIN(u,v,w,Sets,p1,p2);
	}
	else if(c1) {
		UNITE(Sets,u,v,w,p1);
	}
		 else {
			UNITE(Sets,v,u,w,p2);
		 }
}


void DIVIDE(int n, int EDGES[][3], int RobotPosition[], int k) {
	SET *Sets[n];
	for(int i=0;i<n;i++)
		Sets[i] = MAKE_SET(i);
	int u, v, w;   // u, v is an edge of the graph
	for(int i=0;i<n-1;i++)
	{
		u = EDGES[i][0];
		v = EDGES[i][1];
		w = EDGES[i][2];
		UNION(u,v,Sets,EDGES,w,RobotPosition,k);
	}	
}

int main() {
	int n, k;    // n is the no of vertices and k is the no of robots
	cin>>n>>k;
	int v1, v2, w;   // (v1,v2) is an edge of the graph and w is the weight of the edge
	int EDGES[n-1][3];
	for(int i=0;i<n-1;i++) {
		cin>>v1>>v2>>w;  // inserting edges into a 2-D array along with weights to store the graph
		EDGES[i][0] = v1;
		EDGES[i][1] = v2;
		EDGES[i][2] = w;
	}
	int RobotPosition[k];
	for(int i=0;i<k;i++)
		cin>>RobotPosition[i];
	mergeSort(RobotPosition,0,k-1);
	DIVIDE(n,EDGES,RobotPosition,k);
	cout<<minTime;
	return 0;
}
