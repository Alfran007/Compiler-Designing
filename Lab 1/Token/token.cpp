#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<endl
using namespace std;

int main()
{
	freopen("input_token.txt","r",stdin);
	char c;
	bool isIden=false,isNumber=false,isOperator=false,isString=false;
	long count=0;
	const string operators="+-*/=><!&|%^?:",term=",;(){}";
	while(cin.get(c)){
		if(c=='\\'&&isString)
		{
		cerr<<"back";
			cin.get(c);
			continue;
		}
		else if(c=='\"')
		{
		cerr<<"quote";
			if(isString)
			{
				isString=false;
			}
			else
			{
				count++;
				isString=true;
			}
		}
		else if(isString)
		{
		debug(count);
		debug(c);
			continue;
		}
		else if(isalpha(c)||c=='_')
		{
			cerr<<"alpha";
			if(!isIden)
			{
				count++;
				isIden=true;
			}
		}
		else if(isdigit(c))
		{
		cerr<<"digi";
			if((!isNumber&&!isIden)||c=='.')
			{
				count++;
				isNumber=true;
			}
		}
		else if(isblank(c))
		{
		cerr<<"blank";
			isIden=isNumber=isOperator=isString=false;
		}
		else if(operators.find(c)!=string::npos)
		{
		cerr<<"opera";
			if(!isOperator)
			{
				count++;
				isIden=isNumber=isOperator=isString=false;
				isOperator=true;
			}
		}
		else if(term.find(c)!=string::npos)
		{
		cerr<<"term";
			count++;
			isIden=isNumber=isOperator=isString=false;
		}
		debug(count);
		debug(c);
	}
	cout<<count<<endl;
	return 0;
}
