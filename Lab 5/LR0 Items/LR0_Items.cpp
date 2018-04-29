#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include "utilities.h"
using namespace std;

#define pb push_back
#define mp make_pair
#define f first
#define s second

map<string, vector<string> > grammar;
map<string, vector<string> >::iterator itG;

vector<pair<string, string> > prod;
vector<vector<pair<string, string> > > items;

pair<string, string> p;
vector<string> v;
set<string> vis;

void printGrammar(map<string, vector<string> > grammar)
{
	string str;
	for(itG = grammar.begin(); itG != grammar.end(); ++itG)
	{
		str = itG->f;
		cout<<str<<" -> ";

		v = itG->s;
		for(int i = 0; i < v.size(); ++i)
		{
			if(i != 0) cout<<" | ";
			cout<<v[i];
		}

		cout<<endl;
	}
}

void printItems()
{
	for(int i = 0; i < items.size(); ++i)
	{
		cout<<"Item "<<i<<" : ";
		for(int j = 0; j < items[i].size(); ++j)
		{
			p = items[i][j];
			if(j != 0) cout<<", ";
			cout<<"("<<p.f<<" -> "<<p.s<<")";
		}
		cout<<endl;
	}
}

void addProd()							//To add all the dependent productions
{
    vis.clear();
	for(int i = 0; i < prod.size(); ++i)
	{
        p = prod[i];
        size_t ind = p.s.find(".");
        string k = string(1, p.s[ind+1]);
        if(ind != p.s.length() - 1 && 65 <= p.s[ind+1] && p.s[ind+1] <= 90 && vis.find(k) == vis.end())
        {
            vis.insert(k);
            v = grammar[k];

            for(int j = 0; j < v.size(); ++j)
            {
                prod.pb(mp(k, "."+v[j]));
            }
        }
	}
}

void makeLR0()
{
	for(int i = 0; i < items.size(); ++i)
	{
		//if(i == 10) break;
		prod = items[i];
		addProd();
        //cout<<"Productions : "<<prod<<endl;
		//cout<<"Executing Size"<<items.size()<<endl;
        int flag = 0;
        for(int j = 0; j < i; ++j)				//To check if an item is already existing or not
        {
            if(j != i && items[j] == prod)
            {
            	//cout<<"Item to erase : "<<items[i]<<endl;
                items.erase(items.begin() + i);
                //cout<<"Erasing item["<<i<<"]"<<endl;
                i--;
                flag = 1;
                break;
            }
        }

        if(!flag)														//If not existing
        {
            items[i] = prod;
			//cout<<"Item ["<<i<<"] : "<<items[i]<<endl;
            vis.clear();
            for(int j = 0; j < items[i].size(); ++j)					//Shift The Dots Towards Right And Make New Items
            {
            	prod.clear();
                p = items[i][j];

                size_t ind = p.s.find(".");
                char c = p.s[ind+1];
                string k = string(1, c);
                if(ind != p.s.length() - 1 && vis.find(k) == vis.end())			//Selecting One Symbol
                {
                    vis.insert(k);

                    for(int k = 0; k < items[i].size(); ++k)										//Adding all other productions of same Symbol
                    {
                        p = items[i][k];
                        size_t ind2 = p.s.find(".");
                        if(ind2 != p.s.length() - 1 && p.s[ind2+1] == c)
                        {
							string temp = p.s;
							temp[ind2] = temp[ind2+1];
							temp[ind2+1] = '.';
							prod.pb(mp(p.f, temp));
                        }
                    }
                }
				if(!prod.empty()) items.pb(prod);
            }
        }
	}
}

int main()
{
	freopen("Input_LR0_Items5.txt", "r", stdin);

	string str, sSym;
	size_t ind;

	getline(cin, sSym);
	while(getline(cin, str))
	{
		ind = str.find(" -> ");
		string first = str.substr(0, ind);
		string second = str.substr(ind+4);

		grammar[first].push_back(second);
	}

	cout<<"The Input Grammar Is :- "<<endl;
	cout<<"Start Symbol : "<<sSym<<endl;
	printGrammar(grammar);
	cout<<"--------------------------------------------"<<endl;

	prod.pb(mp("S'", "."+sSym));
	items.pb(prod);
	makeLR0();

	cout<<"The Items Are :- "<<endl;
	printItems();
	cout<<"--------------------------------------------"<<endl;
	return 0;
}

