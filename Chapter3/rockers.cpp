/*
ID: sangobl1
PROG: rockers
LANG: C++
*/

#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

const int nN = 20;

class CDisk
{
public:
	int volume, rank;
};

int N, T, M;
CDisk disks[nN+1];
int songs[nN+1];
int backrank[nN+1][nN+1];
int ans;

void search(int depth, int curNum);

int main()
{
	ifstream in("rockers.in");
	ofstream out("rockers.out");
	assert (in!=NULL && out!=NULL);
	in >> N >> T >> M;
	for (int i = 1; i <= N; ++ i)
	{
		in >> songs[i];
	}
	in.close();
	in.clear();

	for (int i = 1; i <= M; ++ i)
	{
		disks[i].volume = T;
		disks[i].rank = N; // any song with the ID less than rank can be inserted into this disk
	}
	//////////////////////////////////////////////////////////////////////////
	search(1, 0);
	out << ans << endl;
	out.close();
	out.clear();
	return EXIT_SUCCESS;
}

void search(int depth, int curNum)
{
	if (curNum > ans)
		ans = curNum;

	if (depth > N)
		return;

	bool can = false;
	//search(depth+1, curNum); //

	for (int i = 0; i <= M; ++ i)
	{
		if (i == 0)
			search(depth+1, curNum); // we don't insert depthth song
		else
		{

			if (disks[i].volume < songs[depth] || disks[i].rank < depth)
				continue;
			else
			{
				can = true;
				disks[i].volume -= songs[depth];
				for (int j = 1; j < i; ++ j)
				{
					backrank[depth][j] = disks[j].rank;
					if (disks[j].rank > depth)
						disks[j].rank = depth;
				}
				search(depth+1, curNum+1);
				for (int j = 1; j < i; ++ j)
				{
					//backrank[j] = disks[j].rank;
					disks[j].rank = backrank[depth][j];
				}
				disks[i].volume += songs[depth];
			}
			if (can)
				break;
		}//if
	}

	//if (!can)
}