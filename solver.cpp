#include<bits/stdc++.h>
using namespace std;

#define ST 0
#define UST 1
#define NM 2
#define COMP 3
void clear_and_resize(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,vector<int> &variable_sign,
int var_cnt,int cl_cnt)
{	clauses.clear();
	clauses.resize(cl_cnt);

	variables.clear();
	variables.resize(var_cnt, -1);

	variable_freq.clear();
	variable_freq.resize(var_cnt,0);

	variable_sign.clear();
	variable_sign.resize(var_cnt,0);

}
void read(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,
vector<int> &variable_sign,int &var_cnt,int &cl_cnt)
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
int transformation(vector<vector<int> > &clauses,vector<int> &variables,int lit_to_apply)
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
			else if (clauses[i][j] / 2 == lit_to_apply) 
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
  return NM;
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
				int result = transformation(clauses,variables, clauses[i][0] /2); 
				if (result == ST|| result == UST) 
				{
					return result;
				}
				break; // exit loop , 
			} 
			else if (clauses[i].size() == 0) 
			{
				return UST; // the formula is unsatisfiable in this branch
			}
		}
  	} while (unit_clause_found);

  return NM;
}

void display_result(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,
vector<int> &variable_sign,int &var_cnt,int &cl_cnt,int result)
{
	if (result == ST) // if the formula is satisfiable
  	{
		cout << "SAT" << endl;
		for (int i = 0; i < variables.size(); i++) 
		{
			if (i != 0) 
			{
				cout << " ";
			}
			if (variables[i] != -1) 
			{
				cout << pow(-1, variables[i]) * (i + 1);
			} 
			else // for literals which can take either value, arbitrarily assign them to be true
			{
				cout << (i + 1);
			}
		}
		cout << " 0";
  	} 
	else // if the formula is unsatisfiable
	{
		cout << "UNSAT";
	}
}
int DPLL(vector<vector<int> > &clauses,vector<int> &variables,vector<int> &variable_freq,
vector<int> &variable_sign,int &var_cnt,int &cl_cnt) 
{
  int result = unit_propagation(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt); // perform unit propagation on the formula
  if (result == ST) // if formula satisfied, show result and return
  {
    display_result(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt, result);
    return COMP;
  } 
  else if (result == UST) 
  {
    return NM;
  }
  
  int i = distance(variable_freq.begin(),max_element(variable_freq.begin(), variable_freq.end()));
  // need to apply twice, once true, the other false
  for (int j = 0; j < 2; j++) 
  {
	vector<vector<int> > copy_clauses(clauses);
	vector<int> copy_variables(variables);
	vector<int> copy_variable_freq(variable_freq);
	vector<int> copy_variable_sign(variable_sign);
	int copy_var_cnt=var_cnt,copy_cl_cnt=cl_cnt;
    
    if (copy_variable_sign[i] >0) 
    {
      copy_variables[i] = j; 
    } 
	else                   
    {
      copy_variables[i] = (j + 1) % 2; 
    }
    copy_variable_freq[i] = -1; // reset the frequency to -1 
    int transformation_res = transformation(copy_clauses,copy_variables, i); // apply the change to all the clauses
    if (transformation_res == ST) // if formula satisfied, show result and return
    {
      display_result(copy_clauses,copy_variables,copy_variable_freq,copy_variable_sign,copy_var_cnt,copy_cl_cnt, transformation_res);
      return COMP;
    } 
	else if (transformation_res == UST) 
    {
      continue;
    }
    int dpll_result = DPLL(copy_clauses,copy_variables,copy_variable_freq,copy_variable_sign,copy_var_cnt,copy_cl_cnt); // recursively call DPLL on the new formula
    if (dpll_result == COMP) // propagate the result, if completed
    {
      return dpll_result;
    }
  }
  return NM;
}
int main()
{	// Read from input file in DIMACS format
	vector<vector<int> > clauses;
	vector<int> variables,variable_freq,variable_sign;
	int var_cnt,cl_cnt;
	read(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt);

	int result = DPLL(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt); 
	if (result == NM) 
	{
		display_result(clauses,variables,variable_freq,variable_sign,var_cnt,cl_cnt, UST); 
	}
	return 0;
}
