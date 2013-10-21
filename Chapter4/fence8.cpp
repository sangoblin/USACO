/*
ID: sangobl1
PROG: fence8
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstdlib>
using namespace std;

const int nN = 50;
const int nR = 1023;

int N, R;
int boards[nN], rails[nR];
bool e2f[nR];
//int remains[nR+1];
int waste;
int upper, ans;
bool result = false;

//bool can[nN][nN][nR][nR]; //��ʾ��i��j��boards�ܷ�������m��n��ľ��
//���������Ĺ����������˺ܶ�ԳƵĴ�ŷ�ʽ���˵����ͨ����֦���б���

//pollution������ʾ�Ѿ�����Щboard��ʹ���ˣ�����Щ���ƺ�ֻ������boards�ĳ��Ⱦ���ͬʱ
//����ֻ�ܻ�һ�ּ�֦�ķ����ˣ���ͨ��������Ҫ��rail���кܶ���ͬ�ĳߴ�ģ����start���ڼ�¼��ͬ��С��rail�ĵ�һ�����ֵ�λ��
bool search(/*vector<int>&,*/ /*vector<int>&,*/ int depth, /*int w,*/ int start);

int main(int argc, char** argv)
{
	ifstream in("fence8.in");
	ofstream out("fence8.out");
	in >> N;
	for (int i = 0; i < N; ++ i)
		in >> boards[i];
	in >> R;
	for (int i = 0; i < R; ++ i)
		in >> rails[i];
	in.clear();
	in.close();
	//sort(boards, boards+N, greater<int>());
	sort(boards, boards+N, greater<int>());
	sort(rails, rails+R);
	//��Ϊ������޷�����board���е�rail,��ô���railһ���Ƿǳ����ģ�������̰���㷨�ó��ý���
	//int sum = 0;
	int sum_b = accumulate(boards, boards+N, 0), sum = 0;

	e2f[0] = false;
	for (int i = 1; i < R; ++ i)
	{
		if (rails[i] == rails[i-1])
			e2f[i] = true;
		else
			e2f[i] = false;
	}

	//remains[R] = rails[R];
	while (sum < sum_b)
	{
		sum += rails[upper++];		//upper
		if (upper >= R)
			break;
	}

	ans = (sum>sum_b)?--upper:upper;
	while (!result)
	{
		//vector<int> vBoards(boards, boards+N);
		vector<int> vRails(rails, rails+ans);

		/*remains[ans] = vRails[ans-1];
		for (int i = ans-1; i >= 1; --i)
		{
			remains[i] = remains[i+1]+vRails[i-1];
		}*/
		//int sum_r = accumulate(vRails.begin(), vRails.end(), 0);
		int sum_r = accumulate(rails, rails+ans, 0);
		waste = sum_b-sum_r; //���ֻ��������ô��Ŀռ䱻�˷ѵ�

		//sort(vRails.begin(), vRails.end(), greater<int>());

		result = search(/*vBoards, *//*vRails,*/ 0, /*0,*/ 0);
		if(!result)
			--ans;
	}
	out << ans << endl;
	out.clear();
	out.close();
	return EXIT_SUCCESS;
}

bool search(/*vector<int>& boards, *//*vector<int>& rails,*/ int depth, /*int w,*/ int start)
{
	bool result;
	int start_ = 0, anotherw = 0;

	if (depth == ans)
		return true;

	for (int i = 0; i < N; ++i)
		if (boards[i] < rails[0])
			anotherw += boards[i];

	if (anotherw > waste)
		return false;

	for (int j = start; j < N; ++ j)
	{
		if (boards[j] >= rails[ans-depth-1])
		{
			//backrail = rails[depth];
			boards[j] -= rails[ans-depth-1];
			//rails.erase(rails.begin());
			//if (depth+1<rails.size() && rails[depth+1] == rails[depth])
				//result = search(boards, rails, depth-1, w, j);
			if (e2f[depth+1])
				start_ = j;
			result = search(/*boards,*/ /*rails,*/ depth+1, /*w,*/ start_);
			if (result)
				return true;
			else
			{
				boards[j] += rails[ans-depth-1];
			}
		}
		//else //the shortest rail cannot be set to this board, then it cannot be utilized any more
		//{
		//	w += boards[j];

		//	if (w > waste)
		//		return false;
		//}
	}

	return false;
}