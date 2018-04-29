#include<iostream>

using namespace std;

string itoa(int number)
{
    string numString = "";
    char sign;
    if(number < 0)
    {
        sign = '-';
        number*=-1;
    }
    while(number)
    {
        numString = (char)(number%10 + 48) + numString;
        number/=10;
    }
    return sign + numString;
}

int main()
{
    int a;
    cout<<"Enter your number : ";
    cin>>a;
    string s = itoa(a);
    cout<<"Converted To String : ";
    cout<<s<<endl;
    cout<<"Now pushing back \'abc\' in the string."<<endl;
	s.push_back('abc');
	cout<<s<<endl;
	cout<<"String operation performed. Hence converted into string."<<endl;
    return 0;
}
