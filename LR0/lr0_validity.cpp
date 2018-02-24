#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<string,string> > > full;
vector<pair<string,string> > grammar;
vector<pair<string,string> > box;
pair<string,string> line;
vector<vector<pair<string,string> > >::iterator fullit;
vector<pair<string,string> >::iterator grammarit;
vector<pair<string,string> >::iterator boxit;

vector<char> visited;
string dot = ".";
void print_grammar()
{
        for(grammarit=grammar.begin();grammarit!=grammar.end();grammarit++)
        {
            cout << grammarit->first << "->";
            cout << grammarit->second << endl;
        }
}
/*bool isEqual(const pair<string, string>& element)
{
    return element.first ==  boxit->second;
}*/
int main(void)
{
    int n;
    string p[100];
    string init = "";
    FILE *fp;
    fp = freopen("input.txt","r",stdin);

    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> p[i];
    }
    fclose(fp);
    for(int i=0;i<n;i++)
    {
        line.first = p[i][0];
        line.second=p[i].substr(3);
        grammar.push_back(make_pair(line.first,line.second));
    }
    print_grammar();
   // init.insert(0,".");
    char start[10];
    string s;
    strcpy(start, p[0].c_str());
    s = start[0];
    init.insert(0,s);
    line.first = init.insert(1,"'");
    line.second = p[0][0];
    line.second.insert(0,dot);
    box.push_back(make_pair(line.first,line.second));
    for(boxit=box.begin();boxit!=box.end();boxit++)
    {
        cout << boxit->first << "->";
        cout << boxit->second << endl;
    }
   /* for(boxit=grammar.begin();grammar.size();++boxit)
    {

       // afterDot();
       grammarit = find_if(grammar.begin(),grammar.end(),isEqual);
       if(grammarit!=grammmar.end())
       {

       }
       else
       {

       }
        cout << boxit->first << "->" << boxit->second <<< endl;
    }*/

}


