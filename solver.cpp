#include<bits/stdc++.h>
using namespace std;
void clear_and_resize(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign,int var_cnt,int cl_count)
{	clauses.clear();
	clauses.resize(cl_cnt);

	variables.clear();
	variables.resize(var_cnt, -1);

	variable_freq.clear();
	variable_freq.resize(var_cnt,0);

	variable_sign.clear();
	variable_sign.resize(var_cnt,0);

}
void read(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign)
{
	string s;
	char ch;
	// this skips comment lines
	while(true)
	{
		cin>>ch;
		if(ch=='c')
		{
			getline(cin,s);//consume the comment line
			continue;
		}
		else
		break;
	}
	cin>>s;//consume "cnf"
	cout<<s;
	int var_cnt,cl_cnt;
	cin>>var_cnt>>cl_cnt;
	clear_and_resize(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt);
	for(int i=0;i<cl_cnt;i++)
	{	int literal;
		while(true)
		{
			cin>>literal;
			if(literal>0)
			{	clauses[i].push_back(2*(literal-1));
				variable_freq[literal - 1]++;
        		variable_sign[literal - 1]++;
			}	
			else if(literal<0)
			{
				clauses[i].push_back(2*(-1*literal-1)+1);
				variable_freq[-1 - literal]++;
        		variable_sign[-1 - literal]--;
			}
				
			else
				break;
		}
	}
}
int main()
{	// Read from input file in DIMAS format
	vector<vector<int> > clauses();
	vector<int> variables,variable_freq,variable_sign;
	read(clauses,variables,variable_freq,variable_sign);

	for(auto cl:clauses)
	{
		for(auto lit:cl)
			cout<<lit<<" ";
		cout<<"\n";
	}
	return 0;
}
