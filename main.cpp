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
    for (string &s : g)
        cin >> s;
    vc<vc<string>> ps;
    for (int i = 0; i < p; i++)
    {
        int r;
        cin >> r;
        vc<string> piece(r);
        for (string &s : piece)
            cin >> s;
        ps.push_back(piece);
    }
    solve(g, ps);
}
