/*
ID: sangobl1
PROG: fence
LANG: C++
*/
#include <fstream>
#include <cassert>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

const int nF = 1024;
const int nN = 500;


//class CEdge
//{
//public:
//	int i, j;
//};

int F;
int degree[nN+1]; //degrees of the node
int path[nF+1];
vector<int> nodes[nN+1];
stack<int> lnodes;
vector<int> rubbish;
int first, cur = 0;
int maxn, min_ = INT_MAX;
int lastnot;

void setPath(int, int);

int main()
{
	ifstream in("fence.in");
	ofstream out("fence.out");
	assert (in!=NULL && out!=NULL);
	in >> F;

	for (int i = 1; i <= F; ++ i)
	{
		//CEdge tmp;
		int tmpi, tmpj;
		in >> tmpi >> tmpj;
		nodes[tmpi].push_back(tmpj);
		nodes[tmpj].push_back(tmpi);
		++ degree[tmpi];
		++ degree[tmpj];
		if (tmpi > maxn)
			maxn = tmpi;
		if (tmpj > maxn)
			maxn = tmpj;
		if (min_ > tmpi)
			min_ = tmpi;
		if (min_ > tmpj)
			min_ = tmpj;
	}
	in.close();
	/*for (int i = maxn; i >= 1; -- i)
	{
		if (degree[i]%2 == 1)
		{
			first = i;
			break;
		}
	}*/
	for (int i = min_; i <= maxn; ++i)
	{
		if (degree[i]%2 == 1)
		{
			first = i;
			break;
		}
	}
	first = (first == 0) ?  min_:first;
	for (int i = min_; i <= maxn; ++ i)
	{
		if (degree[i] != 0)
		{
			sort(nodes[i].begin(), nodes[i].end());
		}
	}
	//path[cur++] = first;
	//lastnot = F;
	setPath(cur, first);
	for (int i = F; i >= 0; -- i)
	{
		out << path[i] << endl;
	}
	out.close();
	out.clear();
	return 0;
}

void setPath(int cur, int node/*, int eff*/)
{
	if (cur > F)
		return;
	if (degree[node] == 0)
	{
		path[cur] = node;
		++ cur;
		if (cur > F)
			return;
		else
		{
			int j = lnodes.top();
			lnodes.pop();
			setPath(cur, j);
		}
	}
	else
	{
		int j = *nodes[node].begin();
		-- degree[node];
		-- degree[j];
		nodes[node].erase(nodes[node].begin());
		nodes[j].erase(find(nodes[j].begin(), nodes[j].end(), node));
		lnodes.push(node);
		setPath(cur, j);
	}
	//int nodeend, index1, index = 0, index2 = 0, index_;
	////int eff;
	//if (!nodes[node].empty())
	//{
	//	nodeend = *nodes[node].begin();
	//	//eff = cur;
	//}
	//else
	//{
	//	rubbish.clear();
	//	for (int i = min_; i <= maxn; ++ i)
	//	{
	//		if (degree[i] != 0)
	//		{
	//			//index1 = i;
	//			//break;
	//			rubbish.push_back(i);
	//		}
	//	}
	//	//sort(rubbish.begin(), rubbish.end());
	//	//rubbish.erase(unique(rubbish.begin(), rubbish.end()), rubbish.end());
	//	for (int j = rubbish.size()-1; j >= 0; -- j)
	//	{
	//		for (int i = 0; i <= nF; ++ i)
	//		{
	//			if (path[i] == rubbish[j])
	//			{
	//				index = i;
	//				index_ = rubbish[j];
	//				break;
	//			}
	//		}
	//		if (index > index2)
	//		{
	//			index2 = index;
	//			index1 = index_;
	//		}
	//	}
	//	for (int j = cur-1; j >= index2; -- j )
	//		path[j+(lastnot-cur+1)] = path[j];

	//	lastnot = index2+lastnot-cur-1;
	//	
	//	node = index1;
	//	nodeend = *nodes[index1].begin();
	//	cur = index2;
	//}
	//-- degree[node];
	//-- degree[nodeend];
	//nodes[node].erase(nodes[node].begin());
	//nodes[nodeend].erase(find(nodes[nodeend].begin(), nodes[nodeend].end(), node));
	//path[cur++] = nodeend;
	//++ eff;
	//setPath(cur, nodeend, eff);
}