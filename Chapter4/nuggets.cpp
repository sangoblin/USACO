/*
ID: sangobl1
PROG: nuggets
LANG: C++
*/



//
//  main.cpp
//  nuggets
//
//  Created by DeathKnight on 13-3-14.
//  Copyright (c) 2013年 DeathKnight. All rights reserved.
//

#include <fstream>
#include <cassert>
#include <algorithm>

using namespace std;

const int nN = 10;
const int nNum = 256*255; // this could be the biggest number ever found, actually it cannot be

int N;
int max_;

int compo[nN];
int mode[nNum+1];
bool allEven = true;
//bool remain[nNum];

int main(int argc, const char * argv[])
{

    // insert code here...
    ifstream in("nuggets.in");
    ofstream out("nuggets.out");
    //assert(in!=NULL && out!=NULL);
    assert (in && out);
    
    in >> N;
    
    for (int i = 0; i < N; ++ i)
	{
        in >> compo[i];
		if (compo[i]%2 != 0)
			allEven = false;
	}
    
    sort(compo, compo+N);
    
	if (compo[0] == 1 || allEven || N == 1)
    {
        out << 0 << endl;
        return 0;
    }
    
    // now that there is no 1 here, we can get at least some numbers that cannot be represented by other numbers
    mode[0] = 1;
    for (int j = 0 ; j < N; ++ j)
        for (int i = 0; i <= nNum-compo[j]; ++ i)
        {
            mode[i+compo[j]] += mode[i];
        }

    for (int i = 1; i < nNum; ++ i)
    {
        if (mode[i] == 0)
        {
            max_ = i;
        }
    }
    
    out << max_ << endl;
    
    return 0;
}

