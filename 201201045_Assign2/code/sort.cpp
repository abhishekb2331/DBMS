#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
string input_file;
string output_file;
int sort_flag;
vector<string> sort_col;
vector<string>col;
vector<int>col_size;
int main_mem_size;
int record_size;
int block_size;
int no_block;  //no of  block in mm;
int no_record_blk;
int total_record; //total no. of record
int err;
int file_cnt;
map<string ,int>col_mapper;
ifstream *file_ptr; 
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
void calculate_block_size()
{
	/*
	string r="wc "+ input_file + " > no.lines";
	system(r.c_str()); 
	FILE *pfile = fopen("no.lines", "r");
	int lines; 
	fscanf(pfile, "%d", &lines); 
	system("rm no.lines");
	//	cout<<lines<<endl;
	total_record=lines+1;
	*/
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
	no_record_blk=bl_size/record_size;
	//	cout<<no_record_blk<<endl;
	return;
}
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
		/*		
				int i;
				cout<<col.size()<<' '<<col_size.size()<<endl;
				for(i=0;i<col.size();i++)
				{
				cout<<col[i]<<' '<<col_size[i]<<endl;
				}
		 */		
	}
	else
	{
		cout<<"Cannot open file: metadata.txt"<<endl;
		err=1;chk_exit();
	}

}
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
void sort_input()
{
	int record_len,i;
	//	char file_wr[15] ="temp";
	string file_wr("temp");
	file_cnt=0;
	int col_len=col.size();
	record_len=((main_mem_size*800000)/record_size)/col_len;
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
	ifstream file1(input_file.c_str());
	string file_line,file_line1;
	int tmp,tmp1;


	total_record=0;
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
			total_record++;
			stringstream file_line2(file_line);
			string out1;
			tmp1=0;
			while(getline(file_line2,out1,' '))
			{
				//				cout<<inp[0][0]<<endl;
				//			char *t=(char *)out1.c_str();
				//			cout<<t<<endl;
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
				sprintf(str, "%d", file_cnt);
				qsort(inp,tmp,sizeof(inp[0]),cmp);
				string tgh;
				tgh=file_wr+str;
				ofstream filew(tgh.c_str());
				file_cnt++;
				for(i=0;i<tmp;i++)
				{
					for(j=0;j<col.size()-1;j++)
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
			sprintf(str, "%d", file_cnt);
			qsort(inp,tmp,sizeof(inp[0]),cmp);
			string tgh;
			tgh=file_wr+str;
			ofstream filew(tgh.c_str());
			file_cnt++;
			for(i=0;i<tmp;i++)
			{
				for(j=0;j<col.size()-1;j++)
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
	//	mainmm_buff[i][col.size()][record_size];
	string file_line,file_line1;
	int tmp,tmp1;
	//	cout<<file_ptr[i]<<' '<<i<<endl;
	if(file_ptr[i].is_open())
	{
		tmp=0;
		while(getline(file_ptr[i],file_line))
		{
		//	cout<<"entered"<<endl;
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
			//			cout<<"end"<< inp[0][0]<<endl;
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
	string file_wr("temp");
	char str[15];
	string tgh;
	ofstream file_out(output_file.c_str());
	//	ifstream *file_ptr;
	//	file_ptr=(ifstream *)malloc(file_cnt*sizeof(ifstream));
	file_ptr=new ifstream[file_cnt];
	//	ifstream fl[100];
	int i,j,k;
	//	cout<<file_ptr[0]<<' '<<fl[0]<<endl;
	for(i=0;i<file_cnt;i++)
	{
		sprintf(str, "%d",i);
		tgh=file_wr+str;
	//	cout<<tgh<<' '<<i<<endl;
		//	ifstream filer(tgh.c_str());
		file_ptr[i].open(tgh.c_str());
	//	cout<<file_ptr[i]<<endl;
	//	cout<<tgh<<endl;
		//		fl[i]=filer;
		//		file_ptrs.push_back(filer);
	}
	//	no_block=file_cnt+1;
	//	no_record_blk=2;
	block_fill=(int *)malloc(no_block*sizeof(int));
	block_ptr=(int *)malloc(no_block*sizeof(int));
	mainmm_buff=(char ****)malloc(no_block*sizeof(char ***));
	for(i=0;i<no_block;i++)
	{
		block_fill[i]=0;
		block_ptr[i]=0;
		mainmm_buff[i]=(char ***)malloc(no_record_blk*sizeof(char **));
		for(j=0;j<no_record_blk;j++)
		{
			mainmm_buff[i][j]=(char **)malloc((col.size())*sizeof(char *));
			for(k=0;k<col.size();k++)
			{
				mainmm_buff[i][j][k]=(char *)malloc(record_size*sizeof(char));
			}
		}
	}
	cmp_str=(char **)malloc((col.size())*sizeof(char *));
	for(k=0;k<col.size();k++)
	{
		cmp_str[k]=(char *)malloc(record_size*sizeof(char));
	}
	/*	string file_wr("temp");
		char str[15];
		string tgh;
	 */
	for(i=0;i<file_cnt;i++)
	{
		//	sprintf(str, "%d",i);
		//	tgh=file_wr+str;
		get_record(i,no_record_blk);
	}
/*
	for(i=0;i<no_block-1;i++)
	{
		for(j=0;j<no_record_blk;j++)
		{
			for(k=0;k<col.size();k++)
			{
				printf("%s ",mainmm_buff[i][j][k]);
			}
			cout<<endl;
		}
	}
*/
	block_fill[no_block-1]=no_record_blk;
	int chk,rec,ret;
	chk=0;
	while(chk!=1)
	{
	//	cout<<endl<<"start"<<endl;
		rec=-1;
		for(i=0;i<no_block-1;i++)
		{
			if(block_fill[i]!=0 && block_ptr[i]!=block_fill[i])
			{
				rec=i;
				for(j=0;j<col.size();j++)
				{
					strcpy(cmp_str[j],mainmm_buff[i][block_ptr[i]][j]);
			//		cout<<cmp_str[j]<<' ';
				}
			//	cout<<endl;
			//	cout<<endl;
				break;
			}
		}
		if(rec!=-1)
		{
			//cout<<"testing"<<endl;
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
//					file_out<<endl;
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
//				file_out<<endl;
			}
			block_ptr[no_block-1]=0;
			file_out.close();
		}

	}

	free(block_fill);
	free(block_ptr);
	for(i=0;i<no_block;i++)
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
	for(k=0;k<col.size();k++)
	{
		free(cmp_str[k]);
	}
	free(cmp_str);

	for(i=0;i<file_cnt;i++)
	{
		file_ptr[i].close();
	}
	delete [] file_ptr;



}
int main(int argc, char * argv[])
{
	int i;
	input_file=argv[1];
	output_file=argv[2];
	main_mem_size=atoi(argv[3]);
	//cout<<argv[4]<<endl;
	if(strcmp(argv[4],"asc")==0)
	{
		sort_flag=1;
	}
	else
	{
		sort_flag=2;
	}
	for(i=5;i<argc;i++)
	{
		sort_col.push_back(argv[i]);
		//		printf("%s\n",argv[i]);
	}
	//cout<<input_file<<endl;
	//cout<<output_file<<endl;
	//printf("%d %d ",main_mem_size,sort_flag);
	/*for(i=0;i<sort_col.size();i++)
	{
		cout<<sort_col[i]<<endl;
		//		printf("%s ",sort_col[i]);
	}*/
//	printf("\n");

	extract();
/*	for(i=0;i<sort_col.size();i++)
	{
		cout<<col_mapper[sort_col[i]]<<"endel"<<endl;
	}
*/
	sort_input();
	// extract_file();
	calculate_block_size();
	printf("%d %d %d\n",(main_mem_size*1000000),block_size,record_size);
	merge_sort();
	return 0;
}
