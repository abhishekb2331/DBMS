#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
string input_file;
vector<string> sort_col;
vector<string>col;
vector<int>col_size;
int main_mem_size;
int record_size;
int block_size;
int total_record; //total no. of record
int file_cnt;
map<string ,int>col_mapper;


string R_input_file;
string S_input_file;
string type;
string output_file;
int sort_flag;
vector<string> R_sort_col;
vector<string> R_col;
vector<int> R_col_size;
vector<string> S_sort_col;
vector<string> S_col;
vector<int> S_col_size;
int no_block;  //no of  block in mm;
int no_record_blk;
int err;
int R_file_cnt;
int S_file_cnt;
int R_total_record; //total no. of record
int S_total_record; //total no. of record

map<string ,int>R_col_mapper;
map<string ,int>S_col_mapper;
map<string ,int>R_Y;
map<string ,int>S_Y;
ifstream *file_ptr; 
//ifstream *R_file_ptr; 
//ifstream *S_file_ptr; 
int *R_hash;
int *S_hash;

char ****mainmm_buff;
int *block_fill;
int *block_ptr;
char **cmp_str;

void chk_exit()
{
	if(err==1)
	{
		exit(0);
	}
}

string  SplitFilename (const std::string& str)
{
//	  std::cout << "Splitting: " << str << '\n';
	   unsigned found = str.find_last_of("/\\");
	     // std::cout << " path: " << str.substr(0,found) << '\n';
	    // std::cout << " file: " << str.substr(found+1) << '\n';
	   return str.substr(found+1);
}

int  hash(string key, int tableSize)
{
	unsigned hashVal = 0;
	for (int x = 0; x < key.length(); ++x)
	{
		hashVal ^= (hashVal << 5) +
			(hashVal >> 2) +
			key[x];
	}
	return hashVal % tableSize;
}
void calculate_block_size()
{


	/*	
		if(record_size>(main_mem_size*800000))
		{
		err=1;chk_exit();
		return;
		}
		int no_of_sorted_files,block_len,bl_size,no_of_record_mm;
		no_of_record_mm=((main_mem_size*800000)/record_size)/col.size();
		no_of_sorted_files=(int)(ceil((total_record*1.0)/no_of_record_mm));
	//	if(no_of_sorted_files==0)
	//		no_of_sorted_files=1;
	block_len=no_of_sorted_files+1; //for output buffer
	no_block=block_len;
	//	cout<<main_mem_size<<' '<<block_len<<endl;
	bl_size=((main_mem_size*800000)/block_len)/col.size();
	block_size=bl_size;
	//	cout<<bl_size<<' '<<no_block<<endl;
	if(record_size>bl_size)
	{
	err=1;chk_exit();
	return;
	}
	 */	

	//	no_record_blk=bl_size/record_size;
	no_record_blk=100;

	//	cout<<no_record_blk<<endl;
	return;
}

/*
   void extract()
   {
   ifstream file1("metadata.txt");
   string file_line,file_line1;
   int tmp,tmp1;
   record_size=0;
   if(file1.is_open())
   {
   tmp1=0;
   while(getline(file1,file_line))
   {
//	file1>>file_line1;
stringstream file_line2(file_line);
string out1;
tmp=0;
while(getline(file_line2,out1,','))
{
//				cout<<out1<<endl;
if(tmp==0)
{
col.push_back(out1);
col_mapper[out1]=tmp1;
}
else
{
col_size.push_back(atoi(out1.c_str()));
record_size+=atoi(out1.c_str());
}
tmp=tmp^1;
//out1.erase(remove( out1.begin(), out1.end(), '\"' ),out1.end());
//	data_in.push_back(atoi(out1.c_str()));
}
tmp1++;
}
file1.close();
//	cout<<record_size<<endl;
}
else
{
cout<<"Cannot open file: metadata.txt"<<endl;
err=1;chk_exit();
}

}
 */
/*
   int cmp(const void *pa,const void *pb)
   {
   const char **a=*(const char ***)pa;
   const char **b=*(const char ***)pb;
   int i,j;
   for(i=0;i<sort_col.size();i++)
   {
   j=col_mapper[sort_col[i]];
   if(sort_flag==1)
   {
   if(strcmp(a[j],b[j])!=0)
   {
   return strcmp(a[j],b[j]);
   }
   }
   else
   {
   if(strcmp(a[j],b[j])!=0)
   {
   return (strcmp(b[j],a[j]));
   }

   }

   }
   return 0;
   }
 */
int R_cmp(const void *pa,const void *pb)
{
	const char **a=*(const char ***)pa;
	const char **b=*(const char ***)pb;
	int i,j;
	j=R_col_mapper["Y"];
	return strcmp(a[j],b[j]);
}
int S_cmp(const void *pa,const void *pb)
{
	const char **a=*(const char ***)pa;
	const char **b=*(const char ***)pb;
	int i,j;
	j=S_col_mapper["Y"];
	return strcmp(a[j],b[j]);
}
int check_str(int i)
{

	//strcpy(cmp_str[j],mainmm_buff[i][block_ptr[i]][j]);
	int j,k,l;
	//cout<<"compare string start"<<endl<<endl;
	for(j=0;j<sort_col.size();j++)
	{
		k=col_mapper[sort_col[j]];
		l=strcmp(cmp_str[k],mainmm_buff[i][block_ptr[i]][k]);
		//	cout<<cmp_str[k]<< ' '<<mainmm_buff[i][block_ptr[i]][k]<<endl;
		if(sort_flag==1)
		{
			if(l!=0)
			{
				//		cout<<"compare string start  "<<l<<endl<<endl;
				return l;
			}
		}
		else
		{
			if(l!=0)
			{
				//		cout<<"compare string start  "<<l<<endl<<endl;
				return -l;
			}
		}
	}
	//cout<<"compare string start"<<endl<<endl;
	return 0;
}
void R_sort_input()
{
	int record_len,i;
	string file_wr("R_temp");
	R_file_cnt=0;
	int col_len=R_col.size();
	record_len=no_record_blk*no_block;
	//	record_len=((main_mem_size*800000)/record_size)/col_len;
	/*
	   string ** inp;
	   inp=(string **)malloc(record_len*sizeof(string *));
	   cout<<col.size()<<endl;
	   for(i=0;i<record_len;i++)
	   {
	   inp[i]=(string *) malloc((col_len)*sizeof(string));
	   }
	   return strcmp(a[0],b[0]);
	   returort_flag[i]] strcmp(a[0],b[0]);
	 */
	ifstream file1(R_input_file.c_str());
	string file_line,file_line1;
	int tmp,tmp1;


	R_total_record=0;
	char ***inp;
	int j;
	inp=(char ***)malloc(record_len*sizeof(char **));
	for(i=0;i<record_len;i++)
	{
		inp[i]=(char **) malloc((col_len)*sizeof(char *));
		//inp[i]=(char **) malloc((col_len)*sizeof(char *));
		for(j=0;j<col_len;j++)
		{
			inp[i][j]=(char *)malloc((record_size)*sizeof(char));
		}
	}


	//	cout<<record_len<<' '<<col_len<<' '<<record_size<<endl;
	//	cout<<record_len<<' '<<col_len<<' '<<record_size<<endl;
	//	inp[0][0]=(char *)"aaaabbbb";
	//	inp[1][0]=(char *)"bbbbaaaa";
	//	cout<<inp[1][0]<<' '<<inp[0][0]<<endl;
	//	cout<<col.size()<<' '<<sizeof(string)<<endl;
	//	inp[record_len-1][1]=(char *)"aasdasdasdasda";
	//	cout<<inp[record_len-1][1]<<endl;

	//	record_len=2;				//testing purpose

	if(file1.is_open())
	{
		tmp=0;
		while(getline(file1,file_line))
		{
			R_total_record++;
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			while(getline(file_line2,out1,' '))
			{
				//				cout<<inp[0][0]<<endl;
				//			char *t=(char *)out1.c_str();
				//			cout<<t<<endl;
				if(tmp1==1)
				{
					R_Y[out1]++;
				}
				strcpy(inp[tmp][tmp1],out1.c_str());
				//				inp[tmp][tmp1]=(char *)(out1.c_str());
				//			cout<<inp[tmp][tmp1]<< ' ' << tmp <<' '<< tmp1<<endl ;
				//			cout<<out1<<' '<<tmp<<' '<<tmp1<<endl;
				//				cout<<inp[0][0]<<endl;
				tmp1++;
			}
			//			cout<<"end"<< inp[0][0]<<endl;
			tmp++;
			if(tmp==record_len)
			{
				//cout<<endl;
				char str[15];
				sprintf(str, "%d", R_file_cnt);
				qsort(inp,tmp,sizeof(inp[0]),R_cmp);
				string tgh;
				tgh=file_wr+str;
				ofstream filew(tgh.c_str());
				R_file_cnt++;
				for(i=0;i<tmp;i++)
				{
					for(j=0;j<R_col.size()-1;j++)
					{
						filew<<inp[i][j]<<' ';
					}
					filew<<inp[i][j]<<endl;
					//					filew<<endl;
				}
				filew.close();
				tmp=0;
			}
		}
		if(tmp!=0)
		{
			/*
			   for(i=0;i<tmp;i++)
			   {
			   cout<<inp[i][0]<<endl;
			   }
			   cout<<endl;
			   cout<<endl;
			   cout<<endl;
			   cout<<endl;
			 */
			//		qsort(inp,tmp,sizeof(inp[0]),cmp);
			char str[15];
			sprintf(str, "%d", R_file_cnt);
			qsort(inp,tmp,sizeof(inp[0]),R_cmp);
			string tgh;
			tgh=file_wr+str;
			ofstream filew(tgh.c_str());
			R_file_cnt++;
			for(i=0;i<tmp;i++)
			{
				for(j=0;j<R_col.size()-1;j++)
				{
					filew<<inp[i][j]<<' ';
				}
				filew<<inp[i][j]<<endl;
				//				filew<<endl;
			}
			filew.close();
			tmp=0;
		}
		file1.close();
		for(i=0;i<record_len;i++)
		{
			for(j=0;j<col_len;j++)
			{
				free(inp[i][j]);
			}
			free(inp[i]);
		}
		free(inp);
	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}

}
void S_sort_input()
{
	int record_len,i;
	string file_wr("S_temp");
	S_file_cnt=0;
	int col_len=S_col.size();
	//record_len=((main_mem_size*800000)/record_size)/col_len;
	record_len=no_record_blk*no_block;
	//	record_len=((main_mem_size*800000)/record_size)/col_len;
	/*
	   string ** inp;
	   inp=(string **)malloc(record_len*sizeof(string *));
	   cout<<col.size()<<endl;
	   for(i=0;i<record_len;i++)
	   {
	   inp[i]=(string *) malloc((col_len)*sizeof(string));
	   }
	   return strcmp(a[0],b[0]);
	   returort_flag[i]] strcmp(a[0],b[0]);
	 */
	ifstream file1(S_input_file.c_str());
	string file_line,file_line1;
	int tmp,tmp1;


	S_total_record=0;
	char ***inp;
	int j;
	inp=(char ***)malloc(record_len*sizeof(char **));
	for(i=0;i<record_len;i++)
	{
		inp[i]=(char **) malloc((col_len)*sizeof(char *));
		//inp[i]=(char **) malloc((col_len)*sizeof(char *));
		for(j=0;j<col_len;j++)
		{
			inp[i][j]=(char *)malloc((record_size)*sizeof(char));
		}
	}


	//	cout<<record_len<<' '<<col_len<<' '<<record_size<<endl;
	//	cout<<record_len<<' '<<col_len<<' '<<record_size<<endl;
	//	inp[0][0]=(char *)"aaaabbbb";
	//	inp[1][0]=(char *)"bbbbaaaa";
	//	cout<<inp[1][0]<<' '<<inp[0][0]<<endl;
	//	cout<<col.size()<<' '<<sizeof(string)<<endl;
	//	inp[record_len-1][1]=(char *)"aasdasdasdasda";
	//	cout<<inp[record_len-1][1]<<endl;

	//	record_len=2;				//testing purpose

	if(file1.is_open())
	{
		tmp=0;
		while(getline(file1,file_line))
		{
			S_total_record++;
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			while(getline(file_line2,out1,' '))
			{
				//				cout<<inp[0][0]<<endl;
				//			char *t=(char *)out1.c_str();
				//			cout<<t<<endl;
				if(tmp1==0)
				{
					S_Y[out1]++;
				}
				strcpy(inp[tmp][tmp1],out1.c_str());
				//				inp[tmp][tmp1]=(char *)(out1.c_str());
				//			cout<<inp[tmp][tmp1]<< ' ' << tmp <<' '<< tmp1<<endl ;
				//			cout<<out1<<' '<<tmp<<' '<<tmp1<<endl;
				//				cout<<inp[0][0]<<endl;
				tmp1++;
			}
			//			cout<<"end"<< inp[0][0]<<endl;
			tmp++;
			if(tmp==record_len)
			{
				//cout<<endl;
				char str[15];
				sprintf(str, "%d", S_file_cnt);
				qsort(inp,tmp,sizeof(inp[0]),S_cmp);
				string tgh;
				tgh=file_wr+str;
				ofstream filew(tgh.c_str());
				S_file_cnt++;
				for(i=0;i<tmp;i++)
				{
					for(j=0;j<S_col.size()-1;j++)
					{
						filew<<inp[i][j]<<' ';
					}
					filew<<inp[i][j]<<endl;
					//					filew<<endl;
				}
				filew.close();
				tmp=0;
			}
		}
		if(tmp!=0)
		{
			/*
			   for(i=0;i<tmp;i++)
			   {
			   cout<<inp[i][0]<<endl;
			   }
			   cout<<endl;
			   cout<<endl;
			   cout<<endl;
			   cout<<endl;
			 */
			//		qsort(inp,tmp,sizeof(inp[0]),cmp);
			char str[15];
			sprintf(str, "%d", S_file_cnt);
			qsort(inp,tmp,sizeof(inp[0]),S_cmp);
			string tgh;
			tgh=file_wr+str;
			ofstream filew(tgh.c_str());
			S_file_cnt++;
			for(i=0;i<tmp;i++)
			{
				for(j=0;j<S_col.size()-1;j++)
				{
					filew<<inp[i][j]<<' ';
				}
				filew<<inp[i][j]<<endl;
				//				filew<<endl;
			}
			filew.close();
			tmp=0;
		}
		file1.close();
		for(i=0;i<record_len;i++)
		{
			for(j=0;j<col_len;j++)
			{
				free(inp[i][j]);
			}
			free(inp[i]);
		}
		free(inp);
	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}

}
void get_record(int i /*, char* inp[col.size()][record_size]*/ , int no_record_block)
{
	string file_line,file_line1;
	int tmp,tmp1;
	if(file_ptr[i].is_open())
	{
		tmp=0;
		while(getline(file_ptr[i],file_line))
		{
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			while(getline(file_line2,out1,' '))
			{
				strcpy(mainmm_buff[i][tmp][tmp1],out1.c_str());
				tmp1++;
				if(tmp1==col.size())
					break;
			}
			tmp++;
			if(tmp==no_record_block)
			{
				block_fill[i]=no_record_block;
				block_ptr[i]=0;
				return;
			}
		}
		block_fill[i]=tmp;
		block_ptr[i]=0;

	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}
	return;

}
void merge_sort()
{
	string R_file_wr("R_temp");
	string S_file_wr("S_temp");
	char str[15];
	string tgh;
	ofstream file_out(output_file.c_str());
	file_ptr=new ifstream[R_file_cnt+S_file_cnt];
	int i,j,k;
	//printf("entered\n");
	for(i=0;i<R_file_cnt;i++)
	{
		sprintf(str, "%d",i);
		tgh=R_file_wr+str;
		file_ptr[i].open(tgh.c_str());
	}
	for(j=0;j<S_file_cnt;j++)
	{
		sprintf(str, "%d",j);
		tgh=S_file_wr+str;
		file_ptr[i].open(tgh.c_str());
		i++;
	}
	file_cnt=R_file_cnt+S_file_cnt;
	block_fill=(int *)malloc(file_cnt*sizeof(int));
	block_ptr=(int *)malloc(file_cnt*sizeof(int));
	mainmm_buff=(char ****)malloc(file_cnt*sizeof(char ***));
	for(i=0;i<file_cnt;i++)
	{
		block_fill[i]=0;
		block_ptr[i]=0;
		mainmm_buff[i]=(char ***)malloc(no_record_blk*sizeof(char **));
		for(j=0;j<no_record_blk;j++)
		{
			mainmm_buff[i][j]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff[i][j][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
	}
	/*
	   cmp_str=(char **)malloc((R_col.size())*sizeof(char *));
	   for(k=0;k<col.size();k++)
	   {
	   cmp_str[k]=(char *)malloc(record_size*sizeof(char));
	   }
	 */
	for(i=0;i<file_cnt;i++)
	{
		get_record(i,no_record_blk);
	}
	block_fill[file_cnt-1]=no_record_blk;
	int chk,rec,ret;
	char R_min[record_size];
	char S_min[record_size];
	chk=0;
	while(chk!=1)
	{
		rec=-1;
		for(i=0;i<R_file_cnt;i++)
		{
			chk=1;
			if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
			{
				rec=i;
				strcpy(R_min,mainmm_buff[i][block_ptr[i]][1]);
				chk=0;
				break;
			}
		}
		if(rec!=-1)
		{
			for(i=rec+1;i<R_file_cnt;i++)
			{
				if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
				{
					if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])>0)
					{
						rec=i;
						strcpy(R_min,mainmm_buff[i][block_ptr[i]][1]);
					}
				}
			}

		}
		if(chk!=1)
		{
			rec=-1;
			for(i=R_file_cnt;i<file_cnt;i++)
			{
				chk=1;
				if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
				{
					rec=i;
					strcpy(S_min,mainmm_buff[i][block_ptr[i]][0]);
					chk=0;
					break;
				}
			}
			if(rec!=-1)
			{
				for(i=rec+1;i<file_cnt;i++)
				{
					if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
					{
						if(strcmp(S_min,mainmm_buff[i][block_ptr[i]][0])>0)
						{
							rec=i;
							strcpy(S_min,mainmm_buff[i][block_ptr[i]][0]);
						}
					}
				}

			}

		}
		if(chk!=1)
		{
			//printf("%s %s\n",R_min,S_min);
			if(strcmp(R_min,S_min)>0)
			{
				for(i=R_file_cnt;i<file_cnt;i++)
				{
					while(block_fill[i]!=0)
					{
						if(strcmp(S_min,mainmm_buff[i][block_ptr[i]][0])==0)
						{
							block_ptr[i]++;
							if(block_ptr[i]==block_fill[i])
							{
								get_record(i,no_record_blk);
							}

						}
						else
							break;
					}
				}
			}
			else if(strcmp(R_min,S_min)<0)
			{
				for(i=0;i<R_file_cnt;i++)
				{
					while(block_fill[i]!=0)
					{
						if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])==0)
						{
							block_ptr[i]++;
							if(block_ptr[i]==block_fill[i])
							{
								get_record(i,no_record_blk);
							}

						}
						else
							break;
					}
				}
			}
			else
			{

				//THe 2 should Join Thus check which Algo To use 1pass, nested loop or none.
				int flag;
				int R_tuple,S_tuple;
				R_tuple=R_Y[R_min];
				S_tuple=S_Y[S_min];
				int tuple;
				tuple=(no_block-file_cnt)*no_record_blk;
				int no_buff;
				no_buff=no_block-file_cnt;
				int R_block=R_tuple/no_record_blk;
				int S_block=S_tuple/no_record_blk;
				R_block++;
				S_block++;
				//printf("%d %d %d\n",R_tuple,S_tuple,tuple);
				if(tuple>=R_tuple+S_tuple)
				{
					int cnt1,cnt2;
					cnt1=0;
					cnt2=0;
					//printf("%d\n",cnt1);
					//WHole Tuple fits in MM
					char ***mainmm_buff1=(char ***)malloc(R_tuple*sizeof(char**));
					for(i=0;i<R_tuple;i++)
					{
						mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}


					//printf("%d\n",cnt1);
					char ***mainmm_buff2=(char ***)malloc(S_tuple*sizeof(char**));
					for(i=0;i<S_tuple;i++)
					{
						mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}
					for(i=0;i<R_file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							//printf("%d\n",i);
							if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])==0)
							{
								for(j=0;j<R_col.size();j++)
								{
									strcpy(mainmm_buff1[cnt1][j],mainmm_buff[i][block_ptr[i]][j]);
									//	cout<<cmp_str[j]<<' ';
								}
								cnt1++;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					//printf("%d\n",cnt1);
					for(i=R_file_cnt;i<file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(S_min,mainmm_buff[i][block_ptr[i]][0])==0)
							{
								for(j=0;j<S_col.size();j++)
								{
									strcpy(mainmm_buff2[cnt2][j],mainmm_buff[i][block_ptr[i]][j]);
									//	cout<<cmp_str[j]<<' ';
								}
								cnt2++;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					//printf("%d %d\n",cnt1,cnt2);
					for(i=0;i<cnt1;i++)
					{
						for(j=0;j<cnt2;j++)
						{
							file_out<<mainmm_buff1[i][0]<<' '<</*mainmm_buff1[i][1]<<' '<<*/mainmm_buff2[j][0]<<' '<<mainmm_buff2[j][1]<<endl;
						}
					}
					//printf("%d %d\n",cnt1,cnt2);
					// Copy Content of block to file;
					for(i=0;i<R_tuple;i++)
					{
						for(k=0;k<col.size();k++)
						{
							free(mainmm_buff1[i][k]);
						}
						free(mainmm_buff1[i]);
					}
					free(mainmm_buff1);


					for(i=0;i<S_tuple;i++)
					{
						for(k=0;k<col.size();k++)
						{
							free(mainmm_buff2[i][k]);
						}
						free(mainmm_buff2[i]);
					}
					free(mainmm_buff2);
				}
				else if(R_tuple<S_tuple && tuple >= R_tuple)
				{
					//printf("Entered R\n");
					int tmpn;
					tmpn=no_buff*no_record_blk;
					char ***mainmm_buff1=(char ***)malloc(tmpn*sizeof(char**));
					for(i=0;i<tmpn;i++)
					{
						mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}


					int cnt1,cnt2;
					cnt1=0;
					cnt2=0;
					for(i=0;i<R_file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])==0)
							{
								for(j=0;j<R_col.size();j++)
								{
									strcpy(mainmm_buff1[cnt1][j],mainmm_buff[i][block_ptr[i]][j]);
									//	cout<<cmp_str[j]<<' ';
								}
								cnt1++;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					//printf("%d\n",cnt1);

					for(i=R_file_cnt;i<file_cnt;i++)
					{
						//printf("PROBLEM1??\n");
						while(block_fill[i]!=0)
						{
							//printf("PROBLEM2??\n");
							if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][0])==0)
							{
							//	printf("PROBLEMENT??\n");
								for(j=0;j<cnt1;j++)
								{
									file_out<<mainmm_buff1[j][0]<<' '/*<<mainmm_buff1[j][1]*/<<mainmm_buff[i][block_ptr[i]][0]<<' '<<mainmm_buff[i][block_ptr[i]][1] <<endl;
								}
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}
							}
							else
							{
								break;
							}
						}

					}

					//printf("%d\n",cnt1);
					for(i=0;i<tmpn;i++)
					{
						for(k=0;k<R_col.size();k++)
						{
							free(mainmm_buff1[i][k]);
						}
						free(mainmm_buff1[i]);
					}
					free(mainmm_buff1);

				}
				else if(S_tuple<R_tuple && tuple >= S_tuple)
				{

					int tmpn;
					tmpn=no_buff*no_record_blk;
					char ***mainmm_buff2=(char ***)malloc(tmpn*sizeof(char**));
					for(i=0;i<tmpn;i++)
					{
						mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}
					int cnt1,cnt2;
					cnt1=0;
					cnt2=0;
					for(i=R_file_cnt;i<file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(S_min,mainmm_buff[i][block_ptr[i]][0])==0)
							{
								for(j=0;j<S_col.size();j++)
								{
									strcpy(mainmm_buff2[cnt2][j],mainmm_buff[i][block_ptr[i]][j]);
									//	cout<<cmp_str[j]<<' ';
								}
								cnt2++;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					for(i=0;i<R_file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])==0)
							{
								for(j=0;j<cnt2;j++)
								{
									file_out<<mainmm_buff[i][block_ptr[i]][0]<<' '/*<<mainmm_buff[i][block_ptr[i]][1] <<' '*/<<mainmm_buff2[j][0]<<' '<<mainmm_buff2[j][1]<<endl;
								}
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}
							}
							else
								break;
						}

					}
					for(i=0;i<tmpn;i++)
					{
						for(k=0;k<R_col.size();k++)
						{
							free(mainmm_buff2[i][k]);
						}
						free(mainmm_buff2[i]);
					}
					free(mainmm_buff2);

				}
				else if(no_buff>=2)
				{
					//printf("nested join\n");
					string R_Subset("Subset_R_temp");
					string S_Subset("Subset_S_temp");
					char str1[15];
					string tgh1;
					ofstream R_file_out(R_Subset.c_str());
					ofstream S_file_out(S_Subset.c_str());

					for(i=R_file_cnt;i<file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(S_min,mainmm_buff[i][block_ptr[i]][0])==0)
							{
								for(j=0;j<S_col.size()-1;j++)
								{
									S_file_out<<mainmm_buff[i][block_ptr[i]][j]<<' ';
									//strcpy(mainmm_buff2[cnt2][S_block_fill[cnt2]][j],mainmm_buff[i][block_ptr[i]][j]);
								}
								S_file_out<<mainmm_buff[i][block_ptr[i]][j]<<endl;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					S_file_out.close();
					for(i=0;i<R_file_cnt;i++)
					{
						while(block_fill[i]!=0)
						{
							if(strcmp(R_min,mainmm_buff[i][block_ptr[i]][1])==0)
							{
								for(j=0;j<R_col.size()-1;j++)
								{
									R_file_out<<mainmm_buff[i][block_ptr[i]][j]<<' ';
									//strcpy(mainmm_buff1[cnt1][R_block_fill[cnt1]][j],mainmm_buff[i][block_ptr[i]][j]);
									//	cout<<cmp_str[j]<<' ';
								}
								R_file_out<<mainmm_buff[i][block_ptr[i]][j]<<endl;
								block_ptr[i]++;
								if(block_ptr[i]==block_fill[i])
								{
									get_record(i,no_record_blk);
								}

							}
							else
								break;
						}
					}
					R_file_out.close();

					ifstream R_file_in(R_Subset.c_str());

					int tmpn,cnt1,cnt2;
					tmpn=(no_buff*(no_record_blk));
					cnt1;
					char ***mainmm_buff1=(char ***)malloc(tmpn*sizeof(char**));
					for(i=0;i<tmpn;i++)
					{
						mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}



					char ***mainmm_buff2=(char ***)malloc(no_record_blk*sizeof(char**));
					for(i=0;i<no_record_blk;i++)
					{
						mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
						for(k=0;k<R_col.size();k++)
						{
							mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
						}
					}
					//printf("yo hoooo %d\n",tmpn);
					int fltmp;
					fltmp=0;
					while(fltmp!=1)
					{
						string file_line,file_line1;
						int tmp,tmp1;
						if(R_file_in.is_open())
						{
							tmp=0;
							fltmp=1;
							while(getline(R_file_in,file_line))
							{
								stringstream file_line2(file_line);
								string out1;
								tmp1=0;
								fltmp=0;
								while(getline(file_line2,out1,' '))
								{
									strcpy(mainmm_buff1[tmp][tmp1],out1.c_str());
									tmp1++;
									if(tmp1==R_col.size())
										break;
								}
								tmp++;
								if(tmp==tmpn)
								{
									//printf("%d %d\n",tmp,tmpn);
									break;
								}
							}
						}
						else
						{
							cout<<"Cannot open file: metadata.txt"<<endl;
							err=1;chk_exit();
						}
						cnt1=tmp;
						//printf("%d\n",cnt1);
						if(fltmp!=1)
						{
							int fltmp2;
							fltmp2=0;
							ifstream S_file_in(S_Subset.c_str());
							while(fltmp2!=1)
							{
								if(S_file_in.is_open())
								{
									tmp=0;
									fltmp2=1;
									while(getline(S_file_in,file_line))
									{
										stringstream file_line2(file_line);
										string out1;
										tmp1=0;
										fltmp2=0;
										while(getline(file_line2,out1,' '))
										{
											strcpy(mainmm_buff2[tmp][tmp1],out1.c_str());
											tmp1++;
											if(tmp1==R_col.size())
												break;
										}
										tmp++;
										if(tmp==no_record_blk)
										{
											break;
										}
									}
									cnt2=tmp;
								}	
								else
								{
									cout<<"Cannot open file: metadata.txt"<<endl;
									err=1;chk_exit();
								}
								//printf("cnt2:: %d\n cnt1::%d",cnt2,cnt1);
								for(i=0;i<cnt1;i++)
								{
									for(j=0;j<cnt2;j++)
									{
										file_out<<mainmm_buff1[i][0]<<' '/*<<mainmm_buff1[i][1]<<' '*/<<mainmm_buff2[j][0]<<' '<<mainmm_buff2[j][1]<<endl;
									}
								}

							}
							S_file_in.close();

						}
					}
					R_file_in.close();

					for(i=0;i<tmpn;i++)
					{
						for(k=0;k<R_col.size();k++)
						{
							free(mainmm_buff1[i][k]);
						}
						free(mainmm_buff1[i]);
					}
					free(mainmm_buff1);
					for(i=0;i<no_record_blk;i++)
					{
						for(k=0;k<R_col.size();k++)
						{
							free(mainmm_buff2[i][k]);
						}
						free(mainmm_buff2[i]);
					}
					free(mainmm_buff2);

				}
				else
				{
					printf("Cant Be Joined\n");
					return;
				}

			}
		}

	}


	/*
	   while(chk!=1)
	   {
	   rec=-1;
	   for(i=0;i<no_block-1;i++)
	   {
	   if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
	   {
	   rec=i;
	   for(j=0;j<col.size();j++)
	   {
	   strcpy(cmp_str[j],mainmm_buff[i][block_ptr[i]][j]);
	   }
	   break;
	   }
	   }
	   if(rec!=-1)
	   {
	   for(i=rec+1;i<no_block-1;i++)
	   {
	   if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
	   {
	   ret=check_str(i);
	   if(ret>0)
	   {
	   rec=i;
	   for(j=0;j<col.size();j++)
	   {
	   strcpy(cmp_str[j],mainmm_buff[i][block_ptr[i]][j]);
	//	cout<<cmp_str[j]<<' ';
	}
	//	cout<<endl;
	//	cout<<endl;
	}
	}
	}
	}
	for(i=0;i<no_block-1;i++)
	{
	chk=1;
	if(block_fill[i]!=0)
	{
	chk=0;
	break;
	}
	}
	if(chk!=1)
	{
	for(i=0;i<col.size();i++)
	{
	strcpy(mainmm_buff[no_block-1][block_ptr[no_block-1]][i],mainmm_buff[rec][block_ptr[rec]][i]);
	}
	block_ptr[rec]++;
	block_ptr[no_block-1]++;
	if(block_ptr[rec]==block_fill[rec])
	{
	get_record(rec,no_record_blk);
	}
	if(block_ptr[no_block-1]==block_fill[no_block-1])
	{
	for(i=0;i<block_fill[no_block-1];i++)
	{
	for(j=0;j<col.size()-1;j++)
	{
	file_out<<mainmm_buff[no_block-1][i][j]<<' ';
	}
	file_out<<mainmm_buff[no_block-1][i][j]<<endl;
	}
	block_ptr[no_block-1]=0;
	}
	}
	else
	{
		for(i=0;i<block_ptr[no_block-1];i++)
		{
			for(j=0;j<col.size()-1;j++)
			{
				file_out<<mainmm_buff[no_block-1][i][j]<<' ';
			}
			file_out<<mainmm_buff[no_block-1][i][j]<<endl;
		}
		block_ptr[no_block-1]=0;
		file_out.close();
	}

}
*/
free(block_fill);
free(block_ptr);
for(i=0;i<file_cnt;i++)
{
	for(j=0;j<no_record_blk;j++)
	{
		for(k=0;k<col.size();k++)
		{
			free(mainmm_buff[i][j][k]);
		}
		free(mainmm_buff[i][j]);
	}
	free(mainmm_buff[i]);
}
free(mainmm_buff);
//printf("fp2:: :%d \n",file_cnt);
/*
   for(k=0;k<col.size();k++)
   {
   free(cmp_str[k]);
   }
   free(cmp_str);
 */
for(i=0;i<file_cnt;i++)
{
	file_ptr[i].close();
}
delete [] file_ptr;


//printf("fp1:: %d \n",file_cnt);

}

void R_retrieve()
{
	int hashed_val;
	int record_len,i;
	string file_wr("R_temp");
	R_file_cnt=0;
	int col_len=R_col.size();
	record_len=no_record_blk*no_block;
	ifstream file1(R_input_file.c_str());
	string file_line,file_line1;
	int tmp,tmp1;

	R_total_record=0;
	char ****inp;
	int j,k;
	block_fill=(int *)malloc((no_block+1)*sizeof(int));
	block_ptr=(int *)malloc((no_block+1)*sizeof(int));
	inp=(char ****)malloc((no_block+1)*sizeof(char ***));
	
	
	char stra[15];
	string tgha;
	for(i=0;i<no_block;i++)
	{
		sprintf(stra, "%d", i);
		tgha=file_wr+stra;
		ofstream lk(tgha.c_str());
		lk.close();
	}

	for(i=0;i<=no_block;i++)
	{
		block_fill[i]=0;
		block_ptr[i]=0;
		inp[i]=(char ***)malloc(no_record_blk*sizeof(char **));
		for(j=0;j<no_record_blk;j++)
		{
			inp[i][j]=(char **) malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				inp[i][j][k]=(char *)malloc((record_size)*sizeof(char));
			}
		}
	}

	if(file1.is_open())
	{
		tmp=0;
		while(getline(file1,file_line))
		{
			R_total_record++;
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
//			cout<<file_line<<endl;
			//printf("asd\n");
			while(getline(file_line2,out1,' '))
			{
//				cout<<out1<<endl;
				if(tmp1==1)
				{
					R_Y[out1]++;
				}
				//printf("1 %d %d\n",no_block,tmp1);
				strcpy(inp[no_block][0][tmp1],out1.c_str());
				//printf("2\n");
				tmp1++;
			}
			int hashed_val=hash(inp[no_block][0][1],no_block);
			strcpy(inp[hashed_val][block_ptr[hashed_val]][0],inp[no_block][0][0]);
			strcpy(inp[hashed_val][block_ptr[hashed_val]][1],inp[no_block][0][1]);
			block_ptr[hashed_val]++;
			if(block_ptr[hashed_val]==no_record_blk)
			{
				char str[15];
				sprintf(str, "%d", hashed_val);
				string tgh;
				tgh=file_wr+str;
				ofstream filew;
				filew.open(tgh.c_str(),std::ios_base::app);
				for(j=0;j<block_ptr[hashed_val];j++)
				{
					R_hash[hashed_val]++;
					filew<<inp[hashed_val][j][0]<<' '<<inp[hashed_val][j][1]<<endl;
				}
				filew.close();
				block_ptr[hashed_val]=0;
			}
			tmp++;
		}
		for(i=0;i<no_block;i++)
		{
			if(block_ptr[i]!=0)
			{
				char str[15];
				sprintf(str, "%d", i);
				string tgh;
				tgh=file_wr+str;
				ofstream filew;
				filew.open(tgh.c_str(),std::ios_base::app);
				for(j=0;j<block_ptr[i];j++)
				{
					R_hash[i]++;
					filew<<inp[i][j][0]<<' '<<inp[i][j][1]<<endl;
				}
				filew.close();
				block_ptr[i]=0;
			}
		}
		file1.close();
		free(block_fill);
		free(block_ptr);
		for(i=0;i<=no_block;i++)
		{
			for(j=0;j<no_record_blk;j++)
			{
				for(k=0;k<R_col.size();k++)
					free(inp[i][j][k]);
				free(inp[i][j]);
			}
			free(inp[i]);
		}
		free(inp);
	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}


}
void S_retrieve()
{
	int hashed_val;
	int record_len,i;
	string file_wr("S_temp");
	S_file_cnt=0;
	int col_len=S_col.size();
	record_len=no_record_blk*no_block;
	ifstream file1(S_input_file.c_str());
	string file_line,file_line1;
	int tmp,tmp1;

	S_total_record=0;
	char ****inp;
	int j,k;
	block_fill=(int *)malloc((no_block+1)*sizeof(int));
	block_ptr=(int *)malloc((no_block+1)*sizeof(int));
	inp=(char ****)malloc((no_block+1)*sizeof(char ***));


	char stra[15];
	string tgha;
	for(i=0;i<no_block;i++)
	{
		sprintf(stra, "%d", i);
		tgha=file_wr+stra;
		ofstream lk(tgha.c_str());
		lk.close();
	}
	for(i=0;i<=no_block;i++)
	{
		block_fill[i]=0;
		block_ptr[i]=0;
		inp[i]=(char ***)malloc(no_record_blk*sizeof(char **));
		for(j=0;j<no_record_blk;j++)
		{
			inp[i][j]=(char **) malloc((S_col.size())*sizeof(char *));
			for(k=0;k<S_col.size();k++)
			{
				inp[i][j][k]=(char *)malloc((record_size)*sizeof(char));
			}
		}
	}

	if(file1.is_open())
	{
		tmp=0;
		while(getline(file1,file_line))
		{
			S_total_record++;
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			while(getline(file_line2,out1,' '))
			{
				if(tmp1==0)
				{
					S_Y[out1]++;
				}
				strcpy(inp[no_block][0][tmp1],out1.c_str());
				tmp1++;
			}
			int hashed_val=hash(inp[no_block][0][0],no_block);
			strcpy(inp[hashed_val][block_ptr[hashed_val]][0],inp[no_block][0][0]);
			strcpy(inp[hashed_val][block_ptr[hashed_val]][1],inp[no_block][0][1]);
			block_ptr[hashed_val]++;
			if(block_ptr[hashed_val]==no_record_blk)
			{
				char str[15];
				sprintf(str, "%d", hashed_val);
				string tgh;
				tgh=file_wr+str;
				ofstream filew;
				filew.open(tgh.c_str(),std::ios_base::app);
				for(j=0;j<block_ptr[hashed_val];j++)
				{
					S_hash[hashed_val]++;
					filew<<inp[hashed_val][j][0]<<' '<<inp[hashed_val][j][1]<<endl;
				}
				filew.close();
				block_ptr[hashed_val]=0;
			}
			tmp++;
		}
		for(i=0;i<no_block;i++)
		{
			if(block_ptr[i]!=0)
			{
				char str[15];
				sprintf(str, "%d", i);
				string tgh;
				tgh=file_wr+str;
				ofstream filew;
				filew.open(tgh.c_str(),std::ios_base::app);
				for(j=0;j<block_ptr[i];j++)
				{
					S_hash[i]++;
					filew<<inp[i][j][0]<<' '<<inp[i][j][1]<<endl;
				}
				filew.close();
				block_ptr[i]=0;
			}
		}
		file1.close();
		free(block_fill);
		free(block_ptr);
		for(i=0;i<=no_block;i++)
		{
			for(j=0;j<no_record_blk;j++)
			{
				for(k=0;k<S_col.size();k++)
					free(inp[i][j][k]);
				free(inp[i][j]);
			}
			free(inp[i]);
		}
		free(inp);
	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}


}
void hash_join(int i)
{
	int pt=i;
	string file_wr(output_file.c_str());
	string file_wr1("R_temp");
	char str[15];
	sprintf(str, "%d", i);
	string tgh;
	tgh=file_wr1+str;
	ifstream file1(tgh.c_str());
	string file_wr2("S_temp");

	int tmpn,k,j;
	tmpn=(no_block)*no_record_blk;

	char str1[15];
	sprintf(str1, "%d", i);
	string tgh1;
	tgh1=file_wr2+str1;
	ifstream file2(tgh1.c_str());
	ofstream file_out;
//	cout<<output_file<<endl;
	file_out.open(output_file.c_str(),std::ios_base::app);
	int tuple;
	tuple=(no_block)*no_record_blk;
	if(tuple>=R_hash[i]+S_hash[i])
	{
//		printf("1st cond\n");
		//printf("%d\n",cnt1);
		//WHole Tuple fits in MM
		char ***mainmm_buff1=(char ***)malloc(R_hash[pt]*sizeof(char**));
		for(i=0;i<R_hash[pt];i++)
		{
			mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}

		//printf("%d\n",cnt1);
		char ***mainmm_buff2=(char ***)malloc(S_hash[pt]*sizeof(char**));
		for(i=0;i<S_hash[pt];i++)
		{
			mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
		string file_line,file_line1;
		int tmp,tmp1,cnt1,cnt2,fltmp;
		tmp=0;
		fltmp=1;
		while(getline(file1,file_line))
		{
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			fltmp=0;
			while(getline(file_line2,out1,' '))
			{
				strcpy(mainmm_buff1[tmp][tmp1],out1.c_str());
				tmp1++;
				if(tmp1==R_col.size())
					break;
			}
			tmp++;
			if(tmp==R_hash[pt])
			{
//				printf("file1: %d %d\n",tmp,tmpn);
				break;
			}
		}
		map<string ,int>mapper;
		cnt1=tmp;
		//printf("file1:: %d\n",cnt1);
		qsort(mainmm_buff1,cnt1,sizeof(mainmm_buff1[0]),R_cmp);
		//printf("Start map\n");
		for(i=0;i<cnt1;i++)
		{
		//	cout<<mainmm_buff1[i][0]<<' '<<mainmm_buff1[i][1]<<endl;
			if(mapper.find(mainmm_buff1[i][1])==mapper.end())
			{
				mapper[mainmm_buff1[i][1]]=i;
			}
			else
			{
			}
		}
		tmp=0;
		fltmp=1;
		while(getline(file2,file_line))
		{
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			fltmp=0;
			while(getline(file_line2,out1,' '))
			{
				strcpy(mainmm_buff2[tmp][tmp1],out1.c_str());
				tmp1++;
				if(tmp1==R_col.size())
						break;
			}
			tmp++;
			if(tmp==S_hash[pt])
			{
				//printf("S::: %d %d\n",tmp,tmpn);
				break;
			}
		}
		cnt2=tmp;
		int len;
		if(fltmp!=1)
		{
			for(i=0;i<cnt2;i++)
			{
				if(R_Y[mainmm_buff2[i][0]]!=0)	//Y is in col0 in S
				{
					len=mapper[mainmm_buff2[i][0]]+R_Y[mainmm_buff2[i][0]];
				//	printf("st::%d end::%d len::%d\n",mapper[mainmm_buff2[i][0]],len,R_Y[mainmm_buff2[i][0]]);
					for(j=mapper[mainmm_buff2[i][0]];j<len;j++)
					{
						//		cout<<mainmm_buff1[j][0]<<' '<<mainmm_buff1[j][1]<<' '<<mainmm_buff2[i][0]<<' '<<mainmm_buff2[i][1]<<endl;
						file_out<<mainmm_buff1[j][0]<<' '/*<<mainmm_buff1[j][1]<<' '*/<<mainmm_buff2[i][0]<<' '<<mainmm_buff2[i][1]<<endl;
					}
				}
			}
		}
		for(i=0;i<R_hash[pt];i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff1[i][k]);
			}
			free(mainmm_buff1[i]);
		}
		free(mainmm_buff1);

		//printf("%d\n",cnt1);
		for(i=0;i<S_hash[pt];i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff2[i][k]);
			}
			free(mainmm_buff2[i]);
		}
		free(mainmm_buff2);
	
	}
	else if(R_hash[i]<S_hash[i] && R_hash[i]<=tmpn)
	{
	//	printf("ENtered 1\n");
		char ***mainmm_buff1=(char ***)malloc(tmpn*sizeof(char**));
		for(i=0;i<tmpn;i++)
		{
			mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}

		char ***mainmm_buff2=(char ***)malloc(no_record_blk*sizeof(char**));
		for(i=0;i<no_record_blk;i++)
		{
			mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
		string file_line,file_line1;
		int tmp,tmp1,cnt1,cnt2,fltmp;
		if(file1.is_open())
		{
			tmp=0;
			fltmp=1;
			while(getline(file1,file_line))
			{
				stringstream file_line2(file_line);
				string out1;
				tmp1=0;
				fltmp=0;
				while(getline(file_line2,out1,' '))
				{
					strcpy(mainmm_buff1[tmp][tmp1],out1.c_str());
					tmp1++;
					if(tmp1==R_col.size())
						break;
				}
				tmp++;
				if(tmp==tmpn)
				{
	//				printf("file1: %d %d\n",tmp,tmpn);
					break;
				}
			}
			map<string ,int>mapper;
			cnt1=tmp;
			//printf("file1:: %d\n",cnt1);
			qsort(mainmm_buff1,cnt1,sizeof(mainmm_buff1[0]),R_cmp);
			//printf("Start map\n");
			for(i=0;i<cnt1;i++)
			{
			//	cout<<mainmm_buff1[i][0]<<' '<<mainmm_buff1[i][1]<<endl;
				if(mapper.find(mainmm_buff1[i][1])==mapper.end())
				{
					mapper[mainmm_buff1[i][1]]=i;
				}
				else
				{
				}
			}
		//	printf("End map\n");
			fltmp=0;
			while(fltmp!=1)
			{
				tmp=0;
				fltmp=1;
				while(getline(file2,file_line))
				{
					stringstream file_line2(file_line);
					string out1;
					tmp1=0;
					fltmp=0;
					while(getline(file_line2,out1,' '))
					{
						strcpy(mainmm_buff2[tmp][tmp1],out1.c_str());
						tmp1++;
						if(tmp1==R_col.size())
							break;
					}
					tmp++;
					if(tmp==no_record_blk)
					{
						//printf("S::: %d %d\n",tmp,tmpn);
						break;
					}
				}
				cnt2=tmp;
				int len;
				if(fltmp!=1)
				{
					for(i=0;i<cnt2;i++)
					{
						if(R_Y[mainmm_buff2[i][0]]!=0)	//Y is in col0 in S
						{
							len=mapper[mainmm_buff2[i][0]]+R_Y[mainmm_buff2[i][0]];
						//	printf("st::%d end::%d len::%d\n",mapper[mainmm_buff2[i][0]],len,R_Y[mainmm_buff2[i][0]]);
							for(j=mapper[mainmm_buff2[i][0]];j<len;j++)
							{
						//		cout<<mainmm_buff1[j][0]<<' '<<mainmm_buff1[j][1]<<' '<<mainmm_buff2[i][0]<<' '<<mainmm_buff2[i][1]<<endl;
								file_out<<mainmm_buff1[j][0]<<' '/*<<mainmm_buff1[j][1]<<' '*/<<mainmm_buff2[i][0]<<' '<<mainmm_buff2[i][1]<<endl;
							}
						}
					}
				}

			}
			file_out.close();
			file1.close();
			file2.close();
		}
		else
		{
			cout<<"Cannot open file: metadata.txt"<<endl;
			return;
		//	err=1;chk_exit();
		}
		for(i=0;i<tmpn;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff1[i][k]);
			}
			free(mainmm_buff1[i]);
		}
		free(mainmm_buff1);

		for(i=0;i<no_record_blk;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff2[i][k]);
			}
			free(mainmm_buff2[i]);
		}
		free(mainmm_buff2);
		

		//printf("%d\n",cnt1);				

	}
	else if(S_hash[i]<R_hash[i] && S_hash[i]<=tmpn)
	{
	//	printf("ENtered 2\n");
		char ***mainmm_buff2=(char ***)malloc(tmpn*sizeof(char**));
		for(i=0;i<tmpn;i++)
		{
			mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}

		char ***mainmm_buff1=(char ***)malloc(no_record_blk*sizeof(char**));
		for(i=0;i<no_record_blk;i++)
		{
			mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
		string file_line,file_line1;
		int tmp,tmp1,cnt1,cnt2,fltmp;
		if(file2.is_open())
		{
			tmp=0;
			fltmp=1;
			while(getline(file2,file_line))
			{
				stringstream file_line2(file_line);
				string out1;
				tmp1=0;
				fltmp=0;
				while(getline(file_line2,out1,' '))
				{
					strcpy(mainmm_buff2[tmp][tmp1],out1.c_str());
					tmp1++;
					if(tmp1==R_col.size())
						break;
				}
				tmp++;
				if(tmp==tmpn)
				{
//					printf("%d %d\n",tmp,tmpn);
					break;
				}
			}
			map<string ,int>mapper;
			cnt2=tmp;
			qsort(mainmm_buff2,cnt2,sizeof(mainmm_buff2[0]),S_cmp);
			for(i=0;i<cnt2;i++)
			{
				if(mapper.find(mainmm_buff2[i][0])==mapper.end())
				{
					mapper[mainmm_buff2[i][0]]=i;
				}
				else
				{
				}
			}
			fltmp=0;
			while(fltmp!=1)
			{
				tmp=0;
				fltmp=1;
				while(getline(file1,file_line))
				{
					stringstream file_line2(file_line);
					string out1;
					tmp1=0;
					fltmp=0;
					while(getline(file_line2,out1,' '))
					{
						strcpy(mainmm_buff1[tmp][tmp1],out1.c_str());
						tmp1++;
						if(tmp1==R_col.size())
							break;
					}
					tmp++;
					if(tmp==no_record_blk)
					{
				//		printf("%d %d\n",tmp,tmpn);
						break;
					}
				}
				cnt1=tmp;
				int len;
				if(fltmp!=1)
				{
					for(i=0;i<cnt1;i++)
					{
						if(S_Y[mainmm_buff1[i][1]]!=0)	//Y is in col1 in R
						{
							len=mapper[mainmm_buff1[i][1]]+S_Y[mainmm_buff1[i][1]];
							for(j=mapper[mainmm_buff1[i][1]];j<len;j++)
							{
								file_out<<mainmm_buff1[i][0]<<' '/*<<mainmm_buff1[i][1]<<' '*/<<mainmm_buff2[j][0]<<' '<<mainmm_buff2[j][1]<<endl;
							}
						}
					}
				}

			}
			file_out.close();
			file1.close();
			file2.close();
		}
		else
		{
			cout<<"Cannot open file: metadata.txt"<<endl;
		//	err=1;chk_exit();
			return;
		}
		for(i=0;i<tmpn;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff2[i][k]);
			}
			free(mainmm_buff2[i]);
		}
		free(mainmm_buff2);

		for(i=0;i<no_record_blk;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff1[i][k]);
			}
			free(mainmm_buff1[i]);
		}
		free(mainmm_buff1);
		//printf("%d\n",cnt1);				

	}
	else if(no_block>=2)
	{
	//	printf("ENtered 3\n");

		//NESTED LOOP JOIN
		file1.close();
		file2.close();
		char str1[15];

		ifstream R_file_in(tgh.c_str());

		int tmpn,cnt1,cnt2;
		tmpn=(no_block*(no_record_blk));
		cnt1;
		char ***mainmm_buff1=(char ***)malloc(tmpn*sizeof(char**));
		for(i=0;i<tmpn;i++)
		{
			mainmm_buff1[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff1[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}



		char ***mainmm_buff2=(char ***)malloc(no_record_blk*sizeof(char**));
		for(i=0;i<no_record_blk;i++)
		{
			mainmm_buff2[i]=(char **)malloc((R_col.size())*sizeof(char *));
			for(k=0;k<R_col.size();k++)
			{
				mainmm_buff2[i][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
//		printf("yo hoooo %d\n",tmpn);
		int fltmp;
		fltmp=0;
		while(fltmp!=1)
		{
			string file_line,file_line1;
			int tmp,tmp1;
			if(R_file_in.is_open())
			{
				tmp=0;
				fltmp=1;
				while(getline(R_file_in,file_line))
				{
					stringstream file_line2(file_line);
					string out1;
					tmp1=0;
					fltmp=0;
					while(getline(file_line2,out1,' '))
					{
						strcpy(mainmm_buff1[tmp][tmp1],out1.c_str());
						tmp1++;
						if(tmp1==R_col.size())
							break;
					}
					tmp++;
					if(tmp==tmpn)
					{
				//		printf("%d %d\n",tmp,tmpn);
						break;
					}
				}
			}
			else
			{
				cout<<"Cannot open file: metadata.txt"<<endl;
				//err=1;chk_exit();
				return;
			}
			cnt1=tmp;
//			printf("%d\n",cnt1);
			if(fltmp!=1)
			{
				int fltmp2;
				fltmp2=0;
				ifstream S_file_in(tgh1.c_str());
				while(fltmp2!=1)
				{
					if(S_file_in.is_open())
					{
						tmp=0;
						fltmp2=1;
						while(getline(S_file_in,file_line))
						{
							stringstream file_line2(file_line);
							string out1;
							tmp1=0;
							fltmp2=0;
							while(getline(file_line2,out1,' '))
							{
								strcpy(mainmm_buff2[tmp][tmp1],out1.c_str());
								tmp1++;
								if(tmp1==R_col.size())
									break;
							}
							tmp++;
							if(tmp==no_record_blk)
							{
								break;
							}
						}
						cnt2=tmp;
					}	
					else
					{
						cout<<"Cannot open file: metadata.txt"<<endl;
						//err=1;chk_exit();
						return;
					}
			//		if(file_out.is_open())
			//			printf("Open Out file\n");
//					printf("cnt2:: %d\n cnt1::%d",cnt2,cnt1);
					for(i=0;i<cnt1;i++)
					{
						for(j=0;j<cnt2;j++)
						{
			//				printf("%s %s\n",mainmm_buff1[i][1],mainmm_buff2[j][0]);
							if(strcmp(mainmm_buff1[i][1],mainmm_buff2[j][0])==0)
							{
								file_out<<mainmm_buff1[i][0]<<' '/*<<mainmm_buff1[i][1]<<' '*/<<mainmm_buff2[j][0]<<' '<<mainmm_buff2[j][1]<<endl;
			//				printf("printed to file\n");
							}
						}
					}

				}
				S_file_in.close();

			}
		}
		R_file_in.close();
		file_out.close();
		for(i=0;i<tmpn;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff1[i][k]);
			}
			free(mainmm_buff1[i]);
		}
		free(mainmm_buff1);
		for(i=0;i<no_record_blk;i++)
		{
			for(k=0;k<R_col.size();k++)
			{
				free(mainmm_buff2[i][k]);
			}
			free(mainmm_buff2[i]);
		}
		free(mainmm_buff2);

	}
	else
	{
		printf("Cant Be Joined\n");
		return;

	}

}
void sort_open()
{
		R_sort_input();

		S_sort_input();
}
void sort_getnext()
{
		merge_sort();
}
void hash_open()
{
		R_retrieve();
		S_retrieve();
}
void hash_getnext()
{
	int i;
		for(i=0;i<no_block;i++)
		{
			if(S_hash[i]!=0 && R_hash[i]!=0)
				hash_join(i);
		}
}
int main(int argc, char * argv[])
{
	int i;
	R_input_file=argv[1];
	S_input_file=argv[2];
	string h1,h2;
	h1=SplitFilename(R_input_file);
	h2=SplitFilename(S_input_file);
	output_file=h1+"_"+h2+"_join";
	type=argv[3];
	//	main_mem_size=atoi(argv[3]);
	no_block=atoi(argv[4]);
	//no_record_blk=100;
	no_record_blk=100;
	R_col.push_back("X");
	R_col.push_back("Y");
	S_col.push_back("Y");
	S_col.push_back("Z");

	R_col_mapper["X"]=0;
	R_col_mapper["Y"]=1;

	S_col_mapper["Y"]=0;
	S_col_mapper["Z"]=1;
	record_size=30;
	if(strcmp((type.c_str()),"hash")==0)
	{
//		printf("hash\n");
		R_hash=(int *)malloc((no_block)*sizeof(int));
		S_hash=(int *)malloc((no_block)*sizeof(int));
		for(i=0;i<no_block;i++)
		{
			R_hash[i]=0;
			S_hash[i]=0;
		}
	
		hash_open();
		ofstream lk(output_file.c_str());
		lk.close();
		hash_getnext();
	}
	else
	{
//		printf("sort\n");
	
	   sort_flag=1;
	   R_sort_col.push_back("Y");
	   S_sort_col.push_back("Y");




	//extract();

	   	sort_open();
		if(R_file_cnt+S_file_cnt > no_block)
		{
			printf("CAN't Fit Sorted Sublist in MM");
			return 0;
		}
	//	sort_input();
	//	calculate_block_size();
	//	printf("%d %d %d\n",(main_mem_size*1000000),block_size,record_size);
		sort_getnext();
	 
	}
	return 0;
}
