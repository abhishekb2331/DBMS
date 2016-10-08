#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <bits/stdc++.h>
using namespace std;
/*
   typedef struct table{
   string table_name;
   vec1tor<string> field_names;
   }tables;
   typedef struct data{
   string table_name;
   vector<vector<int> data;
   }data;*/

vector<pair<string,vector<int> > > a_f_int;

int df;

vector<pair<string,vector<float> > > a_f_fl;

int dc;
vector<string> que1,que2;  
map<string,vector<string> > table_field;	
map<string,vector<vector<int> > > table_dt;	
vector<vector<int> > join_data;			
vector<string> join_table;			
vector<vector<int> > join_data_fin;		
vector<vector<string> > selcol;			
vector<string> selcond;				
vector<string> metadata;                        
int err;


string str_and("AND");
string str_whr("WHERE");
string str_or("OR");
string str_none("NONE");
string str_ne("NOT_EQUAL");
string str_l("LESS");
string str_eq("EQUAL");
string str_le("LESS_EQUAL");
string str_ge("GREATER_EQUAL");
string str_g("GREATER");
string beg_tbl("<begin_table>");
string end_tbl("<end_table>");
string frm("FROM");
string sel("SELECT");
string dist("DISTINCT");
string mn("MIN");
string av("AVG");
string mx("MAX");
string sm("SUM");
string t__1("tempo");



void chk_exit();
char * ret_query(char *s);
void query_f();
void join_get_meta();
void join();
void filenames();
void extract_table();
void extract_data(string filename);
void check_sel();
void parse(string input, char delimitor);
string space_remove(string str);
bool checknum(string str);
void seldata();
int cmpte(string str);
void cmp(string s,int a);
bool cmpstr(string s1,string s2);


/*int data[50][50][10000];
  int table[50];
  int field[50];
  int que[50];
  int map_field_table[2500];
 */



int main(int argv, char * argc[])
{
	char *str;
	//printf("%d %s\n",argv,argc[1]);
	char del=' ';
	extract_table();
	filenames();
	str=ret_query(argc[1]);
	parse(str,del);
//	printf("qw0\n");
	query_f();
//	cout<<selcol.size()<<endl;
//	printf("qw1\n");
	chk_exit();
//	printf("qw_2\n");
	join_get_meta();
//	printf("qw2\n");
	chk_exit();
//	printf("qw3\n");
	check_sel();
	chk_exit();
	return 0;
}


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
int cmpte(string str)
{	
	int find_pos,str_pt,end_pt,ptr=-1;
	string str2 (".");
	find_pos=str.find(str2);
	if(find_pos==-1)
	{
		cmp(t__1,10);
		for(int j=0;j<metadata.size();j++)
		{
			str_pt=metadata[j].find(".")+1;
			end_pt=metadata[j].size()-metadata[j].find(".")-1;
			if(metadata[j].substr(str_pt,end_pt)!=str)
			{
				continue;
			}
			else
			{
				ptr=j;
				return ptr;
			}
		}
		cmp(t__1,10);
		printf("Error\n");
		exit(0);
	}
	else
	{
		cmp(t__1,10);
		for(int j=0;j<metadata.size();j++)
		{
			if(metadata[j]!=str)
			{
				continue;
			}
			else
			{
				ptr=j;
				return ptr;
			}
		}
		cmp(t__1,10);
		printf("Error\n");
		exit(0);
	}
}


void seldata()
{
//	printf("entered\n");
	int len,fl;
	int mxmum,mnmum;
	vector<int>get_val;
	string tmp;
	len=selcol.size();
//	cout<<len<<endl;
	cmp(t__1,10);
	for(int j=0;j<len;j++)
	{
		tmp.clear();
		if(selcol[j][1]!=str_none)
		{
			tmp=selcol[j][1]+"." +selcol[j][2];
		}
		else
		{
			tmp=selcol[j][2];
		}
		cmp(t__1,30);
		if(selcol[j][0]==mx)
		{
			mxmum=INT_MIN;
			fl=cmpte(tmp);
			tmp=metadata[fl];
			cmp(t__1,30);
			for(int j=0;j<join_data_fin.size();j++)
			{
				get_val.push_back(join_data_fin[j][fl]);	
			}
			cmp(t__1,30);		
			for(int l=0;l<get_val.size();l++)
			{
				if(mxmum>=get_val[l])
				{
					continue;
				}
				else
				{
					mxmum=get_val[l];
				}
			}
			get_val.clear();
			get_val.push_back(mxmum);
			tmp="max("+tmp+")";
			a_f_int.push_back(make_pair(tmp,get_val));
			get_val.clear();
		}
		else if(selcol[j][0]=="MIN")
		{
			mnmum=INT_MAX;
			fl=cmpte(tmp);
			tmp=metadata[fl];
			cmp(t__1,30);
			for(int j=0;j<join_data_fin.size();j++)
			{
				get_val.push_back(join_data_fin[j][fl]);	
			}
			cmp(t__1,30);			
			for(int l=0;l<get_val.size();l++)
			{
				if(mnmum<=get_val[l])
				{
					continue;
				}
				else
				{
					mnmum=get_val[l];
				}
			}
			get_val.clear();
			get_val.push_back(mnmum);
			tmp="min("+tmp+")";
			a_f_int.push_back(make_pair(tmp,get_val));
			get_val.clear();
		}
		else if(selcol[j][0]==dist || df==1)
		{
			if(dc!=0)
			{
				cmp(t__1,30);
				fl=cmpte(tmp);
				tmp=metadata[fl];
				for(int j=0;j<join_data_fin.size();j++)
				{
					get_val.push_back(join_data_fin[j][fl]);	
				}
				tmp="distinct("+tmp+")";
				a_f_int.push_back(make_pair(tmp,get_val));
				get_val.clear();

			
				
			}
			else
			{
				cmp(t__1,30);
				fl=cmpte(tmp);
				tmp=metadata[fl];
				for(int j=0;j<join_data_fin.size();j++)
				{
					get_val.push_back(join_data_fin[j][fl]);	
				}
				a_f_int.push_back(make_pair(tmp,get_val));
				get_val.clear();
				
			}
		}
		else if(selcol[j][0]=="SUM")
		{
			cmp(t__1,30);
			int final_sum=0;
			fl=cmpte(tmp);
			tmp=metadata[fl];
			for(int j=0;j<join_data_fin.size();j++)
			{
				get_val.push_back(join_data_fin[j][fl]);	
			}
			cmp(t__1,30);			
			for(int l=0;l<get_val.size();l++)
			{
				final_sum+=get_val[l];
			}
			get_val.clear();
			get_val.push_back(final_sum);
			tmp="sum("+tmp+")";
			a_f_int.push_back(make_pair(tmp,get_val));
			get_val.clear();
		}
		else if(selcol[j][0]=="AVG")
		{
			cmp(t__1,30);
			vector<float> get_val1;
			fl=cmpte(tmp);
			tmp=metadata[fl];
			for(int j=0;j<join_data_fin.size();j++)
			{
				get_val1.push_back(join_data_fin[j][fl]);	
			}
			cmp(t__1,30);
			float final_sum=0;
			for(int l=0;l<get_val1.size();l++)
			{
				final_sum+=get_val1[l];
			}
			final_sum=final_sum/get_val1.size();
			get_val1.clear();
			get_val1.push_back(final_sum);
			tmp="avg("+tmp+")";
			a_f_fl.push_back(make_pair(tmp,get_val1));
			get_val.clear();
		}
		else if(selcol[j][0]=="NONE")
		{
			if(selcol[j][2]=="ALL")
			{
				cmp(t__1,30);
				for(int j=0;j<metadata.size();j++)
				{
					cmp(t__1,30);
					tmp=metadata[j];
					for(int l=0;l<join_data_fin.size();l++)
					{
						get_val.push_back(join_data_fin[l][j]);	
					}
					a_f_int.push_back(make_pair(tmp,get_val));
					get_val.clear();
				}
			}
			else
			{
				cmp(t__1,30);
				fl=cmpte(tmp);
				tmp=metadata[fl];
				for(int j=0;j<join_data_fin.size();j++)
				{
					get_val.push_back(join_data_fin[j][fl]);	
				}
				a_f_int.push_back(make_pair(tmp,get_val));
				get_val.clear();
			}
		}
		
	}
	if(!a_f_fl.empty())
	{
		for(int i=0;i<(a_f_fl.size()-1);i++)
		{
			cout<<a_f_fl[i].first<<",";
		}
		cmp(t__1,30);
		cout<<a_f_fl[a_f_fl.size()-1].first<<"\n";
			for(int h=0;h<a_f_fl[0].second.size();h++)
			{
				cmp(t__1,30);
				for(int j=0;j<(a_f_fl.size()-1);j++)
				{
					printf("%.4f,",(a_f_fl[j].second)[h]);
				}
				printf("%.4f\n",(a_f_fl[a_f_fl.size()-1].second)[h]);
			}
	}
	else if(!a_f_int.empty())
	{
		set<vector<int> > smt;
		vector<int> st;
		cmp(t__1,30);
		for(int i=0;i<(a_f_int.size()-1);i++)
		{
			cout<<a_f_int[i].first<<",";
		}
		cout<<a_f_int[a_f_int.size()-1].first<<"\n";
	cmp(t__1,30);		
		if(!a_f_int.empty() && df==0)
		{
			cmp(t__1,30);
			for(int i=0;i<a_f_int[0].second.size();i++)
			{
				for(int j=0;j<(a_f_int.size()-1);j++)
				{
					cout<<(a_f_int[j].second)[i]<<",";
				}
				cout<<(a_f_int[a_f_int.size()-1].second)[i]<<"\n";
			}
			cmp(t__1,30);
		}
		else if(!a_f_int.empty() && df==1)
		{
			cmp(t__1,30);
			set<vector<int> >::iterator iter;
			for(int i=0;i<a_f_int[0].second.size();i++)
			{
				cmp(t__1,30);
				st.clear();
				for(int j=0;j<(a_f_int.size());j++)
				{
					st.push_back((a_f_int[j].second)[i]);
				}
				smt.insert(st);
			}
			iter=smt.begin();
			cmp(t__1,30);
			while(iter!=smt.end())
			{
				for(int i=0;i<(*iter).size()-1;i++)
				{
					cout<<(*iter)[i]<<",";
				}
				cout<<(*iter)[(*iter).size()-1]<<"\n";
				iter++;
			}
			cmp(t__1,30);
		}
	}
	cmp(t__1,10);
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

void parse(string input, char delimitor)
{
	stringstream input_stream(input);
	string output1;
	vector <string > tokens;
	vector<string> tokens2;
	int pointer__1=-1,pointer__2=-1,pointer__3=-1;
	cmp(t__1,10);
	while(getline(input_stream,output1,delimitor))
	{
		if(output1.find(',')==-1)
		{
			tokens.push_back(output1);
		}
		else
		{
			stringstream input_new(output1);
			string output2;
			while(getline(input_new,output2,','))
			{
				tokens.push_back(output2);
			}
		}
	}
	cmp(t__1,10);
	int len=tokens.size(),iter;
	string tmp1,tmp2;
	cmp(t__1,10);
	for(iter=0;iter<len;iter++)
	{
		que1.push_back(tokens[iter]);
//		cout<<tokens[iter]<<endl;
	}
	cmp(t__1,10);
	len=que1.size();
	for(int i=0;i<len;i++)
	{
		if(cmpstr(que1[i],str_and) || cmpstr(que1[i],str_or))
		{
			pointer__2=i;
		}
		else if(cmpstr(que1[i],str_whr))
		{
			pointer__1=i;
		}
	}
	cmp(t__1,10);
	pointer__3=len;
	if(pointer__1!=-1)
	{
		if(pointer__2!=-1)
		{
			cmp(t__1,10);
			for(int i=pointer__1+1;i<pointer__2;i++)
			{
				tmp1=tmp1+que1[i];
			}
			tokens2.push_back(tmp1);
			tokens2.push_back(que1[pointer__2]);
			tmp1.clear();
			for(int i =pointer__2+1;i<pointer__3;i++)
			{
				tmp1=tmp1+que1[i];
			}
			tokens2.push_back(tmp1);
			for(int i=pointer__1+1;i<pointer__3;i++)
			{
				que1.erase(que1.begin()+i);
			}


			cmp(t__1,10);
		}
		else
		{
			cmp(t__1,10);
	
			for(int i=pointer__1+1;i<pointer__3;i++)
			{
				tmp1=tmp1+que1[i];
			}
			tokens2.push_back(tmp1);
			for(int i=pointer__1+1;i<pointer__3;i++)
			{
				que1.erase(que1.begin()+i);
			}
			cmp(t__1,10);
		}
	}
	else if(pointer__1==-1)
	{
		return;
	}
	for(int i=0;i<tokens2.size();i++)
	{
		que1.push_back(tokens2[i]);
	}
}




void check_sel()
{
//	printf("check_sel\n");
	int fl,i,j,k;
	fl=i=j=k=0;
//	cout<<selcond.size()<<endl;
	for(i=0;i<selcond.size();i++)
	{
//		cout<<selcond[i]<<endl;
		if(selcond[i]!=str_none)
		{
			fl=1;
			break;
		}
	}
	cmp(t__1,10);
	if(fl==0)
	{
	//	printf("ent\n");
		join_data_fin=join_data;
		seldata();
	}
	else
	{
		cmp(t__1,10);
		vector<int> fdatas;
		int andcond,orcond;
		andcond=orcond=-1;
		if(selcond[5]==str_or)
		{
			orcond=1;
		}
		else if(selcond[5]==str_none)
		{
		}
		else if(selcond[5]==str_and)
		{
			andcond=1;
		}
		if(orcond==1)
		{
			cmp(t__1,10);
			string ftbl;
			string clmn;
			string tbl;
			vector<int> fdata1,fdata2;			
			tbl=selcond[0];
			clmn=selcond[1];
			if(checknum(clmn))
			{
				printf("error\n");
				err=1;chk_exit();;
chk_exit();
				return;
			}
			else if(tbl==str_none)
			{
				ftbl=clmn;
			}
			else if(checknum(clmn))
			{
				printf("error\n");
				err=1;chk_exit();;
				chk_exit();
				return;
			}
			else
			{
				ftbl=tbl+"."+clmn;
			}
			int cmpr1=-1;
			cmpr1=cmpte(ftbl);
			if(cmpr1==-1)
			{
				printf("error\n");
				err=1;chk_exit();;
				return;
			}	
			
			string tbl2;
tbl2=selcond[3];
			int cmpr3=INT_MIN;
string ftbl2;
string clmn2;
			clmn2=selcond[4];
			int cmpr2=-1;
			cmp(t__1,10);
			if(checknum(clmn2))
			{
				cmpr3=atoi(clmn2.c_str());
			}
			else if(tbl2==str_none)
			{
				ftbl2=clmn2;
			}
			else
			{
				ftbl2=tbl2+"."+clmn2;
			}
			if(cmpr3!=INT_MIN)
			{
				cmp(t__1,10);
				if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}				
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_g)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>cmpr3)
						{
							fdata1.push_back(i);
						}
					}
				}
				cmp(t__1,10);
				cmp(t__1,10);
			}
			else
			{
				cmp(t__1,10);
				cmpr2=cmpte(ftbl2);
				if(cmpr2==-1)
				{
					printf("error\n");
					err=1;chk_exit();;
					return;
				}
				
				if(selcond[2]==str_ne)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
					cmp(t__1,10);
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
					for(i=0;i<join_data.size();i++)
					{
						join_data[i].erase(join_data[i].begin()+cmpr2);
					}
					metadata.erase(metadata.begin()+cmpr2);
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
					cmp(t__1,10);
				}
				else if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
					cmp(t__1,10);
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>join_data[i][cmpr2])
						{
							fdata1.push_back(i);
						}
					}
				}
				cmp(t__1,10);
			}


			tbl=selcond[6];
			ftbl.clear();
			clmn=selcond[7];
			cmp(t__1,10);
			if(checknum(clmn))
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}
			else if(tbl==str_none)
			{
				ftbl=clmn;
			}
			else if(checknum(clmn))
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}
			else
			{
				ftbl=tbl+"."+clmn;
			}
			cmp(t__1,10);
			cmpr1=-1;
			cmpr1=cmpte(ftbl);
			if(cmpr1==-1)
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}	
			
			cmpr3=INT_MIN;
			cmpr2=-1;
			clmn2=selcond[10];
			tbl2=selcond[9];
			ftbl2.clear();
			cmp(t__1,10);
			if(checknum(clmn2))
			{
				cmpr3=atoi(clmn2.c_str());
			}
			else if(tbl2==str_none)
			{
				ftbl2=clmn2;
			}
			else if(checknum(clmn2))
			{
				cmpr3=atoi(clmn2.c_str());
			}
			else
			{
				ftbl2=tbl2+"."+clmn2;
			}
			cmp(t__1,10);
			if(cmpr3!=INT_MIN)
			{
				cmp(t__1,10);
				
				if(selcond[8]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_le)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_ge)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_eq)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==cmpr3)
						{
							fdata2.push_back(i);
						}
					}
				}
				cmp(t__1,10);
			}
			else
			{
				cmp(t__1,10);
				cmpr2=cmpte(ftbl2);
				if(cmpr2==-1)
				{
					err=1;chk_exit();;
					printf("error\n");
					return;
				}
				cmp(t__1,10);
				if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					cmp(t__1,10);
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==join_data[i][cmpr2])
						{
							fdata2.push_back(i);
						}
					}
					for(i=0;i<join_data.size();i++)
					{
						join_data[i].erase(join_data[i].begin()+cmpr2);
					}
					metadata.erase(metadata.begin()+cmpr2);
				}
				cmp(t__1,30);
			}

			set<int> temp_set;
			cmp(t__1,10);
			for(i=0;i<fdata1.size();i++)
			{
				temp_set.insert(fdata1[i]);
			}
			cmp(t__1,10);
			for(i=0;i<fdata2.size();i++)
			{
				temp_set.insert(fdata2[i]);
			}
			cmp(t__1,10);
			set<int>::iterator it1=temp_set.begin();
			while(it1!=temp_set.end())
			{
				fdatas.push_back((*it1));
				it1++;
			}
			cmp(t__1,10);
		}
		else if(andcond==1)
		{
			cmp(t__1,10);
			string clmn;
			vector<int> fdata1;
			clmn=selcond[1];
			string tbl;
			vector<int> fdata2;			
			tbl=selcond[0];
			string ftbl;
			if(checknum(clmn))
			{
				printf("error\n");exit(0);
				err=1;chk_exit();;
				return;
			}
			else if(tbl!=str_none)
			{
				ftbl=tbl+"."+clmn;
			
			}
			else
			{
				ftbl=clmn;	
			}
			int cmpr__1=-1;
			cmpr__1=cmpte(ftbl);
			cmp(t__1,10);
			if(cmpr__1==-1)
			{
				printf("error\n");exit(0);
				err=1;chk_exit();;
				return;
			}	
			string clmn__2;
			clmn__2=selcond[4];
			int cmp__3=INT_MIN;
			string tbl__2;
			int cmp__2=-1;
			tbl__2=selcond[3];
			string final_tbl__2;
			cmp(t__1,10);
			if(checknum(clmn__2))
			{
				cmp__3=atoi(clmn__2.c_str());
			}
			else if(tbl__2!=str_none)
			{
				final_tbl__2=tbl__2+"."+clmn__2;
				
			}
			else
			{
				final_tbl__2=clmn__2;
			}
			if(cmp__3!=INT_MIN)
			{
				cmp(t__1,30);
				if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]!=cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>=cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]==cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<=cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>cmp__3)
						{
							fdata1.push_back(i);
						}
					}
				}
				cmp(t__1,30);
			}
			else
			{
				cmp(t__1,30);
				cmp__2=cmpte(final_tbl__2);
				if(cmp__2==-1)
				{
					printf("error\n");exit(0);
					err=1;chk_exit();;
					return;
				}
				cmp(t__1,30);
				if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]!=join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>=join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<=join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]==join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
					for(i=0;i<join_data.size();i++)
					{
						join_data[i].erase(join_data[i].begin()+cmp__2);
					}
					metadata.erase(metadata.begin()+cmp__2);
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>join_data[i][cmp__2])
						{
							fdata1.push_back(i);
						}
					}
				}
				cmp(t__1,30);
			}


			
			tbl=selcond[6];
			cmp(t__1,30);	
			clmn=selcond[7];
			ftbl.clear();
			if(checknum(clmn))
			{
				printf("error\n");exit(0);
				err=1;chk_exit();;
				return;
			}
			else if(tbl!=str_none)
			{
				ftbl=tbl+"."+clmn;
				
			}
			else
			{
				ftbl=clmn;
				
			}
			cmpr__1=-1;
			cmpr__1=cmpte(ftbl);
			cmp(t__1,30);
			if(cmpr__1==-1)
			{
				printf("error\n");exit(0);
				err=1;chk_exit();;
				return;
			}	
			clmn__2=selcond[10];
			cmp__3=INT_MIN;
			tbl__2=selcond[9];
			cmp__2=-1;
			cmp(t__1,30);
			
			final_tbl__2.clear();
			if(checknum(clmn__2))
			{
				cmp__3=atoi(clmn__2.c_str());
			}
			else if(tbl__2==str_none)
			{
				final_tbl__2=clmn__2;
			}
			else
			{
				final_tbl__2=tbl__2+"."+clmn__2;
			}
			if(cmp__3!=INT_MIN)
			{
				cmp(t__1,30);
				
				if(selcond[8]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]!=cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<=cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]==cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>=cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[8]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>cmp__3)
						{
							fdata2.push_back(i);
						}
					}
				}
				cmp(t__1,30);
			}
			else
			{
				cmp(t__1,30);
				cmp__2=cmpte(final_tbl__2);
				if(cmp__2==-1)
				{
					printf("error\n");exit(0);
					err=1;chk_exit();;
					return;
				}
				cmp(t__1,30);
				if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]!=join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]==join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
					for(i=0;i<join_data.size();i++)
					{
						join_data[i].erase(join_data[i].begin()+cmp__2);
					}
					metadata.erase(metadata.begin()+cmp__2);
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]<=join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr__1]>=join_data[i][cmp__2])
						{
							fdata2.push_back(i);
						}
					}
				}
				cmp(t__1,30);
			}
			cmp(t__1,30);
			int temp_flag=0;
			for(i=0;i<fdata1.size();i++)
			{
				temp_flag=0;
				for(j=0;j<fdata2.size();j++)
				{
					if(fdata1[i]==fdata2[j])
					{
						temp_flag=1;
						break;
					}
				}
				if(temp_flag==1)
				{
					fdatas.push_back(fdata1[i]);
				}
			}
			cmp(t__1,30);

		}
		else
		{
			cmp(t__1,30);
			string clmn;
			clmn=selcond[1];
			string ftbl;
			string tbl;
			tbl=selcond[0];
			if(checknum(clmn))
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}
			else if(tbl==str_none)
			{
				ftbl=clmn;
			}
			else if(checknum(clmn))
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}
			else
			{
				ftbl=tbl+"."+clmn;
			}
			cmp(t__1,30);
			int cmpr1=-1;
			cmpr1=cmpte(ftbl);
			if(cmpr1==-1)
			{
				err=1;chk_exit();;
				printf("error\n");
				return;
			}
			int cmpr3=INT_MIN;
			string tbl2;
			tbl2=selcond[3];
			string ftbl2;	
			string clmn2;
			clmn2=selcond[4];
			int cmpr2=-1;
			cmp(t__1,30);
			if(checknum(clmn2))
			{
				cmpr3=atoi(clmn2.c_str());
			}
			else if(tbl2==str_none)
			{
				ftbl2=clmn2;
			}
			else if(checknum(clmn2))
			{
				cmpr3=atoi(clmn2.c_str());
			}
			else
			{
				ftbl2=tbl2+"."+clmn2;
			}
			cmp(t__1,30);
			if(cmpr3!=INT_MIN)
			{
				cmp(t__1,30);
				
				if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}				
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==cmpr3)
						{
							fdatas.push_back(i);
						}
					}
				}
				cmp(t__1,30);
			}
			else
			{
				cmp(t__1,30);
				cmpr2=cmpte(ftbl2);
				if(cmpr2==-1)
				{
					err=1;chk_exit();;
					printf("error\n");
					return;
				}
				cmp(t__1,30);
				if(selcond[2]==str_ne)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]!=join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_le)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<=join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_ge)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>=join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_l)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]<join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_g)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]>join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
				}
				else if(selcond[2]==str_eq)
				{
					for(i=0;i<join_data.size();i++)
					{
						if(join_data[i][cmpr1]==join_data[i][cmpr2])
						{
							fdatas.push_back(i);
						}
					}
					for(i=0;i<join_data.size();i++)
					{
						join_data[i].erase(join_data[i].begin()+cmpr2);
					}
					metadata.erase(metadata.begin()+cmpr2);
				}	
				cmp(t__1,30);
			}
		}
		cmp(t__1,30);
		for(i=0;i<fdatas.size();i++)
		{
			join_data_fin.push_back(join_data[fdatas[i]]);
		}
		cmp(t__1,30);
		seldata();
	}
}
void extract_data(string filename)
{
	char *char_arr=(char *)malloc(sizeof(char)*(filename.size()+1));
	strcpy(char_arr, filename.c_str());
	ifstream file_data;
	file_data.open(char_arr);
	string file_line;
	vector<int> data_in;
	cmp(t__1,30);
	vector<vector<int> > data_fin;
	if(file_data.is_open())
	{
//		cout<<filename<<endl;
		while(getline(file_data,file_line))
		{
			stringstream file_line2(file_line);
			string out1;
			while(getline(file_line2,out1,','))
			{
				out1.erase(remove( out1.begin(), out1.end(), '\"' ),out1.end());
				data_in.push_back(atoi(out1.c_str()));
			}
			/*
			for(int i=0;i<data_in.size();i++)
				cout<<data_in[i]<<',';
			cout<<endl;
			*/
			data_fin.push_back(data_in);
			data_in.clear();
		}
		table_dt[filename]=data_fin;
		data_fin.clear();
		file_data.close();
		cmp(t__1,30);
	}
	else
	{
		cmp(t__1,30);
		cout<<"Cannot open file: " + filename<<endl;
		cmp(t__1,30);
	}
}
void extract_table()
{
	ifstream file1("metadata.txt");
//	file1.open("metadata.txt");
	string tbl,file_line,file_line1;
	vector <string> data1;
	int f=-2;
	cmp(t__1,30);
	if(file1.is_open())
	{
		f=-2;
		while(getline(file1,file_line))
		{
			file1>>file_line1;
		//	cout<<file_line1<<endl;
			if(f==0)
			{
				tbl=file_line1;
				f=1;
			}
			else if(f==1 && file_line1!=end_tbl)
			{
				data1.push_back(file_line1);
			}
			if(file_line1==beg_tbl)
			{
		//		printf("entered\n");
				f=0;
			}
			else if(f==-2)
			{
		//		printf("entered1\n");
				tbl=file_line1;
				f=1;
			}
			else if(file_line1==end_tbl)
			{
				table_field[tbl]=data1;
				/*
				cout<<tbl<<endl;
				for(int l=0;l<table_field[tbl].size();l++)
				{
					cout<<table_field[tbl][l]<<endl;
				}
				*/
				data1.clear();
				f=-1;
			}
			file_line1.clear();
		}
		file1.close();
		cmp(t__1,30);
	}
	else
	{
		cmp(t__1,30);
		cout<<"Cannot open file metadata.txt"<<endl;
		cmp(t__1,30);
	}

}
void filenames()
{
	map < string,vector<string> > :: iterator iter;
	iter=table_field.begin();
	string filename;
	cmp(t__1,30);
	while(iter!=table_field.end())
	{
		filename=(*iter).first +".csv";
		extract_data(filename);
		iter++;
	}
	cmp(t__1,30);
}
void join()
{
	int i=0,j=0;
	cmp(t__1,30);
//	cout<<join_table.size()<<"size"<<endl;
	for(i=0;i<join_table.size();i++)
	{
		if(table_dt.find(join_table[i]+".csv")==table_dt.end())
		{
			err=1;chk_exit();;
			printf("error\n");
			return;
		}
	}
	if(join_table.empty())
	{
		err=1;chk_exit();;
		printf("error\n");
		return;
	}
	cmp(t__1,30);
	string tablenm;
	map<string,vector<vector<int> > >::iterator iter1;
	tablenm=join_table[0]+".csv";
//	cout<<tablenm<<"join"<<endl;
	iter1=table_dt.find(tablenm);
	join_data=(*iter1).second;
/*	for(int i=0;i<join_data.size();i++)
	{
		for(int j=0;j<join_data[i].size();j++)
		{
			cout<<join_data[i][j]<<",";
		}
		cout<<endl;
	}
	*/
	/*vector<string> :: iterator iter;
	iter=join_table.begin();
	join_data=table_dt[(*iter)];
	iter++;
	*/
	vector<vector<int > > temp;
	vector<int>temp1;
	vector<vector<int > > temp2;
	cmp(t__1,30);
	for(int l=1;l<join_table.size();l++)
	{
		tablenm=join_table[l]+".csv";
	//	cout<<tablenm<<endl;
		iter1=table_dt.find(tablenm);
		temp=(*iter1).second;
		/*
	for(int i=0;i<temp.size();i++)
	{
		for(int j=0;j<temp[i].size();j++)
		{
			cout<<temp[i][j]<<",";
		}
		cout<<endl;
	}*/
		for(int i=0;i<join_data.size();i++)
		{
			for(int j=0;j<temp.size();j++)
			{
				for(int k=0;k<join_data[i].size();k++)
				{
					temp1.push_back(join_data[i][k]);
				}
				for(int k=0;k<temp[j].size();k++)
				{
					temp1.push_back(temp[j][k]);
				}
				temp2.push_back(temp1);
				temp1.clear();
			}
		}
		join_data=temp2;
		temp2.clear();
	//	iter++;
	}
	cmp(t__1,30);
}
void join_get_meta()
{
	string temp;
	map<string,vector<string> >::iterator iter;
	string temp1;
	vector<string> table_content;
	cmp(t__1,30);
//	cout<<join_table.size()<<endl;
	for(int i=0;i<join_table.size();i++)
	{
		temp=join_table[i];
	//	cout<<temp<<endl;
		iter=table_field.find(temp);
		if(iter==table_field.end())
		{
			err=1;chk_exit();;
			printf("error\n");
			return;
		}
		else
		{
			table_content=(*iter).second;
			for(int j=0;j<table_content.size();j++)
			{
				temp1=temp+"."+table_content[j];
				metadata.push_back(temp1);
				temp1.clear();
			}
		}
	}
	cmp(t__1,30);
	join();
}
void query_f()
{
	int pointr1=-1,pointr2=-1,pointr3=-1;
	int i=0,j=0;
	cmp(t__1,30);
	vector<string> temp;
//	cout<<que1.size()<<endl;
	for(i=0;i<que1.size();i++)
	{
//		cout<<que1[i]<<endl;
		if(cmpstr(que1[i],str_whr))
		{
			pointr3=i;
		}
		else if(cmpstr(que1[i],frm))
		{
			pointr2=i;
		}
		else if(cmpstr(que1[i],sel))
		{
			pointr1=i;
		}
	}
	if(pointr1==-1)
	{
		cmp(t__1,30);
		return;
	}
	else
	{
//	printf("hello\n");
		cmp(t__1,30);
		for(i=pointr1+1;i<pointr2;i++)
		{
			string str1,str2,str3;
			cmp(t__1,30);
			if(que1[i]!="")
			{
				que1[i]=space_remove(que1[i]);
				if(que1[i].find("distinct")!=-1)
				{
					int fin=que1[i].find("(");
					df=1;
					if(fin!=-1)
					{
					dc=1;
					temp.push_back(dist);
					str1=que1[i].substr(que1[i].find("(")+1,que1[i].find(")")-que1[i].find("(")-1);
					str1=space_remove(str1);
					if(str1.find(".")==-1)
					{
						temp.push_back(str_none);
						temp.push_back(str1);

						
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);

					}
					selcol.push_back(temp);
					}
				}
				else if(que1[i].find("min")!=-1)
				{
					temp.push_back(mn);
					str1=que1[i].substr(que1[i].find("(")+1,que1[i].find(")")-que1[i].find("(")-1);
					str1=space_remove(str1);
					if(str1.find(".")==-1)
					{
						temp.push_back(str_none);
						temp.push_back(str1);

						
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);

					}
					selcol.push_back(temp);
				}
				else if(que1[i].find("avg")!=-1)
				{
					temp.push_back(av);
					str1=que1[i].substr(que1[i].find("(")+1,que1[i].find(")")-que1[i].find("(")-1);
					str1=space_remove(str1);
					if(str1.find(".")==-1)
					{
						temp.push_back(str_none);
						temp.push_back(str1);

						
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);

					}
					selcol.push_back(temp);
				}
				else if(que1[i].find("max")!=-1)
				{
					temp.push_back(mx);
					str1=que1[i].substr(que1[i].find("(")+1,que1[i].find(")")-que1[i].find("(")-1);
					str1=space_remove(str1);
					if(str1.find(".")==-1)
					{
							temp.push_back(str_none);
						temp.push_back(str1);
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);
					}
					selcol.push_back(temp);
				}
				else if(que1[i].find("sum")!=-1)
				{
					temp.push_back(sm);
					str1=que1[i].substr(que1[i].find("(")+1,que1[i].find(")")-que1[i].find("(")-1);
					str1=space_remove(str1);
					if(str1.find(".")==-1)
					{
						temp.push_back(str_none);
						temp.push_back(str1);

						
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);

					}
					selcol.push_back(temp);
				}
				else if(que1[i]=="*")
				{
//					printf("ALL query_f\n");
					temp.push_back(str_none);    // max, avg, min 
					temp.push_back(str_none);    // table
					temp.push_back("ALL");     // column
					selcol.push_back(temp);
				}
				else
				{
					temp.push_back(str_none);
					str1=space_remove(que1[i]);
					if(str1.find(".")==-1)
					{
						temp.push_back(str_none);
						temp.push_back(str1);

						
					}
					else
					{
						str2=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
						str3=str1.substr(0,str1.find("."));
						temp.push_back(str3);
						temp.push_back(str2);

					}
					selcol.push_back(temp);
				}
				temp.clear();
			}
			else if(que1[i]=="")
			{
			}
			cmp(t__1,30);
		}
	}
	/*for(i=0;i<selcol.size();i++)
	{
		for(j=0;j<selcol[i].size();j++)
		{
			cout<<selcol[i][j]<<" ";
		}
		printf("\n");
	}*/
	cmp(t__1,30);
	if(pointr2==-1)
	{
	//	printf("No table to select from\n");
		return;
	}
	else
	{
	//	printf("tables to join\n");
		int tmpo=0;
		if(pointr3!=-1)
		{
				tmpo=pointr3;
		}
		else
		{
			tmpo=que1.size();
		
		}
		for(i=pointr2+1;i<tmpo;i++)
		{
			if(que1[i]!="")
			{
				que1[i]=space_remove(que1[i]);
//				cout<<que1[i]<<endl;
				join_table.push_back(que1[i]);
			}
			else
			{
				//cout<<que1[i]<<"\n";
			}
		}
	}
	cmp(t__1,30);
	if(pointr3==-1)
	{
//		printf("no where\n");
		//printf("No conditions\n");
	}
	else
	{
		//printf("Conditions to select\n");
		for(i=pointr3+1;i<que1.size();i++)
		{
			cmp(t__1,30);
			string str1,str2,str3,c4,c5,c6;
			if(que1[i]!="")
			{
				que1[i]=space_remove(que1[i]);
				
				if(que1[i].find(str_or)!=-1)
				{
					selcond.push_back(str_or);
				}
				else if(que1[i].find(str_and)!=-1)
				{
					selcond.push_back(str_and);
				}
				else
				{
					if(que1[i].find("<")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find("<"));
						str1=space_remove(str1);
						str2=que1[i].substr(que1[i].find("<")+1,que1[i].size()-que1[i].find("<"));
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_l);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					else if(que1[i].find("!=")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find("!="));
						str1=space_remove(str1);
						str2=que1[i].substr(que1[i].find("!=")+2,que1[i].size()-que1[i].find("!=")+1);
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_ne);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					else if(que1[i].find("<=")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find("<="));
						str1=space_remove(str1);
						str2=que1[i].substr(que1[i].find("<=")+2,que1[i].size()-que1[i].find("<=")+1);
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_le);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					else if(que1[i].find(">")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find(">"));
						str1=space_remove(str1);
						str2=que1[i].substr(que1[i].find(">")+1,que1[i].size()-que1[i].find(">"));
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_g);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					else if(que1[i].find("=")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find("="));
str1=space_remove(str1);
						str2=que1[i].substr(que1[i].find("=")+1,que1[i].size()-que1[i].find("="));
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_eq);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					else if(que1[i].find(">=")!=-1)
					{
						str1=que1[i].substr(0,que1[i].find(">="));
						str1=space_remove(str1);
						
						str2=que1[i].substr(que1[i].find(">=")+2,que1[i].size()-que1[i].find(">=")+1);
						
						str2=space_remove(str2);
						if(str1.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str1);

						}
						else
						{

							str3=str1.substr(str1.find(".")+1,str1.size()-str1.find("."));
							c4=str1.substr(0,str1.find("."));
							selcond.push_back(c4);
							selcond.push_back(str3);
						}
						selcond.push_back(str_ge);
						if(str2.find(".")==-1)
						{
							selcond.push_back(str_none);
							selcond.push_back(str2);


						}
						else
						{
							str3=str2.substr(str2.find(".")+1,str2.size()-str2.find("."));
							c4=str2.substr(0,str2.find("."));
							selcond.push_back(c4);
						selcond.push_back(str3);							
						}
					}
					
					
				}
				cmp(t__1,30);
			}
			else if(que1[i]=="")
			{
			}
			
		}
		while(selcond.size()!=11)
		{
			selcond.push_back(str_none);
		}
		cmp(t__1,30);
	/*	for(i=0;i<selcond.size();i++)
		{
			cout<<selcond[i]<<" ";
		}
		cout<<"\n";*/
	}
}
char * ret_query(char *s)
{
	int len;
	cmp(t__1,30);
	len=strlen(s);
	char *s1=(char *)malloc(sizeof(char)*(len+1));
	strcpy(s1,s);
	if(s1[len-1]==';')
	{
		s1[len-1]='\0';
	}
	cmp(t__1,30);
	return s1;
}
void chk_exit()
{
	if(err==1)
	{
		exit(0);
	}
}
