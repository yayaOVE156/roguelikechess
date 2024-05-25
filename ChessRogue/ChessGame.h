#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

const int BOARD_SIZE = 8;

enum class Piece {
    None, Pawn, Knight, Bishop, Rook, Queen, King
};

enum class Player {
    None, White, Black
};

struct ChessPiece {
    Piece piece;
    Player player;
    bool EligibleForPromotion = false;
};

using Chessboard = std::vector<std::vector<ChessPiece>>;

// Function declarations
void InitializeChessboard(Chessboard& Board);
void PrintChessboard(const Chessboard& Board);
bool isValidMove(const Chessboard& Board, int fromX, int fromY, int toX, int toY, Player player);
void makeMove(Chessboard& Board, int fromX, int fromY, int toX, int toY);
bool parseMove(const std::string& move, int& fromX, int& fromY, int& toX, int& toY);
void printCoordinates(int fromX, int fromY, int toX, int toY);
std::string coordinatesToChessNotation(int x, int y);
void StartChessGame();
void promotePawn(Chessboard& Board, int x, int y);

#endif // CHESSGAME_H
