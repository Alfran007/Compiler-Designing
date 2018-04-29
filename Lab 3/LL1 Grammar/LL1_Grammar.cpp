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

int checkIntersection(set<string> check[], int n)
{
    map<string, int> m;

    /* To print the sets
    for(int i = 0; i < n; ++i)
    {
        cout<<"Set "<<i+1<<" : { ";
        for(set<string>::iterator j = check[i].begin(); j != check[i].end(); ++j)
        {
            if(j != check[i].begin()) cout<<", ";
            cout<<*j;
        }
        cout<<" }"<<endl;
    }
    */

    for(int i = 0; i < n; ++i)
    {
        for(set<string>::iterator j = check[i].begin(); j != check[i].end(); ++j)
        {
            if(m[*j]) return 0;
            else m[*j] = 1;
        }
    }

    return 1;
}

int checkGrammar()
{
    string str;
    for(it = grammar.begin(); it != grammar.end(); ++it)
	{
		str = it->first;
		v = it->second;

		if(v.size() <= 1) continue;

        set<string> check[v.size()];

		for(int i = 0; i < v.size(); ++i)
		{
		    if(v[i] == "#")
            {
                check[i].insert(Follow[str].begin(), Follow[str].end());
                continue;
            }
		    for(int j = 0; j < v[i].length(); ++j)
            {
                char ch = v[i][j];
                string k = string(1, ch);
                if(ch >= 65 && ch <= 90)
                {
                    check[i].insert(First[k].begin(), First[k].end());
                    if(First[k].find("#") == First[k].end()) break;
                }
                else
                {
                    check[i].insert(k);
                    break;
                }
            }
		}

		if(!checkIntersection(check, v.size())) return 0;
	}

	return 1;
}

int main()
{
	freopen("Input_LL1_Grammar4.txt", "r", stdin);

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

	if(checkGrammar()) cout<<"Grammar is LL1"<<endl;
	else cout<<"Grammar is not LL1"<<endl;
	cout<<"--------------------------------------------"<<endl;

	return 0;
}
