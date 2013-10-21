/*
ID: sangobl1
PROG: butter
LANG: C++
*/

#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const int nN = 500;
const int nP = 800, nC = 1450;
const int nLimit = 225*1450;


int N, P, C;
int path[nP+1][nP+1];
int vertex[nN+1];
int min_ = INT_MAX;
//int dist[nP+1][nP+1];

typedef pair<int, int> NT;

class CComp
{
public:
	bool operator() (const NT& left, const NT& right)
	{
		return left.second>right.second;
	}
};


int main()
{
	ifstream in("butter.in");
	ofstream out("butter.out");
	in >> N >> P >> C;
	for (int i = 1; i <= N; ++ i)
	{
		in >> vertex[i];
	}

	for (int i = 1; i <= P; ++ i)
	{
		for (int j = 1; j <= P; ++ j)
		{
			path[i][j] = nLimit;
			//dist[i][j] = nLimit;
		}
	}
	//for (int i = 1; i <= N; ++ i)
	//{
	//	for (int j = 1; j <= P; ++ j)
	//	{
	//		//path[i][j] = nLimit;
	//		dist[vertex[i]][j] = nLimit;
	//	}
	//}

	for (int i = 1; i <= nP; ++ i)
	{
		path[i][i] = 0;
		//dist[i][i] = 0;
	}
	int x,y;
	for (int i = 1; i <= C; ++ i)
	{
		in >> x >> y;
		in >> path[x][y];
		path[y][x] = path[x][y];
	}
	in.close();
	in.clear();
	//////////////////////////////////////////////////////////////////////////
	for (int k = 1; k <= P; ++ k )
	{
		for (int i = 1; i <= P; ++i)
			for (int j = i+1; j <= P; ++ j)
			{
				int tmp = path[i][k]+path[k][j];
				if ( tmp < path[i][j])
				{
					//path[vertex[i]][j] = tmp;
					//path[j][vertex[i]] = tmp;
					path[i][j] = tmp;
					path[j][i] = tmp;
				}
			}
	}
	//for (int i = 1; i <= N; ++ i)
	//{
	//	vector<pair<int,int> > existed;
	//	existed.reserve(P);
	//	dist[vertex[i]][vertex[i]] = 0;
	//	for (int j = 1; j <= P; ++ j)
	//		if(j != vertex[i])
	//		{
	//			existed.push_back(make_pair(j, path[vertex[i]][j]));
	//		}

	//	while (!existed.empty())
	//	{
	//		//sort(existed.begin(), existed.end(), CComp());
	//		int _min = existed[0].second, idx=0;
	//		for (int k = 1; k < existed.size(); ++ k)
	//		{
	//			if (existed[k].second < _min)
	//			{
	//				_min = existed[k].second;
	//				idx = k;
	//			}
	//		}
	//		NT fav = existed[idx];
	//		dist[vertex[i]][fav.first] = fav.second;
	//		//dist[fav][]
	//		existed.erase(existed.begin()+idx);
	//		for (int k = 0; k < existed.size(); ++ k)
	//		{
	//			/*if (dist[vertex[i]][fav.first]+path[fav.first][existed[k].first]<
	//				dist[vertex[i]][existed[k].first])
	//			{
	//				existed[k].second =  dist[vertex[i]][fav.first]+
	//					path[fav.first][existed[k].first];
	//			}*/
	//			if (path[fav.first][existed[k].first] < nLimit)
	//			{
	//				if (dist[vertex[i]][fav.first]+path[fav.first][existed[k].first]<
	//					dist[vertex[i]][existed[k].first])
	//				{
	//					existed[k].second =  dist[vertex[i]][fav.first]+
	//						path[fav.first][existed[k].first];
	//				}
	//			}
	//		}
	//	}
	//}

	for (int i = 1; i <= P; ++ i)
	{
		int sum = 0;
		for (int j = 1; j <= N; ++ j)
		{
			sum += path[vertex[j]][i];
		}
		//sum = accumulate(path[vertex[i]]+1, path[vertex[i]]+P+1, 0);
		if (sum < min_ )
		{
			min_ = sum;
		}
	}
	out << min_ << endl;
	out.close();
	out.clear();
	return EXIT_SUCCESS;
}