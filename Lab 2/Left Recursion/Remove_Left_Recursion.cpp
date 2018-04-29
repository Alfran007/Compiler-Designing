#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<string>
using namespace std;

map<string, vector<string> > grammar, finalGrammar;
map<string, vector<string> >::iterator it;

vector<string> v, marked;

void printGrammar(map<string, vector<string> > grammar)
{
	string str;
	for(it = grammar.begin(); it != grammar.end(); ++it)
	{
		str = it->first;
		cout<<str<<" -> ";
		
		v = it->second;
		for(int i = 0; i < v.size(); ++i)
		{
			if(i != 0) cout<<" | ";
			cout<<v[i];
		}
		
		cout<<endl;
	}
}

void findLR()
{
	string str;
	for(it = grammar.begin(); it != grammar.end(); ++it)
	{
		str = it->first;
		v = it->second;
		
		size_t ind;
		for(int i = 0; i < v.size(); ++i)
		{
			ind = v[i].find(str);
			if(ind != string::npos) 
			{
				marked.push_back(str);
				//cout<<str<<" has left recursion"<<endl;
				break;
			}
		}
		
	}
	
}

string findNext()
{
	static int count = -1;
	count++;
	string ret = "Z";
	
	for(int i = 0; i < count; ++i) ret += "'";
	return ret;
}

void removeLR()
{
	for(int i = 0; i < marked.size(); ++i)
	{
		string add = findNext();
	
		string str = marked[i];
		v = finalGrammar[str];
		
		finalGrammar.erase(str);
		
		size_t ind;
		for(int j = 0; j < v.size(); ++j)
		{
			ind = v[j].find(str);
			if(ind == string::npos)									//For Non Recursive elements in recursive Non Terminal
			{
				finalGrammar[str].push_back(v[j] + add);
			}
			else													//For Recursive elements in recursive Non Terminal
			{
				finalGrammar[add].push_back(v[j].substr(str.length()) + add);
			}
		}
		finalGrammar[add].push_back("epsilon");
	}
}

int main()
{
	freopen("Input_Remove_Left_Recursion.txt", "r", stdin);
	
	string str;
	size_t ind;
	
	while(getline(cin, str)) 
	{
		ind = str.find(" -> ");
		string first = str.substr(0, ind);
		string second = str.substr(ind+4);
		
		grammar[first].push_back(second);
	}
	
	finalGrammar = grammar;
	
	cout<<"The actual grammar with Left Recursion is : "<<endl;
	printGrammar(grammar);
	cout<<"--------------------------------------------"<<endl;
	
	findLR();
	
	removeLR();
	
	cout<<"The changed grammar withour left recursion is : "<<endl;
	printGrammar(finalGrammar);
	cout<<"------------------------------------------------"<<endl;
	
     return 0;
}
