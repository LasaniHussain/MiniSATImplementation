#include<bits/stdc++.h>
using namespace std;

#define ST 0
#define UST 0
#define NM 0
#define COMP 0
void clear_and_resize(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign,int var_cnt,int cl_cnt)
{	clauses.clear();
	clauses.resize(cl_cnt);

	variables.clear();
	variables.resize(var_cnt, -1);

	variable_freq.clear();
	variable_freq.resize(var_cnt,0);

	variable_sign.clear();
	variable_sign.resize(var_cnt,0);

}
void read(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign,int &var_cnt,int &cl_cnt)
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
	//int var_cnt,cl_cnt;
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
int unit_propagation(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign,int &var_cnt,int &cl_cnt)
{
	bool unit_clause_found =false; // current iteration found a unit clause
	if (clauses.size() == 0) // formula contains no clauses
	{
		return UST; // vacuously true
	}
  	do 
	{
		unit_clause_found = false;
		for (int i = 0; i < clauses.size(); i++) 
		{
			if (clauses[i].size() ==1) 
			{
				unit_clause_found = true;
				variables[clauses[i][0] / 2] = clauses[i][0] % 2; 
				variable_freq[clauses[i][0] / 2] = -1; 
				int result = apply_transform(clauses,variables, clauses[i][0] /2); 
				if (result == ST|| result == UST) 
				{
					return result;
				}
				break; // exit loop , check for another unit clause from the start
			} 
			else if (clauses[i].size() == 0) // if a given clause is empty
			{
				return UST; // the formula is unsatisfiable in this branch
			}
		}
  	} while (unit_clause_found);

  return NM;
}
void transformation(vector<vector<int> > &clauses,vector<int> &variables,int lit_to_apply)
{	int val_to_apply = variables[lit_to_apply];
	for (int i = 0; i < clauses.size(); i++) 
	{

    	for (int j = 0; j < clauses[i].size(); j++) 
		{
      
			if ((2 * lit_to_apply + val_to_apply) == clauses[i][j]) 
			{
				clauses.erase(clauses.begin() + i); 
				i--;                
				if (clauses.size() ==0) 
				{
				return ST;
				}
				break; 
			} 
			else if (clauses[i][j] / 2 == literal_to_apply) 
			{
				clauses[i].erase(clauses[i].begin() +j); 
				j--;    
				if (clauses[i].size()==0) 
				{
					return UST;
				}
				break; 
			}
		}
    }
  // the function is exiting normally
  return NM;
}
int main()
{	// Read from input file in DIMAS format
	vector<vector<int> > clauses;
	vector<int> variables,variable_freq,variable_sign;
	int var_cnt,cl_cnt;
	read(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt);

	unit_propagation(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt);

	for(auto cl:clauses)
	{
		for(auto lit:cl)
			cout<<lit<<" ";
		cout<<"\n";
	}
	return 0;
}
