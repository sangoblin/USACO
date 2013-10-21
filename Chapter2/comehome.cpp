/*
ID: sangobl1
PROG: comehome
LANG: C++
*/

#include <fstream>
#include <queue> //dijkstra
#include <algorithm>
#include <cctype>
using namespace std;

class CSol
{
public:
	int idx, length;
	friend bool operator < (const CSol& left, const CSol& right)
	{
		if (left.length < right.length)
			return true;
		else
			return false;
	}
	friend bool operator > (const CSol& left, const CSol& right)
	{
		if (left.length > right.length)
			return true;
		else
			return false;
	}
	CSol(int i, int l) : idx(i), length(l) {}
};

const int nN = 52;
int conn[nN+1][nN+1];
int ans[nN+1];
bool visited[nN+1];

int main()
{
	int P;
	ifstream in ("comehome.in");
	ofstream out ("comehome.out");
	in >> P;

	for(int i = 1; i <= nN; i ++)
		for (int j = 1; j <= nN; j ++)
			conn[i][j] = -1;

	for (int i = 1; i <= nN; i ++)
	{
		conn[i][i] = 0;
	}
	

	for (int i = 0; i < P; i ++)
	{
		char tmpa, tmpb;
		int tmp, former, latter;
		in >> tmpa >> tmpb >> tmp;
		if (isupper(tmpa))
		{
			former = tmpa-'A'+1;
		}
		else if (islower (tmpa))
		{
			former = tmpa-'a'+27;
		}

		if (isupper(tmpb))
		{
			latter = tmpb-'A'+1;
		}
		else if (islower (tmpb))
		{
			latter = tmpb-'a'+27;
		}
		
		if(conn[former][latter] == -1)
		{
			conn[former][latter] = tmp;
			conn[latter][former] = tmp;
		}
		else if (conn[former][latter] > tmp)
		{
			conn[former][latter] = tmp;
			conn[latter][former] = tmp;
		}
		
	}
	in.close();
	priority_queue<CSol, vector<CSol>, greater<CSol> > dijk;
	int _min, idx;
	_min = nN*1000;
	dijk.push(CSol('Z'-'A'+1, 0));
	//visited['Z'-'A'+1] = true;
	for(int i = 1; i <= nN; i ++)
		ans[i] = _min;
	//ans['Z'-'A'+1] = 0;
	/*for(int i = 1; i <= nN; i ++)
	{
		dijk.push(CSol(i, ans[i]));
	}*/
	while(!dijk.empty())
	{
		CSol ctmp = dijk.top();
		dijk.pop();
		if(!visited[ctmp.idx]) //可能会多次pop
		{
			visited[ctmp.idx] = true;
			ans[ctmp.idx] = ctmp.length;
		}

		for (int i = 1; i <= nN; i ++)
		{
			if (!visited[i] && conn[i][ctmp.idx]!=-1)
			{
				if(ans[ctmp.idx]+conn[i][ctmp.idx] < ans[i])
					dijk.push(CSol(i, ans[ctmp.idx]+conn[i][ctmp.idx]));
			}
		}
		//sort (dijk.front(), );
	}
	

	for (int i = 1; i < nN/2; i ++)
	{
		if (ans[i]!=0 && ans[i]<_min)
		{
			_min = ans[i];
			idx = i;
		}
	}
	out << char('A'+idx-1) << ' ' << _min << endl;
	out.close();
	return 0;
}