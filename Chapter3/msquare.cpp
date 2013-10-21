/*
ID: sangobl1
PROG: msquare
LANG: C++
*/

#include <fstream>
#include <string>
//#include <iostream>
#include <queue>
//#include <vector>
#include <utility>
//#include <algorithm>
//#include <map>
using namespace std;
//using namespace rel_ops;

const int nR = 2;
const int nC = 4;
const int nL = 60;
const int SIZE = nR*nC;
const int factory[SIZE] = {5040, 720, 120, 24, 6, 2, 1};
const int index[] = {1e7, 1e6, 1e5, 1e4, 1e3, 1e2, 1e1, 1e0};
//const int *a = factory;
const int SSIZE = 40320;


//factory[0] = 1;


class CSol
{
public:
	enum MOVE {A, B, C};
	static const string moveStr[];
	int converted;
	string method;
	int ms[SIZE];
	void setMove(MOVE);
	
	CSol(int (&a)[SIZE]) : converted(0)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			ms[i] = a[i];
			converted += ms[i]*index[i];
		}
		
	}
	CSol() {}

	CSol(const CSol& sol)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			ms[i] = sol.ms[i];
			//converted += ms[i]*index[i];
		}
		this->converted = sol.converted;
		this->method = sol.method;
	}

	friend bool operator == (const CSol& left, const CSol& right)
	{
		if (left.converted != right.converted)
			return false;
		else
			return true;
	}
	friend int calIdx(const CSol&);
};

const string CSol::moveStr[] = {"A", "B", "C"};

void CSol::setMove(MOVE m)
{
	switch (m)
	{
	case A:
		for (int i = 0; i < nC; ++i)
		{
			ms[i] ^= ms[SIZE-1-i];
			ms[SIZE-1-i] ^= ms[i];
			ms[i] ^= ms[SIZE-1-i];
		}
		method += moveStr[A];
		break;
	case B:
		{
			int tmp1 = ms[3], tmp2 = ms[4];
			for (int i = 3; i >= 1; -- i)
				ms[i] = ms[i-1];
			ms[0] = tmp1;
			for (int i = 4; i <= 6; ++ i)
				ms[i] = ms[i+1];
			ms[7] = tmp2;
		}
		method += moveStr[B];
		break;
	case C:
		{
			int tmp = ms[6];
			ms[6] = ms[5];
			ms[5] = ms[2];
			ms[2] = ms[1];
			ms[1] = tmp;
		}
		method += moveStr[C];
		break;
	}
	converted = 0;
	for (int i = 0; i < SIZE; ++ i)
	{
		converted += ms[i]*index[i];
	}
}

//////////////////////////////////////////////////////////////////////////
int calIdx(const CSol& sol)
{
	int _count[SIZE-1] = {0};
	int res = 0;
	for (int i = 0; i < SIZE-1; ++ i)
	{
		for (int j = i+1; j < SIZE; ++ j)
		{
			if (sol.ms[j] < sol.ms[i])
				++ _count[i];
		}
		res += _count[i]*factory[i];
	}
	 return res;
}

queue<CSol> cand;
int init[] = {1,2,3,4,5,6,7,8};
bool state[SSIZE+1];
int res[SIZE];
bool _find = false;
string answer;
CSol sinit(init);

int main()
{
	ifstream in("msquare.in");
	ofstream out("msquare.out");
	for (int i = 0; i < SIZE; ++ i)
		in >> res[i];
	CSol final(res);
	if (final == sinit)
	{
		_find = true;
		answer = "";
	}
	else
	{
		cand.push(sinit);
		state[calIdx(sinit)] = true;
	}

	while (!cand.empty())
	{
		CSol tmp = cand.front();
		cand.pop();

		for (int i = CSol::A; i <= CSol::C; ++ i)
		{
			CSol tmp_ = tmp;
			tmp_.setMove(CSol::MOVE(i));
			
			if (!state[calIdx(tmp_)])
			{
				state[calIdx(tmp_)] = true;
				if (tmp_ == final)
				{
					answer = tmp_.method;
					_find = true;
					break;
				}
				cand.push(tmp_);
			}			
		}

		if (_find)
			break;
	}

	string::size_type n = answer.size();
	out << n << endl;
	int _i;
	for ( _i = 0; _i < n/nL; ++ _i )
		out << answer.substr(nL*_i, nL) << endl;
	out << answer.substr(nL*_i, n%nL) << endl;
	return EXIT_SUCCESS;
}

