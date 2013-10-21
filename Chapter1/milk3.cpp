/*
ID: sangobl1
PROG: milk3
LANG: C++
*/
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class CMilk
{
public:
	int A, B, C;
	CMilk()
	{}
	CMilk(int a, int b, int c)
	{
		A = a;
		B = b;
		C = c;
	}
	CMilk(const CMilk& cmil)
	{
		A = cmil.A;
		B = cmil.B;
		C = cmil.C;
	}
	void setValue(int a, int b, int c)
	{
		A = a;
		B = b;
		C = c;
	}
	bool operator == (const CMilk& cm)
	{
		if(A == cm.A && B == cm.B && C == cm.C)
			return true;
		return false;
	}
	void operator = (const CMilk& cmil)
	{
		A = cmil.A;
		B = cmil.B;
		C = cmil.C;
	}
};

bool isInvis(CMilk&, vector<CMilk>&);

int main()
{
	ifstream in("milk3.in");
	ofstream out("milk3.out");
	int A,B,C;
	vector<int> answer;
	vector<CMilk> visited;
	queue<CMilk> nodes;
	in >> A >> B >> C;
	CMilk ini(0, 0, C);
	nodes.push(ini);
	/*int min3 = min(min(A, B), C);
	int max3 = max(max(A, B), C);
	answer.push_back(C);
	if(C == min3)
	{
		answer.push_back(0);
		//answer.push_back(C);
	}
	else if(A == min3)
	{
		if(C > B)
		{
			int tmp = C - B;
			while(tmp < C)
			{
				answer.push_back(tmp);
				tmp += A;
			}
			tmp = C - A;
			while(tmp > C-B)
			{
				answer.push_back(tmp);
				tmp -= A;
			}
		}
		else
		{

		}
	}*/
	while(!nodes.empty())
	{
		CMilk tmp = nodes.front();
		CMilk _tmp(tmp);
		nodes.pop();
		visited.push_back(tmp);
		//从A开始查看
		if(tmp.A == 0)
			answer.push_back(tmp.C);

		if(tmp.A != 0)
		{
			if((tmp.A + tmp.B) <= B)
			{				
				tmp.B = tmp.A + tmp.B;
				tmp.A = 0;
			}
			else
			{
				tmp.A -= (B-tmp.B);
				tmp.B = B;
			}		//将A倒入B
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
			tmp = _tmp;
			if((tmp.A + tmp.C) <= C)
			{
				tmp.C = tmp.A + tmp.C;
				tmp.A = 0;	
			}
			else
			{
				tmp.A -= (C-tmp.C);
				tmp.C = C;
			}		//将A倒入C
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
		} //
		tmp = _tmp;
		if(tmp.B != 0)
		{
			if((tmp.A + tmp.B) <= A)
			{
				tmp.A = tmp.A + tmp.B;
				tmp.B = 0;		
			}
			else
			{
				tmp.B -= (A-tmp.A);
				tmp.A = A;
			}		//将B倒入A
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
			tmp = _tmp;
			if((tmp.B + tmp.C) <= C)
			{
				tmp.C = tmp.B + tmp.C;
				tmp.B = 0;		
			}
			else
			{
				tmp.B -= (C-tmp.C);
				tmp.C = C;
			}		//将B倒入C
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
		} //
		tmp = _tmp;
		if(tmp.C != 0)
		{
			if((tmp.A + tmp.C) <= A)
			{
				tmp.A = tmp.A + tmp.C;
				tmp.C = 0;
			}
			else
			{
				tmp.C -= (A-tmp.A);
				tmp.A = A;
			}		//将C倒入A
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
			tmp = _tmp;
			if((tmp.B + tmp.C) <= B)
			{
				tmp.B = tmp.B + tmp.C;
				tmp.C = 0;
			}
			else
			{
				tmp.C -= (B-tmp.B);
				tmp.B = B;
			}		//将C倒入B
			if(!isInvis(tmp, visited))
				nodes.push(tmp);
		} //

	} // while
	sort(answer.begin(), answer.end());
	answer.erase(unique(answer.begin(), answer.end()), answer.end());
	for(int i = 0; i <= answer.size()-2; i ++)
		out << answer[i] << ' ';
	out << answer[answer.size()-1] << endl;
	return 0;
}

bool isInvis(CMilk& cm, vector<CMilk>& cv)
{
	vector<CMilk>::iterator cmit;
	for(cmit = cv.begin(); cmit != cv.end(); cmit ++)
	{
		if(*cmit == cm)
			return true;
	}
	return false;
}