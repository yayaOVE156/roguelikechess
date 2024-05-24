#include "ChessGame.h"
#include <iostream>
#include <cctype>
#include <limits>

void InitializeChessboard(Chessboard& Board) {
    Board.resize(BOARD_SIZE, std::vector<ChessPiece>(BOARD_SIZE, {Piece::None, Player::None}));

    // Set up the black pieces
    Board[0][0] = Board[0][7] = {Piece::Rook, Player::Black};
    Board[0][1] = Board[0][6] = {Piece::Knight, Player::Black};
    Board[0][2] = Board[0][5] = {Piece::Bishop, Player::Black};
    Board[0][3] = {Piece::Queen, Player::Black};
    Board[0][4] = {Piece::King, Player::Black};
    for (int i = 0; i < BOARD_SIZE; ++i) {
        Board[1][i] = {Piece::Pawn, Player::Black};
    }

    // Set up the white pieces
    Board[7][0] = Board[7][7] = {Piece::Rook, Player::White};
    Board[7][1] = Board[7][6] = {Piece::Knight, Player::White};
    Board[7][2] = Board[7][5] = {Piece::Bishop, Player::White};
    Board[7][3] = {Piece::Queen, Player::White};
    Board[7][4] = {Piece::King, Player::White};
    for (int i = 0; i < BOARD_SIZE; ++i) {
        Board[6][i] = {Piece::Pawn, Player::White};
    }
}

void PrintChessboard(const Chessboard& Board) {
    std::cout << "  A   B   C   D   E   F   G   H" << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << 8 - i << " ";  // Print the row number
        for (int j = 0; j < BOARD_SIZE; ++j) {
            const ChessPiece& piece = Board[i][j];
            if (piece.player == Player::White) {
                switch (piece.piece) {
                    case Piece::Pawn: std::cout << " ♙ "; break;
                    case Piece::Knight: std::cout << " ♘ "; break;
                    case Piece::Bishop: std::cout << " ♗ "; break;
                    case Piece::Rook: std::cout << " ♖ "; break;
                    case Piece::Queen: std::cout << " ♕ "; break;
                    case Piece::King: std::cout << " ♔ "; break;
                    default: std::cout << "   ";
                }
            } else if (piece.player == Player::Black) {
                switch (piece.piece) {
                    case Piece::Pawn: std::cout << " ♟ "; break;
                    case Piece::Knight: std::cout << " ♞ "; break;
                    case Piece::Bishop: std::cout << " ♝ "; break;
                    case Piece::Rook: std::cout << " ♜ "; break;
                    case Piece::Queen: std::cout << " ♛ "; break;
                    case Piece::King: std::cout << " ♚ "; break;
                    default: std::cout << "   ";
                }
            } else {
                std::cout << "   ";
            }
        }
        std::cout << " " << 8 - i << std::endl;  // Print the row number again at the end
    }
    std::cout << "  A   B   C   D   E   F   G   H" << std::endl;  // Print the column headers again at the bottom
}

bool isValidMove(const Chessboard& Board, int fromX, int fromY, int toX, int toY, Player player) {
    const ChessPiece& fromPiece = Board[fromX][fromY];
    const ChessPiece& toPiece = Board[toX][toY];

    if (fromPiece.player != player || fromPiece.piece == Piece::None) {
        return false;
    }

    if (fromX == toX && fromY == toY) {
        return false;
    }

    switch (fromPiece.piece) {
        case Piece::Pawn:
            if (fromPiece.player == Player::White) {
                if (fromX == 6 && toX == 4 && fromY == toY && toPiece.piece == Piece::None && Board[5][fromY].piece == Piece::None) {
                    return true;
                }
                if (fromX - 1 == toX && fromY == toY && toPiece.piece == Piece::None) {
                    return true;
                }
                if (fromX - 1 == toX && (fromY - 1 == toY || fromY + 1 == toY) && toPiece.player == Player::Black) {
                    return true;
                }
                // En passant
                if (fromX == 3 && toX == 2 && std::abs(fromY - toY) == 1 && Board[3][toY].piece == Piece::Pawn && Board[3][toY].player == Player::Black) {
                    return true;
                }
            } else {
                if (fromX == 1 && toX == 3 && fromY == toY && toPiece.piece == Piece::None && Board[2][fromY].piece == Piece::None) {
                    return true;
                }
                if (fromX + 1 == toX && fromY == toY && toPiece.piece == Piece::None) {
                    return true;
                }
                if (fromX + 1 == toX && (fromY - 1 == toY || fromY + 1 == toY) && toPiece.player == Player::White) {
                    return true;
                }
                // En passant
                if (fromX == 4 && toX == 5 && std::abs(fromY - toY) == 1 && Board[4][toY].piece == Piece::Pawn && Board[4][toY].player == Player::White) {
                    return true;
                }
            }
            break;

        case Piece::Knight:
            if ((std::abs(fromX - toX) == 2 && std::abs(fromY - toY) == 1) ||
                (std::abs(fromX - toX) == 1 && std::abs(fromY - toY) == 2)) {
                return true;
            }
            break;

        case Piece::Bishop:
            if (std::abs(fromX - toX) == std::abs(fromY - toY)) {
                int dx = (toX > fromX) ? 1 : -1;
                int dy = (toY > fromY) ? 1 : -1;
                int x = fromX + dx;
                int y = fromY + dy;
                while (x != toX) {
                    if (Board[x][y].piece != Piece::None) {
                        return false;
                    }
                    x += dx;
                    y += dy;
                }
                return true;
            }
            break;

        case Piece::Rook:
            if (fromX == toX || fromY == toY) {
                int dx = (fromX == toX) ? 0 : ((toX > fromX) ? 1 : -1);
                int dy = (fromY == toY) ? 0 : ((toY > fromY) ? 1 : -1);
                int x = fromX + dx;
                int y = fromY + dy;
                while (x != toX || y != toY) {
                    if (Board[x][y].piece != Piece::None) {
                        return false;
                    }
                    x += dx;
                    y += dy;
                }
                return true;
            }
            break;

        case Piece::Queen:
            if (fromX == toX || fromY == toY || std::abs(fromX - toX) == std::abs(fromY - toY)) {
                int dx = (fromX == toX) ? 0 : ((toX > fromX) ? 1 : -1);
                int dy = (fromY == toY) ? 0 : ((toY > fromY) ? 1 : -1);
                int x = fromX + dx;
                int y = fromY + dy;
                while (x != toX || y != toY) {
                    if (Board[x][y].piece != Piece::None) {
                        return false;
                    }
                    x += dx;
                    y += dy;
                }
                return true;
            }
            break;

        case Piece::King:
            if (std::abs(fromX - toX) <= 1 && std::abs(fromY - toY) <= 1) {
                return true;
            }
            break;

        default:
            return false;
    }

    return false;
}

void promotePawn(Chessboard& Board, int x, int y) {
    char choice;
    std::cout << "Pawn promotion! Choose (Q)ueen, (R)ook, (B)ishop, or K(n)ight: ";
    std::cin >> choice;
    switch (std::toupper(choice)) {
        case 'Q':
            Board[x][y].piece = Piece::Queen;
            break;
        case 'R':
            Board[x][y].piece = Piece::Rook;
            break;
        case 'B':
            Board[x][y].piece = Piece::Bishop;
            break;
        case 'N':
            Board[x][y].piece = Piece::Knight;
            break;
        default:
            std::cout << "Invalid choice. Promoting to Queen by default." << std::endl;
            Board[x][y].piece = Piece::Queen;
            break;
    }
}

void makeMove(Chessboard& Board, int fromX, int fromY, int toX, int toY) {
    if (Board[fromX][fromY].piece == Piece::Pawn && std::abs(fromY - toY) == 1 && Board[toX][toY].piece == Piece::None) {
        // En passant
        if (Board[fromX][fromY].player == Player::White) {
            Board[toX + 1][toY] = {Piece::None, Player::None};
        } else {
            Board[toX - 1][toY] = {Piece::None, Player::None};
        }
    }

    Board[toX][toY] = Board[fromX][fromY];
    Board[fromX][fromY] = {Piece::None, Player::None};

    // Check for pawn promotion
    if (Board[toX][toY].piece == Piece::Pawn && (toX == 0 || toX == 7)) {
        promotePawn(Board, toX, toY);
    }
}

bool parseMove(const std::string& move, int& fromX, int& fromY, int& toX, int& toY) {
    if (move.length() != 5 || move[2] != ' ') {
        return false;
    }

    fromY = std::toupper(move[0]) - 'A';
    fromX = 8 - (move[1] - '0');
    toY = std::toupper(move[3]) - 'A';
    toX = 8 - (move[4] - '0');

    if (fromX < 0 || fromX >= BOARD_SIZE || fromY < 0 || fromY >= BOARD_SIZE ||
        toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE) {
        return false;
    }

    return true;
}
void printCoordinates(int fromX, int fromY, int toX, int toY) {
    std::cout << "Move coordinates: from (" << 8 - fromX << ", " << char(fromY + 'A') << ") to (" << 8 - toX << ", " << char(toY + 'A') << ")" << std::endl;
}

std::string coordinatesToChessNotation(int x, int y) {
    char file = 'A' + y;
    int rank = 8 - x;
    return std::string(1, file) + std::to_string(rank);
}

void StartChessGame() {
    Chessboard Board;
    InitializeChessboard(Board);

    Player currentPlayer = Player::White;
    while (true) {
        PrintChessboard(Board);
        std::cout << (currentPlayer == Player::White ? "White" : "Black") << "'s turn. Enter your move (e.g., E2 E4): ";
        
        std::string move;
        std::getline(std::cin, move);  // Use getline to read the input including spaces

        int fromX, fromY, toX, toY;
        if (!parseMove(move, fromX, fromY, toX, toY)) {
            std::cout << "Invalid input format. Please try again." << std::endl;
            continue;
        }

        printCoordinates(fromX, fromY, toX, toY);  // Print the coordinates of the move

        if (isValidMove(Board, fromX, fromY, toX, toY, currentPlayer)) {
            makeMove(Board, fromX, fromY, toX, toY);
            currentPlayer = (currentPlayer == Player::White) ? Player::Black : Player::White;
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }
}


// int main() {
//     Chessboard Board;
//     InitializeChessboard(Board);

//     Player currentPlayer = Player::White;
//     while (true) {
//         PrintChessboard(Board);
//         std::cout << (currentPlayer == Player::White ? "White" : "Black") << "'s turn. Enter your move (e.g., E2 E4): ";
        
//         std::string move;
//         std::cin >> move;

//         int fromX, fromY, toX, toY;
//         if (!parseMove(move, fromX, fromY, toX, toY)) {
//             std::cout << "Invalid input format. Please try again." << std::endl;
//             continue;
//         }

//         if (isValidMove(Board, fromX, fromY, toX, toY, currentPlayer)) {
//             makeMove(Board, fromX, fromY, toX, toY);
//             currentPlayer = (currentPlayer == Player::White) ? Player::Black : Player::White;
//         } else {
//             std::cout << "Invalid move. Try again." << std::endl;
//         }
//     }

//     return 0;
// }
