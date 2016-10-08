#include<stdio.h>
#include <iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include <cstring>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
#define A 54059 /* a prime */
#define B 76963 /* another prime */
//#define C 86969 /* yet another prime */

map < int , set < vector < int > > > relobject_hash_tables;
int df,V=9,err;
string t__1("tempo");

int tree[300];
int flag[300];

class BTreeNode
{
	unsigned long long int *keys;  
	int t;      
	BTreeNode **C; 
	int n;     
	bool leaf; 
	public:
	BTreeNode(int _t, bool _leaf);   
	void insertNonFull(unsigned long long int k);
	void splitChild(int i, BTreeNode *y);
	void traverse();
	BTreeNode *search(unsigned long long int k);
	friend class BTree;
};


bool cmpstr(string s1,string s2)
{
	string s3,s4;
	s3=s1;
	s4=s2;
	transform( s3.begin(), s3.end(), s3.begin(), ::tolower );
	transform( s4.begin(), s4.end(), s4.begin(), ::tolower );
	return ( s3 == s4 );
}
void cmp(string s,int a)
{
	if(a==0)
		return;
	int b;
	b=a;
	b=b-1;
	cmp(s,b);
	return;
}
bool checknum(string str)
{
	string::iterator iter=str.begin();
	if(str.find("-")!=-1)
	{
		iter++;
	}
	cmp(t__1,10);
	while(iter!=str.end() && isdigit(*iter))
	{
		iter++;
	}
	cmp(t__1,10);
	return !str.empty() && iter==str.end();
}
string space_remove(string str)
{
	cmp(t__1,10);
	string s1(str);
	str.erase(str.begin(), find_if(str.begin(), str.end(), bind1st(not_equal_to<char>(), ' ')));
	str.erase(find_if(str.rbegin(), str.rend(), bind1st(not_equal_to<char>(), ' ')).base(), str.end());
	cmp(t__1,10);	
	return str;
}
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t\t %d\n", i, dist[i]);
}

class BTree
{
	BTreeNode *root; 
	int t;  
	public:	
	BTree(int _t)
	{ 
		root = NULL; 
		 t = _t; 
	}
	BTreeNode* search(unsigned long long int k)
	{  
		return (root == NULL)? NULL : root->search(k); 
	}
	void insert(unsigned long long int k);
};
unsigned long hash1(string str);
unsigned long hash2(string str);
unsigned long hash3(string str);
unsigned long hash4(string str);
unsigned long hash5(string str);
unsigned long hash6(string str);
unsigned long hash7(string str);
unsigned long hash8(string str);
unsigned long hash9(string str);
unsigned long hash10(string str);
unsigned long hash11(string str);
unsigned long hash12(string str);
unsigned long hash13(string str);
unsigned long hash14(string str);
unsigned long hash15(string str);
//BTreeNode::BTreeNode(int t1, bool leaf1);
//BTreeNode *BTreeNode::search(unsigned long long int k);
//void BTree::insert(unsigned long long int k);
//void BTreeNode::insertNonFull(unsigned long long int k);
//void BTreeNode::splitChild(int i, BTreeNode *y);
int calculate(int function_return_hash_value,int val);
int calculate1(int function_return_hash_value,int main_buff);
vector < int > calculate2(vector < int > input_integer_line,int val);
void calculate4(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line);
unsigned long long int calculate9(string input_comma_sep_line);
void calculate5(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line);
void calculate3(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line);
vector< int > calculate8(string file_rel,int attr_len,int main_buff, int algo_type,string input_comma_sep_line,string ints,int val);
vector< int > calculate7(string file_rel,int attr_len,int main_buff, int algo_type,string input_comma_sep_line,string ints,int val);
void Getnext(string file_rel,int attr_len,int main_buff, int algo_type); 
void calculate6(string file_rel,int attr_len,int main_buff, int algo_type);
void open(string file_rel,int attr_len,int main_buff, int algo_type);
void distinct(string file_rel,int attr_len,int main_buff, int algo_type);
void close();


string output_file("output.txt");
ofstream file_out(output_file.c_str());

int function_return_hash_value=0;	

BTreeNode::BTreeNode(int t1, bool leaf1)
{
	t = t1;
	leaf = leaf1;
	keys = new unsigned long long int[2*t-1];
	C = new BTreeNode *[2*t];
	n = 0;
}


void distinct(string file_rel,int attr_len,int main_buff, int algo_type)
{
	open(file_rel,attr_len,main_buff,algo_type);
	close();
	return;
}
void close()
{
	file_out.close();
	return;
}
void dijkstra(int graph[9][9], int src)
{
	int V=9;

     int dist[V];     
     bool sptSet[V]; 
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
 for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
 for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
 for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
 for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
 for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
     dist[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }


 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
 for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
     printSolution(dist, V);
}

int calc(int node,int a,int b,int l,int h,int count)
{
	if(b<a || l<a || h>b || l>h)
		return 0;
	int m=(a+b)>>1;
	int lx=node*2;
	int rx=lx+1;

	if(a==l && b==h)
	{
		if(count)
			return b-a+1-tree[node];
		return tree[node];
	}
	count=count^flag[node];

	if(h<=m)
		return calc(lx,a,m,l,h,count);
	else
	{
		if(l>m)
			return calc(rx,m+1,b,l,h,count);
		else
			return calc(lx,a,m,l,m,count)+calc(rx,m+1,b,m+1,h,count);
	}

}

void computeLPSArray(char *pat, int M, int *lps);

void BTreeNode::insertNonFull(unsigned long long int k)
{
	int i = n-1;
	if (leaf == true)
	{
		while (i >= 0 && keys[i] > k)
		{
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n = n+1;
	}
	else 
	{
		while (i >= 0 && keys[i] > k)
			i--;
		if (C[i+1]->n == 2*t-1)
		{
			splitChild(i+1, C[i+1]);
			if (keys[i+1] < k)
				i++;
		}
		C[i+1]->insertNonFull(k);
	}
}




int calculate(int function_return_hash_value,int val)
{
	function_return_hash_value=function_return_hash_value+val;
	return function_return_hash_value;
}
int calculate1(int function_return_hash_value,int main_buff)
{
	function_return_hash_value=function_return_hash_value%main_buff;
	return function_return_hash_value;
}
vector < int > calculate2(vector < int > input_integer_line,int val)
{
	vector < int > tempo_var;
	tempo_var=input_integer_line;
	tempo_var.push_back(val);
	return tempo_var;
}
BTree bite(3); 
void calculate3(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line)
{
	if(algo_type==0)
	{
		calculate4(file_rel,attr_len,main_buff,algo_type,function_return_hash_value,input_integer_line,input_comma_sep_line);
	}
	else
	{
		calculate5(file_rel,attr_len,main_buff,algo_type,function_return_hash_value,input_integer_line,input_comma_sep_line);
	}

}
vector< int > calculate8(string file_rel,int attr_len,int main_buff, int algo_type,string input_comma_sep_line,string ints,int val)
{
	vector < int > integer_tempo;
	integer_tempo.clear();
	stringstream file_line2(input_comma_sep_line);
	function_return_hash_value=0;
	while(getline(file_line2,ints,','))
	{
		val=atoi(ints.c_str());
		function_return_hash_value=calculate(function_return_hash_value,val);
		function_return_hash_value=calculate1(function_return_hash_value,main_buff);
		integer_tempo=calculate2(integer_tempo,val);
	}
	return integer_tempo;

}
vector< int > calculate7(string file_rel,int attr_len,int main_buff, int algo_type,string input_comma_sep_line,string ints,int val)
{
	vector < int > integer_tempo;
	integer_tempo.clear();
	stringstream file_line2(input_comma_sep_line);
	function_return_hash_value=0;
	integer_tempo=calculate8(file_rel,attr_len,main_buff,algo_type,input_comma_sep_line,ints,val);
	/*
	   while(getline(file_line2,ints,','))
	   {
	   val=atoi(ints.c_str());
	   function_return_hash_value=calculate(function_return_hash_value,val);
	   function_return_hash_value=calculate1(function_return_hash_value,main_buff);
	   integer_tempo=calculate2(integer_tempo,val);
	   }*/
	return integer_tempo;
}


void open(string file_rel,int attr_len,int main_buff, int algo_type)
{
	calculate6(file_rel,attr_len,main_buff,algo_type);
	Getnext(file_rel,attr_len,main_buff,algo_type);
	return;
}


int main()
{
	string hsh("hash");
	string btr("btree");
	string file_rel;
	string algo;
	int attr_len;
	int main_buff;
	int algo_type;
	cin>>file_rel;
	cin>>attr_len;
	cin>>main_buff;
	cin>>algo;
	if(algo.compare(hsh))
	{
		algo_type=0;
	}
	else
	{
		algo_type=1;
	}
//	cin>>algo_type;
	distinct(file_rel,attr_len,main_buff,algo_type);
	return 0;
}

unsigned long hash1(string str)
{
	unsigned long hash = 5381;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash << 5) + hash);
		hash+= *it; /* hash * 33 + character */
	}
	return hash;
}


unsigned long hash2(string str)
{
	unsigned long hash = 86969;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}

	return hash;
}

unsigned long hash3(string str)
{
	unsigned long hash = 9791;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash4(string str)
{
	unsigned long hash = 9787;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
void Getnext(string file_rel,int attr_len,int main_buff, int algo_type)
{
	int val;
	ifstream inp(file_rel.c_str());
	string input_comma_sep_line,ints;
	vector < int > input_integer_line;
	while(getline(inp,input_comma_sep_line))
	{
		input_integer_line.clear();
		input_integer_line=calculate7(file_rel,attr_len,main_buff,algo_type,input_comma_sep_line,ints,val);
		calculate3(file_rel,attr_len,main_buff,algo_type,function_return_hash_value,input_integer_line,input_comma_sep_line);
	}
	inp.close();
	//file_out.close();
	return;
}
unsigned long hash5(string str)
{
	unsigned long hash = 8999;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash6(string str)
{
	unsigned long hash = 8353;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
int bs(int px,int py,int arr[])
{
	int l,u,mid;
	l=0,u=px;
	while(l<=u)
	{
		mid=(l+u)/2;
		if(py==arr[mid])
		{
			return 1;
			break;
		}
		else if(py<arr[mid])
		{
			u=mid-1;
		}
		else
			l=mid+1;
	}
	return 0;
}
void KMPSearch(char *pat, char *txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	// create lps[] that will hold the longest prefix suffix values for pattern
	int *lps = (int *)malloc(sizeof(int)*M);
	int j  = 0;  // index for pat[]

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);

	int i = 0;  // index for txt[]
	while(i < N)
	{
		if(pat[j] == txt[i])
		{
			j++;
			i++;
		}

		if (j == M)
		{
			printf("Found pattern at index %d \n", i-j);
			j = lps[j-1];
		}

		// mismatch after j matches
		else if(pat[j] != txt[i])
		{
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if(j != 0)
				j = lps[j-1];
			else
				i = i+1;
		}
	}
	free(lps); // to avoid memory leak
}

void computeLPSArray(char *pat, int M, int *lps)
{
	int len = 0;  // lenght of the previous longest prefix suffix
	int i;

	lps[0] = 0; // lps[0] is always 0
	i = 1;

	// the loop calculates lps[i] for i = 1 to M-1
	while(i < M)
	{
		if(pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len])
		{
			if( len != 0 )
			{
				// This is tricky. Consider the example AAACAAAA and i = 7.
				len = lps[len-1];

				// Also, note that we do not increment i here
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

int minVal(int x, int y) { return (x < y)? x: y; }

int getMid(int s, int e) {  return s + (e -s)/2;  }

int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
	// If segment of this node is a part of given range, then return the
	// min of the segment
	if (qs <= ss && qe >= se)
		return st[index];

	// If segment of this node is outside the given range
	if (se < qs || ss > qe)
		return INT_MAX;

	// If a part of this segment overlaps with the given range
	int mid = getMid(ss, se);
	return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
			RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}

int RMQ(int *st, int n, int qs, int qe)
{
	// Check for erroneous input values
	if (qs < 0 || qe > n-1 || qs > qe)
	{
		printf("Invalid Input");
		return -1;
	}

	return RMQUtil(st, 0, n-1, qs, qe, 0);
}
int constructSTUtil(int arr[], int ss, int se, int *st, int si)
{
	
	if (ss == se)
	{
		st[si] = arr[ss];
		return arr[ss];
	}
	int mid = getMid(ss, se);
	st[si] =  minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
			constructSTUtil(arr, mid+1, se, st, si*2+2));
	return st[si];
}
int *constructST(int arr[], int n)
{
	
	int x = (int)(ceil(log2(n))); //Height of segment tree
	int max_size = 2*(int)pow(2, x) - 1; //Maximum size of segment tree
	int *st = new int[max_size];

	constructSTUtil(arr, 0, n-1, st, 0);
	return st;
}

void BTree::insert(unsigned long long int k)
{
	if (root == NULL)
	{
		root = new BTreeNode(t, true);
		root->keys[0] = k;  
		root->n = 1;  
	}
	else 
	{
		
		if (root->n == 2*t-1)
		{
			
			BTreeNode *s = new BTreeNode(t, false);
			s->C[0] = root;
			s->splitChild(0, root);
			int i = 0;
			if (s->keys[0] < k)
				i++;
			s->C[i]->insertNonFull(k);
			root = s;
		}
		else  
			root->insertNonFull(k);
	}
}
unsigned long hash7(string str)
{
	unsigned long hash = 7603;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash8(string str)
{
	unsigned long hash = 7877;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash9(string str)
{
	unsigned long hash = 8171;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash10(string str)
{
	unsigned long hash = 10691;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash11(string str)
{
	unsigned long hash = 10039;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash12(string str)
{
	unsigned long hash = 9319;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash13(string str)
{
	unsigned long hash = 8089;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
unsigned long hash14(string str)
{
	unsigned long hash = 9949;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
template<class T>
class BIT
{
	T *tree;
	int maxVal;
	public:
	BIT(int N)
	{
		tree = new T[N+1];
		memset(tree,0,sizeof(T)*(N+1));
		maxVal = N;
	}
	void update(int idx, T val)
	{
		while (idx <= maxVal)
		{
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
	T read(int idx)
	{
		T sum=0;
		while (idx>0)
		{
			sum += tree[idx];
			idx -= (idx & -idx);
		}
		return sum;
	}
};

typedef struct profile{
	char gender[1];
	double soc;
} PROFILE;

int compare(const void *p1, const void *p2)
{
	const struct profile *elem1;    
	const struct profile *elem2;
	if ( elem1->soc < elem2->soc)
		return -1;
	else if (elem1->soc > elem2->soc)
		return 1;
	else
		return 0;
}

struct suffix
{
	int index;
	char *suff;
};

int cmp(struct suffix a, struct suffix b)
{
	return strcmp(a.suff, b.suff) < 0? 1 : 0;
}

int *buildSuffixArray(char *txt, int n)
{

	struct suffix suffixes[n];

	for (int i = 0; i < n; i++)
	{
		suffixes[i].index = i;
		suffixes[i].suff = (txt+i);
	}


	int *suffixArr = new int[n];
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index;

	return  suffixArr;
}


void printArr(int arr[], int n)
{
	for(int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void search(char *pat, char *txt, int *suffArr, int n)
{
	int m = strlen(pat);  

	int l = 0, r = n-1;  
	while (l <= r)
	{
		int mid = l + (r - l)/2;
		int res = strncmp(pat, txt+suffArr[mid], m);

		if (res == 0)
		{
			cout << "Pattern found at index " << suffArr[mid];
			return;
		}

		if (res < 0) r = mid - 1;

		else l = mid + 1;
	}

	cout << "Pattern not found";
}
BTreeNode *BTreeNode::search(unsigned long long int k)
{
	
	int i = 0;
	while (i < n && k > keys[i])
		i++;
	if (keys[i] == k)
		return this;
	if (leaf == true)
		return NULL;
	return C[i]->search(k);
}
unsigned long hash15(string str)
{
	unsigned long hash = 10331;
	string::iterator it;
	for(it=str.begin();it!=str.end();it++)
	{
		hash = ((hash *A)^((*it)*B));
	}
	return hash;
}
void calculate4(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line)
{
	if(relobject_hash_tables[function_return_hash_value].find(input_integer_line)==relobject_hash_tables[function_return_hash_value].end())
	{
		relobject_hash_tables[function_return_hash_value].insert(input_integer_line);
//		cout<<input_comma_sep_line<<endl;
		file_out<<input_comma_sep_line<<endl;
	}
}
void calculate6(string file_rel,int attr_len,int main_buff, int algo_type)
{
	if(algo_type==0) 
	{
		relobject_hash_tables.clear();
		return;
	}
	else 
	{
		return;
		
	}
}
unsigned long long int calculate9(string input_comma_sep_line)
{
	unsigned long long int hash_val=hash1(input_comma_sep_line);
	unsigned long long int hash_val2=hash2(input_comma_sep_line);
	unsigned long long int hash_val3=hash3(input_comma_sep_line);
	unsigned long long int hash_val4=hash4(input_comma_sep_line);
	unsigned long long int hash_val5=hash5(input_comma_sep_line);
	unsigned long long int hash_val6=hash6(input_comma_sep_line);
	unsigned long long int hash_val7=hash7(input_comma_sep_line);
	unsigned long long int hash_val8=hash8(input_comma_sep_line);
	unsigned long long int hash_val9=hash9(input_comma_sep_line);
	unsigned long long int hash_val10=hash10(input_comma_sep_line);
	unsigned long long int hash_val11=hash11(input_comma_sep_line);
	unsigned long long int hash_val12=hash12(input_comma_sep_line);
	unsigned long long int hash_val13=hash13(input_comma_sep_line);
	unsigned long long int hash_val14=hash14(input_comma_sep_line);
	unsigned long long int hash_val15=hash15(input_comma_sep_line);
	unsigned long long int hash_v=hash_val^hash_val2^hash_val3^hash_val4^hash_val5^hash_val6^hash_val7^hash_val8^hash_val9^hash_val10^hash_val11^hash_val12^hash_val13^hash_val14^hash_val15;
	return hash_val;
}
void calculate5(string file_rel,int attr_len,int main_buff, int algo_type,int function_return_hash_value,vector < int > input_integer_line,string input_comma_sep_line)
{
	unsigned long long int hash_val=hash1(input_comma_sep_line);
	if(bite.search(hash_val) == NULL)
	{
//		cout<<input_comma_sep_line<<endl;
		file_out<<input_comma_sep_line<<endl;
		bite.insert(hash_val);
	}
}
#define mod 1000000007
#define f(i,a,b) for(i=a;i<b;i++)
#define ff(i,a) for(i=0;i<a;i++)
//#define sc scanf
//#define pr printf
#define clr(a) memset(a,0,sizeof(a))
#define ll long long
#define vi vector<int>
#define pin(n) printf("%d\n",n)
#define pll(n) printf("%lld\n",n)
#define sin(n) scanf("%d",&n)
#define sll(n) scanf("%lld",&n)
#define pins(n) printf("%d ",n)
#define plls(n) printf("%lld ",n)
#define ss(n) scanf("%s",n)
#define nl pr("\n")


inline void sins(int &x)
{
	register int c = getchar_unlocked();
	x = 0;
	int neg = 0;
	for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());
	if(c=='-') {
		neg = 1;
		c = getchar_unlocked();
	}
	for(; c>47 && c<58 ; c = getchar_unlocked()) {
		x = (x<<1) + (x<<3) + c - 48;
	}
	if(neg)
		x = -x;
}

void flip(int node,int a,int b,int l,int h)
{
	if(b<a || l<a || h>b || l>h)
		return;

	int m=(a+b)>>1;

	int lx=node*2;
	int rx=lx+1;

	if(l==a && h==b)
	{
		flag[node]=flag[node]^1;
		tree[node]=b-a+1-tree[node];
		return;
	}
	if(h<=m)
		flip(lx,a,m,l,h);
	else
	{
		if(l>m)
			flip(rx,m+1,b,l,h);
		else
		{
			flip(lx,a,m,l,m);
			flip(rx,m+1,b,m+1,h);
		}
	}

	tree[node]=tree[lx]+tree[rx];
	if(flag[node])
		tree[node]=b-a+1-tree[node];

}

void chk_exit()
{
	if(err==1)
	{
		exit(0);
	}
}
void BTreeNode::splitChild(int i, BTreeNode *y)
{
	
	BTreeNode *z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;
	for (int j = 0; j < t-1; j++)
		z->keys[j] = y->keys[j+t];
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j+t];
	}
	y->n = t - 1;
	for (int j = n; j >= i+1; j--)
		C[j+1] = C[j];
	C[i+1] = z;
	for (int j = n-1; j >= i; j--)
		keys[j+1] = keys[j];
	keys[i] = y->keys[t-1];
	n = n + 1;
}
