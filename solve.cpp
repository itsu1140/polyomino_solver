#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;
template <typename T>
using vc = vector<T>;
template <typename T>
using vv = vc<vc<T>>;

#include "puzzle.hpp"

bool canfill(Piece &piece, vc<string> &fill, Puzzle &pz, int d)
{
    bool filled = 0;
    for (int gi = 0; gi < fill.size() - piece.data.size() + 1; gi++)
    {
        for (int gj = 0; gj < fill[0].size() - piece.data[0].size() + 1; gj++)
        {
            set<pair<int, int>> fillidx;
            bool ok = 1;
            for (int pi = 0; pi < piece.data.size(); pi++)
            {
                for (int pj = 0; pj < piece.data[0].size(); pj++)
                {
                    if (piece.data[pi][pj] == '0')
                        continue;
                    int fi = gi + pi, fj = gj + pj;
                    if (pz.grid[fi][fj] == '0' || fill[fi][fj] != '_')
                        ok = 0;
                    fillidx.insert({fi, fj});
                }
            }
            if (ok)
            {
                filled = 1;
                for (pair<int, int> pii : fillidx)
                    fill[pii.first][pii.second] = char(d + '0');
                goto FILLED;
            }
        }
    }
FILLED:
    return filled;
}

string dfs(int dep, Puzzle &pz, vc<string> fill, vc<int> &idx)
{
    string ans = "";
    if (dep == idx.size()) // answer output
    {
        for (string str : fill)
            ans += str + "\n";
        return ans;
    }
    Piece piece = pz.pieces[idx[dep]];
    auto rotate_rec = [&](int rotate_num)
    {
        while (rotate_num--)
        {
            vc<string> fillcp = fill;
            if (ans == "" && canfill(piece, fillcp, pz, dep))
                ans = dfs(dep + 1, pz, fillcp, idx);
            rotate_piece_90deg(piece);
        }
    };
    if (pz.kinds[dep] == Square)
        rotate_rec(1);
    else if (pz.kinds[dep] == Rect)
        rotate_rec(2);
    else
        rotate_rec(4);
    return ans;
}

void solve(vc<string> &grid, vv<string> &pieces)
{
    vc<int> idx(pieces.size());
    iota(idx.begin(), idx.end(), 0);
    Puzzle pz = Puzzle(grid, pieces);
    string ans = "";
    pz.output.open(pz.output_file_path, std::ios::app);
    do
    {
        vc<string> fill(pz.gr, string(pz.gc, '_'));
        ans = dfs(0, pz, fill, idx);
        if (ans != "")
        {
            pz.output << "ANSWER\n"
                      << ans;
            break;
        }
    } while (next_permutation(idx.begin(), idx.end()));
    if (ans == "")
        pz.output << "no answer found\n";
    pz.output.close();
}
