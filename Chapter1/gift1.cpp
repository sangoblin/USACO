/*
ID: sangobl1
PROG: gift1
LANG: C++
*/
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ifstream filein("gift1.in");
	ofstream fileout("gift1.out");
	unsigned number;
	filein >> number;
	string *persons = new string[number];
	int **money = (int **)new int *[number];
	for (unsigned i = 0; i < number; i ++)
		money[i] = new int [number];

	for(unsigned i = 0; i < number; i ++)
		for (unsigned j = 0; j < number; j ++)
			money[i][j] = 0;
		//对二维数组进行初始化

	for (unsigned i = 0; i < number; i ++)
		filein >> persons[i];

	string tmp;
	unsigned index, percount, indexo, pero;
	while(filein >> tmp)
	{
		for (unsigned i = 0; i < number; i ++)
			if (persons[i] == tmp)
			{
				index = i;
				break;
			}

		filein >> money[index][index];
		filein >> percount;
		pero = 0;
		while(percount != pero)
		{
			filein >> tmp;
			for (unsigned i = 0; i < number; i ++)
				if (persons[i] == tmp)
				{
					indexo = i;
					break;
				}

			if (index != indexo)
				money[index][indexo] = money[index][index]/percount;

			pero ++;
		}
		money[index][index] = 0;
	}

	for(unsigned i = 0; i < number; i ++)
	{
		int get = 0, give = 0;
		for(unsigned j = 0; j < number; j ++)
			get += money[j][i];
		for(unsigned j = 0; j < number; j ++)
			give += money[i][j];
		money[i][i] = get - give;
	}
	for (unsigned i = 0; i < number; i ++)
		fileout << persons[i] << ' ' << money[i][i] << '\n';

	filein.close();
	fileout.close();

	return 0;
}
