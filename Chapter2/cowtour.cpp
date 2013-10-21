/*
ID: sangobl1
PROG: cowtour
LANG: C++
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
#include <cmath>
#include <cfloat>
#include <iomanip>
using namespace std;

class CPoint
{
public:
	double x, y;
};

class CField
{
public:
	vector<int> fields;
	vector<int> idx;
	bool isIn (int ii)
	{
		for (int i = 0; i < idx.size(); i ++)
		{
			if(ii == idx[i])
				return true;
		}
		return false;
	}
};

const int nN = 150;

int N;
vector<CPoint> pastures;
vector<vector<bool> > matrix;
vector<vector<int> > fields;
vector<bool> visited;
double ans[nN][nN];
double min_ = FLT_MAX;

int visitedAll();

int main()
{
	ifstream in("cowtour.in");
	ofstream out ("cowtour.out");
	assert (in != NULL && out != NULL);
	in >> N;
	for (int i = 0; i < N; i ++)
	{
		CPoint tmpPnt;
		in >> tmpPnt.x >> tmpPnt.y;
		pastures.push_back (tmpPnt);
	}

	
		for (int j = 0; j < N; j ++)
			for (int k = 0; k < N; k ++)
				ans[j][k] = FLT_MAX; //防止溢出
	
		for (int j = 0; j < N; j ++)
			ans[j][j] = 0;

	for (int i = 0; i < N; i ++)
	{
		vector<bool> tmpv;
		for (int j = 0; j < N; j ++)
		{
			char tmpi;
			in >> tmpi;
			if (tmpi == '1')
			tmpv.push_back(true);
			else
				tmpv.push_back(false);
		}
		matrix.push_back(tmpv);
	}
	in.close();
	for (int i = 0; i < N; i ++)
		visited.push_back(false);
	//seperate the pastures into different fields
	while (visitedAll() != -1)
	{
		vector<int> tmpv;
		queue<int> tmpq;
		//tmpv.push_back(visitedAll());
		tmpq.push(visitedAll());
		//visited[visitedAll()] = true;
		while (!tmpq.empty())
		{
			int tmpi = tmpq.front();
			tmpq.pop();
			visited[tmpi] = true;
			tmpv.push_back(tmpi);
			for (int i = 0; i < N; i ++)
			{
				if(matrix[tmpi][i] )
				{
					if(!visited[i])
					{
						tmpq.push(i);
						visited[i] = true;
					}
					ans[tmpi][i] = sqrt((pastures[tmpi].x-pastures[i].x)*(pastures[tmpi].x-pastures[i].x)
						+(pastures[tmpi].y-pastures[i].y)*(pastures[tmpi].y-pastures[i].y));
					ans[i][tmpi] = ans[tmpi][i];
				}
			}
		}//while q
		fields.push_back(tmpv); 
	}//while v

	//then we use the DP to calculate
	double max_ = 0;
	for (int i = 0; i < fields.size(); i ++)
	{
		for (int j = 0; j < fields[i].size(); j ++)
		{
			for (int k = 0; k < fields[i].size(); k ++)
				for (int p = 0; p < fields[i].size(); p ++)
				{
					if (ans[fields[i][k]][fields[i][j]]+ans[fields[i][j]][fields[i][p]] < ans[fields[i][k]][fields[i][p]])
						ans[fields[i][k]][fields[i][p]] = ans[fields[i][k]][fields[i][j]]+ans[fields[i][j]][fields[i][p]];
				}
		}
	}

	//vector<vector<int> > fields_;
	//queue<CField> fields_;
	for (int i = 0; i < fields.size(); i ++)
	{
		/*CField tmpf;
		tmpf.fields = fields[i];
		tmpf.idx.push_back(i);
		fields_.push(tmpf);*/
		for (int k = 0; k < fields[i].size(); k ++)
			for (int p = 0; p < fields[i].size(); p ++)
			{
				if (ans[fields[i][k]][fields[i][p]] > max_)
					max_ = ans[fields[i][k]][fields[i][p]];
			}	

	}
	double _min = max_;
	/*while (!fields_.empty())
	{
		CField tmpf = fields_.front();
		fields_.pop();

		for (int i = 0; i < fields.size(); i ++)
		{
			if(tmpf.isIn(i))
				continue;
			else
			{
				for (int j = 0; j < fields[i].size(); j ++)
					for (int )
			}
		}
	}*/
	for (int i = 0; i < fields.size(); i ++)
		for (int j = i+1; j < fields.size(); j ++)
		{
			if (i == j)
				continue;
			else
			{
				for (int ii = 0; ii < fields[i].size(); ii ++)	//针对一条边
					for (int jj = 0; jj < fields[j].size(); jj ++)
					{
						//int max_ = 0;
						max_ = 0;
						double med = sqrt((pastures[fields[i][ii]].x-pastures[fields[j][jj]].x)*(pastures[fields[i][ii]].x-pastures[fields[j][jj]].x)
						+(pastures[fields[i][ii]].y-pastures[fields[j][jj]].y)*(pastures[fields[i][ii]].y-pastures[fields[j][jj]].y));
						
						for (int i2 = 0; i2 < fields[i].size(); i2 ++)
							for (int j2 = 0; j2 < fields[j].size(); j2 ++)
							{
								ans[fields[i][i2]][fields[j][j2]] = ans[fields[i][i2]][fields[i][ii]]+ans[fields[j][jj]][fields[j][j2]]+med;
								if(ans[fields[i][i2]][fields[j][j2]] > max_)
									max_ = ans[fields[i][i2]][fields[j][j2]];
							}
						if (max_ < min_)
							min_ = max_;
					}				
			}
		}
	out << fixed << setprecision(6) << max(min_,_min) << endl;
	//out << min_ << endl;
	out.close();

	return 0;
}

int visitedAll ()
{
	for (int i = 0; i < N; i ++)
	{
		if (!visited[i])
		{
			return i;
		}
	}
	return -1;
}