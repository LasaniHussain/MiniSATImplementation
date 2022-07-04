#include<bits/stdc++.h>
using namespace std;
vector<vector<int> > read()
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
	int lit_cnt,cl_cnt;
	cin>>lit_cnt>>cl_cnt;
	vector<vector<int> > clauses(cl_cnt);
	for(int i=0;i<cl_cnt;i++)
	{	int literal;
		while(true)
		{
			cin>>literal;
			if(literal>0)
				clauses[i].push_back(2*(literal-1));
			else if(literal<0)
				clauses[i].push_back(2*(-1*literal-1)+1);
			else
				break;
		}
	}
	return clauses;
}
int main()
{	// Read from input file in DIMAS format
	vector<vector<int> > clauses=read();
	for(auto cl:clauses)
	{
		for(auto lit:cl)
			cout<<lit<<" ";
		cout<<"\n";
	}
	return 0;
}
