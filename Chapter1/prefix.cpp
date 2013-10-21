/*
ID: sangobl1
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cassert>
using namespace std;

const int num = 10;
vector<string> primitives[num];
vector<string> primitives_all;
string ques;
int* ans;

bool less_(const string& left, const string& right)
{
	if(left.length() < right.length())
		return true;
	else
		return false;
}

int main()
{
	ifstream in ("prefix.in");
	assert(in != NULL);
	string maintmp;
	in >> maintmp;
	while(maintmp != ".")
	{
		primitives[maintmp.length()-1].push_back(maintmp);
		in >> maintmp;
	}
	//sort(primitives.begin(), primitives.end(), less_);
	//unsigned minl = primitives.begin()->length(), maxl = (primitives.end()-1)->length();
	for (int i = 0; i < num; i ++)
	{
		if(primitives[i].size() != 0)
			primitives_all.insert(primitives_all.end(), primitives[i].begin(), primitives[i].end());
	}
	unsigned minl = primitives_all.begin()->length(), maxl = (--primitives_all.end())->length();

	char mnBuffer[80];
	in.getline(mnBuffer, 80);
	do 
	{
		in.getline(mnBuffer, 80);
		ques += mnBuffer;
	} while (mnBuffer[0] != '\0');
	ans = new int[ques.length()+1];
	unsigned qlen = ques.length();
	memset(ans, 0, (qlen+1)*sizeof(int));
	/*for(int i = 1; i < minl; i ++)
		ans[i] = 0;*/
	in.close();
	for (int i = minl; i <= maxl; i ++)
	{
		/*for(vector<string>::iterator iter = primitives[i-1].begin(); iter != primitives[i-1].end(); iter ++)
		{
			if (*iter == ques.substr(0, i))
			{
				ans[i] = i;
				break;
			}
		}
		if (ans[i] == 0)
		{
			ans[i] = ans[i-1]; //ensure that the latter is always bigger than the former
		}*/
		ans[i] = ans[i-1];
		for (int j = i-1; j >= 0; j --)
		{
			//if(ques.substr(ans[j], ))
			for(vector<string>::iterator iter = primitives[i-ans[j]-1].begin(); iter != primitives[i-ans[j]-1].end(); iter ++)
				if (*iter == ques.substr(ans[j], i-ans[j]))
				{
					ans[i] = i;
					break;
				}
				if (ans[i] == i)
				{
					break;
				}	
		}
	}
	for (int i = maxl+1; i <= ques.size(); i ++)
	{
		ans[i] = ans[i-1];
		for (int j = i-1; i-ans[j] <= maxl; j --)
		{
			//if(ques.substr(ans[j], ))
			for(vector<string>::iterator iter = primitives[i-ans[j]-1].begin(); iter != primitives[i-ans[j]-1].end(); iter ++)
				if (*iter == ques.substr(ans[j], i-ans[j]))
				{
					ans[i] = i;
					break;
				}
			if (ans[i] == i)
			{
				break;
			}	
		}
	}
	ofstream out("prefix.out");
	out << ans[ques.size()] << endl;
	delete[] ans;
	out.close();
	return 0;
}