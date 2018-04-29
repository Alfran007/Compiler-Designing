#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <stack>
using namespace std;

map<string, vector<string> > grammar;
map<string, vector<string> >::iterator it_mv;

vector<string> v;
set<char> opList;

void printGrammar(map<string, vector<string> > grammar)
{
	string str;
	for(it_mv = grammar.begin(); it_mv != grammar.end(); ++it_mv)
	{
		str = it_mv->first;
		cout<<str<<" -> ";

		v = it_mv->second;
		for(int i = 0; i < v.size(); ++i)
		{
			if(i != 0) cout<<" | ";
			cout<<v[i];
		}

		cout<<endl;
	}
}

bool checkOpGr()
{
	for(it_mv = grammar.begin(); it_mv != grammar.end(); ++it_mv)
	{
		v = it_mv->second;

		for(int i = 0; i < v.size(); ++i)
		{
			if(v[i].length() % 2 == 0) return false;
			bool op = true, exp = false;
			for(int j = 0; j < v[i].length(); ++j)
			{
				if(v[i][j] == '#') return false;

				op = !op;
				exp = !exp;
				//cout<<"op -> "<<op<<" epx -> "<<exp<<" : ch -> "<<v[i][j]<<endl;
				if(op && !(v[i][j] == '+' || v[i][j] == '-' || v[i][j] == '*' || v[i][j] == '/' || v[i][j] == '^')) return false;
				else if(exp && (v[i][j] == '+' || v[i][j] == '-' || v[i][j] == '*' || v[i][j] == '/' || v[i][j] == '^')) return false;
				opList.insert(v[i][j]);
			}
		}
	}

	return true;
}

bool isOp(char ch)
{
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') return true;
	else return false;
}

char checkPre(char t, char i)
{
	if(t == '+' && (i == '+' || i == '-')) return '>';
	else if(t == '-' && (i == '-' || i == '+')) return '>';
	else if(t == '*' && (i == '+' || i == '-' || i == '*')) return '>';
	else if(t == '/' && (i == '+' || i == '-' || i == '*' || i == '/')) return '>';
	else if(t == '^' && i != '^') return '>';												//Exponential is Right Associative
	return '<';
}

bool checkList(char ch)
{
	if(opList.find(ch) == opList.end()) return false;
	return true;
}

bool parsing(char ch, stack<string> &par)
{
    string str;
    if(isOp(ch))
    {
        if(par.size() < 2) return false;

        string a = par.top();
        par.pop();
        string b = par.top();
        par.pop();

        str = b + ch + a;
    }
    else
    {
        str = string(1, ch);
    }

    for(it_mv = grammar.begin(); it_mv != grammar.end(); ++it_mv)
    {
        string key = it_mv->first;
        v = it_mv->second;
        for(int i = 0; i < v.size(); ++i)
        {
            if(str == v[i])
            {
                par.push(key);
                cout<<" and pushing "<<key<<" as "<<key<<" -> "<<str<<endl;
                return true;
            }
        }
    }

    par.push(str);
    cout<<" and pushing "<<str<<endl;
    return true;
}

bool bup(string in)
{
	stack<char> st;
	stack<string> par;
	st.push('$');

	int ind = 0;
	while(!(st.top() == '$' && in[ind] == '$'))
	{
		if(in[ind] != '$' && !checkList(in[ind]))
		{
			cout<<in[ind]<<" is not valid input"<<endl;
			return false;
		}
		cout<<endl<<"Stack Top : "<<st.top()<<", Look Ahead Symbol : "<<in[ind]<<". "<<endl<<"So ";
		/*
		if(st.top() == in[ind])
		{
			cout<<"Reducing "<<st.top()<<" from Stack"<<endl;
			st.pop();
			ind++;
			continue;
		}
		*/
		if(st.top() == '$')
		{
			st.push(in[ind++]);
			cout<<"Shifting "<<st.top()<<" in Stack"<<endl;
			continue;
		}
		if(in[ind] == '$')
		{
			cout<<"Reducing "<<st.top()<<" from Stack";
			if(!parsing(st.top(), par))
            {
                cout<<"Error In Parsing"<<endl;
                return false;
            }
			st.pop();
			continue;
		}
		if(!isOp(st.top()) && isOp(in[ind]))
		{
			cout<<"Reducing "<<st.top()<<" from Stack";
			if(!parsing(st.top(), par))
            {
                cout<<"Error In Parsing"<<endl;
                return false;
            }
			st.pop();
			continue;
		}
		else if(isOp(st.top()) && !isOp(in[ind]))
		{
			st.push(in[ind++]);
			cout<<"Shifting "<<st.top()<<" in Stack"<<endl;
			continue;
		}
		else if(isOp(st.top()) && isOp(in[ind]))
		{
			if(checkPre(st.top(), in[ind]) == '<')
			{
				st.push(in[ind++]);
				cout<<"Shifting "<<st.top()<<" in Stack"<<endl;
			}
			else
			{
				cout<<"Reducing "<<st.top()<<" from Stack";
				if(!parsing(st.top(), par))
                {
                    cout<<"Error In Parsing"<<endl;
                    return false;
                }
				st.pop();
			}
			continue;
		}
		else                                                        //Both are identifiers, Therefore error
        {
            cout<<"Error In Parsing"<<endl;
            return false;
        }
	}
    if(par.top() == "E")
	return true;
	else return false;
}

int main()
{
	freopen("Input_Bottom_Up_Parser5.txt", "r", stdin);

	string str, input;
	size_t ind;

	getline(cin, input);
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

	if(checkOpGr())
	{
		cout<<"Grammar is Operator Grammar"<<endl;
		cout<<"--------------------------------------------"<<endl;
		cout<<"Input String : "<<input<<endl;
		cout<<"Bottom Up Parser :-"<<endl;
		if(bup(input))
        {
            cout<<"--------------------------------------------"<<endl;
            cout<<"Input String is Accepted"<<endl;
        }
		else cout<<"Input String is Not Accepted"<<endl;
	}
	else cout<<"Grammar is not Operator Grammar"<<endl;
	cout<<"--------------------------------------------"<<endl;

	return 0;
}
