/*
ID: sangobl1
PROG: camelot
LANG: C++
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
//#include <cmath>
//#include <cstdlib>
#include <string.h>
#include <algorithm>
//#include <cctype>
using namespace std;

typedef pair<int, int> NT;

const int nR = 30, nC = 26;
const NT MOVES[] = {make_pair(-1, -2), make_pair(-2, -1), make_pair(-2, 1), make_pair(-1, 2), make_pair(1, 2),
make_pair(2, 1), make_pair(2, -1), make_pair(1, -2)};

const NT MOVEK[] = {make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), make_pair(0, 1), make_pair(1, 1),
make_pair(1, 0), make_pair(1, -1), make_pair(0, -1)};

int R,C;

int boardmin[nR+1][nC+1][nR+1][nC+1];
int boardtmp[nR+1][nC+1];
bool board_[nR+1][nC+1];
pair<int, int> king;
vector<pair<int, int> > knights;
vector<pair<int, int> > kValues; 
queue<pair<int, int> > queues;
int count_ = INT_MAX;
//int ans;

//int abs(int a)
//{
//	if (a >= 0)
//		return a;
//	else
//		return -a;
//}

class OSame
{
public:
	bool operator() (pair<int, int>& left, pair<int, int> right)
	{
		if (left.first==right.first && left.second==right.second)
			return true;
		else
			return false;
	}
};

int main()
{
	ifstream in("camelot.in");
	ofstream out("camelot.out");
	assert (in!=NULL && out!=NULL);
	in >> R >> C;
	knights.clear();
	kValues.clear();
	char tmp__;
	in >> tmp__ >> king.first;
	king.second = tmp__-'A'+1;


	//memset(boardtmp, 0, (nR+1)*(nC+1)*sizeof(int));
	//memset(boardmin, 0, (nR+1)*(nC+1)*sizeof(int));

	while (!in.eof())
	{
		char ctmp;
		int itmp;
		in >> ctmp >> itmp;
		if (ctmp >= 'A' && ctmp <= 'Z' && itmp>=1 && itmp<= R)
		{
			knights.push_back(make_pair(itmp, ctmp-'A'+1));
		}
	}
	in.close();
	in.clear();
	knights.erase(unique(knights.begin(), knights.end(), OSame()), knights.end());

	for (int i = 1; i <= R; ++ i)
		for (int j = 1; j <= C; ++ j)
			for (int i_ = 1; i_ <= R; ++ i_)
				for (int j_ = 1; j_ <= C; ++ j_)
					boardmin[i][j][i_][j_] = -1;

	for (int i = 1; i <= R; ++ i)
		for (int j = 1; j <= C; ++ j)
	{
		//int x = 0, y = 0;
		memset(board_, 0, (nR+1)*(nC+1)*sizeof(bool));
		int x = i, y = j;
		board_[x][y] = true;
		boardmin[i][j][x][y] = 0;
		queues.push(make_pair(x, y));
		
		while (!queues.empty())
		{
			NT ptmp = queues.front();
			queues.pop();
			x = ptmp.first, y = ptmp.second;

			for (int k = 0; k < sizeof MOVES/sizeof(NT); ++ k)
			{
				int dx = MOVES[k].first, dy = MOVES[k].second;
				if (x+dx<1 || x+dx>R || y+dy<1 || y+dy>C )
					continue;
				else if (board_[x+dx][y+dy])
					continue;
				else
				{
					board_[x+dx][y+dy] = true;
					boardmin[i][j][x+dx][y+dy] = boardmin[i][j][x][y]+1;
					queues.push(make_pair(x+dx, y+dy));
				}
			}//for
		}// while
	}// for 

	{
		memset(board_, 0, (nR+1)*(nC+1)*sizeof(bool));
		int x = king.first, y = king.second;
		board_[x][y] = true;
		boardtmp[x][y] = 0;
		queues.push(make_pair(x, y));
		
		while (!queues.empty())
		{
			NT ptmp = queues.front();
			queues.pop();
			x = ptmp.first, y = ptmp.second;
			//current = 

			for (int j = 0; j < sizeof MOVEK/sizeof(NT); ++ j)
			{
				int dx = MOVEK[j].first, dy = MOVEK[j].second;
				if (x+dx<1 || x+dx>R || y+dy<1 || y+dy>C )
					continue;
				else if (board_[x+dx][y+dy])
					continue;
				else
				{
					board_[x+dx][y+dy] = true;
					boardtmp[x+dx][y+dy] = boardtmp[x][y]+1;
					queues.push(make_pair(x+dx, y+dy));
				}
			}//for
		}// while
	}

	kValues.push_back(king);
	{
		int x = king.first, y = king.second;
		for (int k = 1; k <= 2; ++ k)
			for (int i = 0; i < sizeof MOVEK/sizeof(NT); ++ i)
			{
				int dx = MOVEK[i].first*k, dy = MOVEK[i].second*k;
				if (x+dx<1 || x+dx>R || y+dy<1 || y+dy>C )
					continue;
				else
				{
					kValues.push_back(make_pair(x+dx, y+dy));
				}
			}
		for (int k = 3; k <= nC; ++ k) //after the third layor, we only need to record the points on 
			for (int i = 0; i < sizeof MOVEK/sizeof(NT); i += 2)//the digonal
			{
				int dx = MOVEK[i].first*k, dy = MOVEK[i].second*k;
				if (x+dx<1 || x+dx>R || y+dy<1 || y+dy>C )
					continue;
				else
				{
					kValues.push_back(make_pair(x+dx, y+dy));
				}
			}
	}

	for (int i = 1; i <= R; ++ i)
		for (int j = 1; j <= C; ++ j)
		{

				
				///*if (index__ != -1)
				//{
				//	 ans_ = ans-boardtmp[xk][yk]+boardtmp[i][j];
				//	ans_ -= boardmin[xk][yk][i][j];
				//	ans_ -= boardmin[knights[index__].first][knights[index__].second][xk][yk];
				//	ans_ += boardmin[knights[index__].first][knights[index__].second][i][j];
				//}
				//else
				//{
				//	ans_ = INT_MAX;
				//}*/

			int ans_ = boardtmp[i][j];
			for (int z = 0; z < knights.size(); ++ z)
			{
				int kx = knights[z].first, ky = knights[z].second;
				if (boardmin[kx][ky][i][j] == -1)
				{
					ans_ = INT_MAX;
					break;
				}

				ans_ += boardmin[kx][ky][i][j];
			}


			int min__ = INT_MAX, index__ = -1;
			bool meet = false, pick = false;
			for (int k = 0; k < kValues.size(); ++ k)
			{
				min__ = INT_MAX;
				int ans;
				ans = 0;
				index__ = -1;
				int xk = kValues[k].first, yk = kValues[k].second;
				//int dx3 = abs(i-xk), dy3 = abs(j-yk);
				ans += boardtmp[xk][yk];
				//ans += boardmin[dx3][dy3];
				if (boardmin[xk][yk][i][j] == -1)
					break;
				ans += boardmin[xk][yk][i][j];
				
				for (int z = 0; z < knights.size(); ++ z)
				{
					int kx = knights[z].first, ky = knights[z].second;
					//int dx1 = abs(kx-xk), dy1 = abs(ky-yk);
					//int dx2 = abs(kx-i), dy2 = abs(ky-j);

					//ans += boardmin[dx2][dy2];
					if (boardmin[kx][ky][xk][yk]==-1)
					{
						continue;
					}
					if (boardmin[kx][ky][i][j]==-1)
					{
						meet = true;
						break;
					}
					if (boardmin[kx][ky][xk][yk]-boardmin[kx][ky][i][j] < min__)
					{
						min__ = boardmin[kx][ky][xk][yk]-boardmin[kx][ky][i][j];
						//ans -= index__;
						//ans += min__;
						index__ = z;
					}
				}//for  z
				if (meet)
					break;

				for (int z = 0; z < knights.size(); ++ z)
				{
					int kx = knights[z].first, ky = knights[z].second;
					if (boardmin[kx][ky][i][j] == -1)
					{
						ans = INT_MAX;
						break;
					}

					if (z != index__)
						ans += boardmin[kx][ky][i][j];
					else
						ans += boardmin[kx][ky][xk][yk];
				}


				//ans = (ans>ans_)?ans_:ans;

				if (ans < count_)
				{
					count_ = ans;
				}
			}
			if (ans_ < count_)
				count_ = ans_;
		}
		out << count_ << endl;
		out.close();
		out.clear();
		return EXIT_SUCCESS;
}