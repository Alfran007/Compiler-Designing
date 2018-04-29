#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <string>
using namespace std;

map<string, vector<string> > grammar;
map<string, set<string> > First, Follow;
map<string, vector<string> >::iterator it;

vector<string> v;
vector<string>::iterator i;
set<string> s, vis;

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

void printSetMap(map<string, set<string> > sm)
{
	for(map<string, set<string> >::iterator i = sm.begin(); i != sm.end(); ++i)
	{
		cout<<i->first<<" : { ";

		s = i->second;
		for(set<string>::iterator j = s.begin(); j != s.end(); ++j)
		{
			if(j != s.begin()) cout<<", ";
			cout<<*j;
		}
		cout<<" }"<<endl;
	}
}

set<string> findFirst(string k)
{
	//cout<<"Visiting For Key -> "<<k<<endl;
	if(vis.find(k) != vis.end()) return First[k];
	vis.insert(k);
	v = grammar[k];
    //cout << "v is :" << v << endl;
    /*for(i=v.begin();i!=v.end();i++)
    {
        cout << *i << endl;
    }
    cout << "lol" << endl;*/
	for(int i = 0; i < v.size(); ++i)
	{
		string str = v[i];
		for(int j = 0; j < str.length(); ++j)
		{
			if(str[j] >= 65 && str[j] <= 90)						//Reading a Non Terminal
			{
				//cout<<"Recursing For "<<str[j]<<endl;
				s = findFirst(string(1, str[j]));

				First[k].insert(s.begin(), s.end());

				if(s.find("#") == s.end()) break;
				else if(j != str.length() - 1)
                {
                    First[k].erase(First[k].find("#"));
                }
			}
			else													//All remaining are Terminals
			{
				First[k].insert(string(1, str[j]));
				//cout<<"Inserted -> "<<str[j]<<endl;
				break;
			}
		}
	}
	return First[k];
}

set<string> findFollow(string k)
{
    //cout<<"Visiting For Key -> "<<k<<endl;
    if(vis.find(k) != vis.end()) return Follow[k];
	vis.insert(k);

	for(map<string, vector<string> >::iterator temp = grammar.begin(); temp != grammar.end(); ++temp)
	{
		string nt = temp->first;
		v = temp->second;
		for(int i = 0; i < v.size(); ++i)
		{
            size_t ind = v[i].find(k);
            if(ind == string::npos) continue;
            for(ind = ind+1; ind < v[i].length(); ++ind)
            {
                if(v[i][ind] >= 65 && v[i][ind] <= 90)
                {
                    //cout<<"Storing First of "<<v[i][ind]<<" in "<<k<<endl;
                    Follow[k].insert(First[string(1, v[i][ind])].begin(), First[string(1, v[i][ind])].end());
                    Follow[k].erase(Follow[k].find("#"));
                    if(First[string(1, v[i][ind])].find("#") == First[string(1, v[i][ind])].end()) break;
                }
                else
                {
                    //cout<<"Storing "<<v[i][ind]<<" in "<<k<<endl;
                    Follow[k].insert(string(1, v[i][ind]));
                    break;
                }
            }
            if(ind == v[i].length())
            {
                //cout<<"Recursing For "<<nt<<endl;
                s = findFollow(nt);
                Follow[k].insert(s.begin(), s.end());
            }
		}
	}

	return Follow[k];
}

int main()
{
	freopen("Input_First_Follow3.txt", "r", stdin);

	string str;
	size_t ind;

	while(getline(cin, str))
	{
		ind = str.find(" -> ");
		string first = str.substr(0, ind);
		string second = str.substr(ind+4);

		grammar[first].push_back(second);
	}

	cout<<"The Input Grammar Is : "<<endl;
	printGrammar(grammar);
	cout<<"--------------------------------------------"<<endl;



	for(it = grammar.begin(); it != grammar.end(); ++it)
	{
		findFirst(it->first);
	}

	cout<<"First is : "<<endl;
	printSetMap(First);
	cout<<"--------------------------------------------"<<endl;



    vis.clear();
	Follow["S"].insert("$");
    findFollow("S");
	for(it = grammar.begin(); it != grammar.end(); ++it)
	{
		findFollow(it->first);
	}

	cout<<"Follow is : "<<endl;
	printSetMap(Follow);
	cout<<"--------------------------------------------"<<endl;

	return 0;
}
