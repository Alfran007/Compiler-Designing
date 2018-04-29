#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

map<string, vector<string> > grammar, finalGrammar;
map<string, vector<string> >::iterator it;

vector<string> v;

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

string findNext()
{
	static int count = -1;
	count++;
	string ret = "Z";

	for(int i = 0; i < count; ++i) ret += "'";
	return ret;
}

void leftFactoring()
{
	for(it = finalGrammar.begin(); it != finalGrammar.end(); ++it)
	{
        vector<string> pre;
		v = it->second;
		sort(v.begin(), v.end());

		string temp = v[0], prefix = "";
		for(int i = 1; i < v.size(); ++i)
		{
			int len = temp.length() + 1;
			size_t ind;
			while(--len)
			{
				ind = v[i].find(temp.substr(0, len));
				if(ind != string::npos && ind == 0)
				{
					prefix = temp.substr(0, len);
					temp = prefix;
					break;
				}
			}

			if(len == 0)
			{
				if(prefix != "") pre.push_back(prefix);
				prefix = "";
				temp = v[i];
			}
		}

		if(prefix != "") pre.push_back(prefix);

		if(!pre.empty())
        {
            vector<string> v1;
            for(int i = 0; i < pre.size(); ++i)
            {
                //cout<<"Prefix is "<<pre[i]<<endl;
                vector<string> v2;
                string add = findNext();
                v1.push_back(pre[i] + add);
                for(int j = 0; j < v.size(); ++j)
                {
                    size_t ind = v[j].find(pre[i]);
                    if(ind != string::npos)
                    {
                        if(v[j] == pre[i]) v2.push_back("%");
                        else v2.push_back(v[j].substr(pre[i].length()));
                        v[j] = "@";
                    }
                }
                finalGrammar[add] = v2;
                //cout<<"Add"<<endl<<add<<" -> ";
                //for(int k = 0; k < v2.size(); ++k) cout<<v2[k]<<" ";
                //cout<<endl;
            }

            for(int i = 0; i < v.size(); ++i) if(v[i] != "@") v1.push_back(v[i]);
            finalGrammar[it->first] = v1;
        }

	}

}

int main()
{
	freopen("Input_ND_To_D.txt", "r", stdin);

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

	cout<<"The Non Deterministic grammar is : "<<endl;
	printGrammar(grammar);
	cout<<"--------------------------------------------"<<endl;

	leftFactoring();

    cout<<"The Deterministic grammar is : "<<endl;
	printGrammar(finalGrammar);
	cout<<"--------------------------------------------"<<endl;
    cout<<"NOTE : % denotes epsilon"<<endl;

	return 0;
}
