#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
template <typename T>
using vc = std::vector<T>;

#include "puzzle.hpp"

Puzzle::Puzzle(vc<std::string> &_grid, vc<vc<std::string>> &_pieces)
{
    grid = _grid;
    for (vc<std::string> p : _pieces)
        pieces.push_back(Piece(p));
    output.open(output_file_path);
    gr = grid.size();
    gc = grid[0].size();
    grid_num_check();
    remove_empty_line();
    remove_double_piece();
}

void Puzzle::grid_num_check()
{
    int grid_cnt = 0, piece_cnt = 0;
    for (std::string str : grid)
        for (char c : str)
            grid_cnt += c == '1';
    for (Piece piece : pieces)
        for (std::string str : piece.data)
            for (char c : str)
                piece_cnt += c == '1';
    std::stringstream ss;
    ss << "grid cnt: " << grid_cnt << ", pieces cnt: " << piece_cnt << "\n\n";
    output << ss.str();
    if (grid_cnt != piece_cnt)
    {
        output << "cell number and item number are not equal\n";
        output.close();
        exit(0);
    }
    output.close();
}

void Puzzle::remove_empty_line()
{
    return;
    // TODO: implement this func
    for (Piece piece : pieces)
    {
        int rows, rowe, cols, cole;
        bool is_not_blank_row = 0;
        bool is_not_blank_col = 0;
    }
}

void Puzzle::remove_double_piece()
{
    // TODO: implement kind process
    vc<Piece> clean_pieces;
    for (Piece piece : pieces)
    {
        int idx = -1;
        Kind pk;
        for (int comp_idx = 0; comp_idx < clean_pieces.size(); comp_idx++)
        {
            if (is_same_piece(piece, clean_pieces[comp_idx]))
            { // doubled
                idx = comp_idx;
                pk = clean_pieces[idx].kind;
                break;
            }
        }
        if (idx == -1) // not doubled
        {
            idx = clean_pieces.size();
            clean_pieces.push_back(piece);
            pk = piece_kind(piece);
        }
        piece_idx.push_back(idx);
        kinds.push_back(pk);
    }
    swap(pieces, clean_pieces);
}

void rotate_piece_90deg(Piece &piece)
{
    // rotate 90 degree
    int h = piece.data.size(), w = piece.data[0].size();
    vc<std::string> new_piece(w, std::string(h, '0'));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            new_piece[w - 1 - j][i] = piece.data[i][j];
    piece.data = new_piece;
}

void rotate_piece_180deg(Piece &piece)
{
    int h = piece.data.size(), w = piece.data[0].size();
    vc<std::string> new_piece(h, std::string(w, ' '));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            new_piece[h - i - 1][w - j - 1] = piece.data[i][j];
    piece.data = new_piece;
}

bool is_same_piece(Piece &a, Piece &b)
{
    bool is_same = false;
    int ah = a.data.size(), aw = a.data[0].size();
    int bh = b.data.size(), bw = b.data[0].size();
    auto same_check = [&](Piece &a, Piece &b)
    {
        is_same |= a.data == b.data;
        rotate_piece_180deg(b);
        is_same |= a.data == b.data;
    };
    if (ah == bh && aw == bw)
    {
        same_check(a, b);
    }
    if (ah == bw && aw == bh)
    {
        rotate_piece_90deg(b);
        same_check(a, b);
    }
    return is_same;
}

Kind piece_kind(Piece p)
{
    Piece cp = p;
    rotate_piece_90deg(cp);
    if (cp.data == p.data)
        return Square;
    cp = p;
    rotate_piece_180deg(cp);
    if (cp.data == p.data)
        return Rect;
    return Asym;
}
