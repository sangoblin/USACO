/*
ID: sangobl1
PROG: calfflac
LANG: C++
*/
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

bool isCharacter(char);
bool isEqual(char, char);

int main()
{
    ifstream in("calfflac.in");
    ofstream out("calfflac.out");

    string raw, refined;
	string solver("#");
    vector<int> index;  //for useful character
	char temp[81];
	raw.clear();
	refined.clear();
	//solver.clear();

	while(in.getline(temp, 81))
	{
		raw += temp;
		raw += '\n';   // the last char'll be erased if not char
	}

	for(int i = 0; i < raw.length(); i ++)
	{
        if(isCharacter(raw[i]))
        {
            index.push_back(i);
            refined += raw[i];
        }
	}
	for(int i = 0; i < refined.length(); i ++)
	{
        solver += refined[i];
        solver += '#';
	}       // completed the initiation of strSolver
   // solver.erase(solver.length()-1, 1);
	//////////////////////now use the Manacher
    int idx, maxR = 0;
    int current;
    int max = 0, tmp, maxi, maxiRe;
    int *p = (int *)new int[solver.length()];   //radius
    memset(p, 0, solver.length()*sizeof(int));

    p[0] = 0;
    maxR = 0;
    idx = 0;
    for(current = 1; current < solver.length(); current ++)
    {

        if(current < maxR)
        {
            p[current] = min(maxR-current, p[2*idx-current]);
        }
        /*else
        {
            p[current] = 1;
        }*/

        while(isEqual(solver[current+p[current]+1], solver[current-p[current]-1]))
            {
                  p[current]++;
                  if((current+p[current]+1)>= solver.length() || (current-p[current]-1) < 0)
                  {
                      break;
                  }
            }
            if((current+p[current])> maxR)
            {
                maxR = current+p[current];
                idx = current;
            }
			if(maxR >= solver.length()-1)
				break;
    }

    for(int i = 0; i < solver.length(); i ++)
    {
            tmp = p[i];
            if(tmp > max)
            {
               max = tmp;
               maxi = i;
            }

    }
    out << max << endl;
    //if(solver[maxi] != '#')
    {
        tmp = maxi - p[maxi] + 1;
        maxiRe = (tmp+1)/2 - 1;
    }

    int count = 1;
    int j = index[maxiRe];
    while(count <= max)
    {
        out << raw[j];
        if(isCharacter(raw[j]))
            count ++;
        j++;
    }
    out << endl;

    return 0;
}

bool isCharacter(char c)  //judge whether is a character
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return true;
	}
	else
		return false;
}

bool isEqual(char c1, char c2)
{
	if((c1 == c2) || ((c2-c1)== 'A'-'a') || ((c1-c2)== 'A'-'a'))
		return true;
	else
		return false;
}
