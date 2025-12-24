#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
template <typename T>
using vc = std::vector<T>;

enum Kind
{
    Square,
    Rect,
    Asym
};

struct Piece
{
    vc<std::string> shape;
    Kind kind;
    Piece(vc<std::string> &piece)
    {
        shape = piece;
    }
};

struct Puzzle
{
    std::string output_file_path = "out.txt";
    vc<std::string> grid;
    vc<Piece> pieces;
    vc<int> piece_idx;
    vc<Kind> kinds;
    int gr, gc; // grid size
    std::ofstream output;
    Puzzle(vc<std::string> &_grid, vc<vc<std::string>> &_pieces);
    void grid_num_check();
    void remove_empty_line();
    void remove_double_piece();
};

void rotate_piece_90deg(Piece &piece);

bool is_same_piece(Piece &a, Piece &b);

Kind piece_kind(Piece p);

#endif
