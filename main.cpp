#include <string>
#include <iostream>
#include <vector>
#include "solve.hpp"

using namespace std;

template <typename T>
using vc = vector<T>;

int main()
{
    int h, p;
    cin >> h >> p;
    vc<string> g(h);
    for (int i = 0; i < h; i++)
        cin >> g[i];
    vc<vc<string>> ps;
    for (int i = 0; i < p; i++)
    {
        int r;
        cin >> r;
        vc<string> piece(r);
        for (int j = 0; j < r; j++)
            cin >> piece[j];
        ps.push_back(piece);
    }
    solve(g, ps);
}
