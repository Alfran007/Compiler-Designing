#include<bits/stdc++.h>
using namespace std;
int main()
{
	int i,j,k;
	int temp,temp1;
	char s[100];
	int status=0,status1=0;

	FILE *fp;
	fp=fopen("keywords_fsm.txt","r");
	fscanf(fp,"%d",&temp);
	char table[temp][100];
	for(i=0;i<temp;i++)
	{
		fscanf(fp,"%s",table[i]);
	}
	fclose(fp);

	fp=fopen("input_fsm.txt","r");
	fscanf(fp,"%d",&temp1);
	for(i=0;i<temp1;i++)
	{
		fscanf(fp,"%s",s);
		status=0;
		status1=0;
		for(k=0;k<temp;k++)
		{
			for(j=0;( j<(int)strlen(s) && strlen(s)==strlen(table[k]) );j++)
			{
				if(s[j]==table[k][j])
				{
					status++;
					if(status==(int)strlen(s))
					{
						cout<<"Input "<<s<<" : matched with keyword "<<table[k]<<" with index number "<<k<<" in table."<<endl;
						status1=1;
						break;
					}
				}
				else
					break;

			}
			if(status1==1)
				break;
		}
		if(status!=(int)strlen(s))
		{
			cout<<"Input "<<s<<" : not matched with any keyword in the table."<<endl;
		}

	}

	fclose(fp);
}
