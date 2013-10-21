/*
ID: sangobl1
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

enum {FENCE, PATH, EXIT};

class CPnt
{
public:
	int x, y;
	CPnt (int i, int j) : x (i), y (j){}
	CPnt () {}
	CPnt (const CPnt& right)
	{
		this->x = right.x;
		this->y = right.y;
	}
	CPnt operator + (const CPnt& right)
	{
		CPnt res;
		res.x = this->x+right.x;
		res.y = this->y+right.y;
		return res;
	}
};

const int LIMITED = 3800;
const CPnt opr[] = {CPnt(-1,0), CPnt(1,0), CPnt(0, -1), CPnt(0,1)};

int W, H;
vector<vector<int> > maze;
vector<vector<bool> >mazeb;
CPnt exit1, exit2;
vector<vector<int> > ans;
int _max = 0;

int  main()
{
	ifstream in ("maze1.in");
	ofstream out ("maze1.out");
	assert (in != NULL && out != NULL);
	in >> W >> H;
	bool first = true;

	for (int i = 0; i < 2*H+1; i ++)
	{
		vector<int> vtmp, vtmp2;
		vector<bool> line;
		for (int j = 0; j < 2*W+1; j ++)
		{
			char tmp;
			//in >> tmp;
			in.get (tmp);
			while(tmp == '\n')
				in.get(tmp);
			
			if (tmp == '+' || tmp == '-' || tmp == '|')
			{
				vtmp.push_back(FENCE);
				vtmp2.push_back(-1);
			}
			else if (tmp == ' ' && (i == 0 || i == 2*H || j == 0 || j == 2*W))
			{
				vtmp.push_back(EXIT);
				if (first)
				{
					first = false;
					exit1.x = i;
					exit1.y = j;
				}
				else
				{
					exit2.x = i;
					exit2.y = j;
				}
				vtmp2.push_back(0);
			}
			else
			{
				vtmp.push_back(PATH);
				vtmp2.push_back(LIMITED);
			}
			line.push_back(false);
		}
		maze.push_back(vtmp);
		ans.push_back(vtmp2);
		mazeb.push_back(line);
	}
	
	in.close();
	//接下来我们从exit开始入回进行计算，将每个path处得到值
	mazeb[exit1.x][exit1.y] = true;
	mazeb[exit2.x][exit2.y] = true;
	queue<CPnt> ansq;
	//int count  = 0;
	ansq.push(exit1);
	while(!ansq.empty())
	{
		CPnt tmp = ansq.front();
		ansq.pop();
		//count ++;
		//for (int i = 1; i >= -1; i -= 2)
		//{
			//for (int j = 1; j >= -1; j -= 2)
			//{
			for(int i = 0; i < sizeof(opr)/sizeof(opr[0]); i ++)
			{
				//if (tmp.x+i<2*H+1 && tmp.x+i>=0 && tmp.y+j<2*W+1 && tmp.y+j>=0 )
				CPnt _tmp = tmp+opr[i];
				if (_tmp.x<2*H+1 && _tmp.x>=0 && _tmp.y<2*W+1 && _tmp.y>=0 )
				{
					if(!mazeb[_tmp.x][_tmp.y])
					{
						mazeb[_tmp.x][_tmp.y] = true;
						if (maze[_tmp.x][_tmp.y] == PATH)
						{
							ansq.push(_tmp);
							ans[_tmp.x][_tmp.y] = ans[tmp.x][tmp.y]+1;
						}
					}
				}
			}
			//}	
		//}//for
	}//while

	ansq.push(exit2);
	while(!ansq.empty())
	{
		CPnt tmp = ansq.front();
		ansq.pop();
		//count ++;
		/*for (int i = 1; i >= -1; i -= 2)
		{
			for (int j = 1; j >= -1; j -= 2)
			{
				if (tmp.x+i<2*H+1 && tmp.x+i>=0 && tmp.y+j<2*W+1 && tmp.y+j>=0 )
				{
					if(mazeb[tmp.x+i][tmp.y+j])
					{
						mazeb[tmp.x+i][tmp.y+j] = false;
						ansq.push(CPnt(tmp.x+i, tmp.y+j));
						if (maze[tmp.x+i][tmp.y+j] == PATH)
						{
							if(ans[tmp.x][tmp.y]+1 < ans[tmp.x+i][tmp.y+j])
								ans[tmp.x+i][tmp.y+j] = ans[tmp.x][tmp.y]+1;
						}
					}
				}
			}	
		}//for*/
		for(int i = 0; i < sizeof(opr)/sizeof(opr[0]); i ++)
		{
			//if (tmp.x+i<2*H+1 && tmp.x+i>=0 && tmp.y+j<2*W+1 && tmp.y+j>=0 )
			CPnt _tmp = tmp+opr[i];
			if(_tmp.x<2*H+1 && _tmp.x>=0 && _tmp.y<2*W+1 && _tmp.y>=0)
			{
				if(mazeb[_tmp.x][_tmp.y])
				{
					mazeb[_tmp.x][_tmp.y] = false;
					
					if (maze[_tmp.x][_tmp.y] == PATH)
					{
						ansq.push(_tmp);
						if(ans[tmp.x][tmp.y]+1 < ans[_tmp.x][_tmp.y])
							ans[_tmp.x][_tmp.y] = ans[tmp.x][tmp.y]+1;
					}
				}
			}
		}
	}//while

	for (int i = 0; i < 2*H+1; i ++)
		for (int j = 0; j < 2*W+1; j ++)
			if (ans[i][j] > _max)
			{
				_max = ans[i][j];
			}
	out << (_max+1)/2 << endl;
	out.close();
	return 0;
}