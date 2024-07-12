#pragma once

#include "string"
#include "Rook.h"
#include "King.h"
#include <memory>

using namespace std;
const int SIZE_B = 8;

class Engine {
    struct BoardState {
        shared_ptr<Piece> board[SIZE_B][SIZE_B];
        bool firstMove[SIZE_B][SIZE_B]{};

        BoardState(shared_ptr<Piece> m_board[SIZE_B][SIZE_B], bool m_firstMove[SIZE_B][SIZE_B]) {
            for (int i = 0; i < SIZE_B; i++) {
                for (int j = 0; j < SIZE_B; j++) {
                    board[i][j] = m_board[i][j];
                    firstMove[i][j] = m_firstMove[i][j];
                }
            }
        }
    };
    shared_ptr<Piece> m_board[SIZE_B][SIZE_B] = {nullptr};
    bool m_firstMove[SIZE_B][SIZE_B] = {false};

    vector<BoardState> move_history;

    bool white_turn = true;
    shared_ptr<King> white_king;
    shared_ptr<King> black_king;
    bool isCheck(bool goodCheck);
    bool isCheckmate();
    bool Castling(int curX, int curY, int nextX, int nextY, const shared_ptr<Piece>& piece);
    void undoMove();




public:
    explicit Engine(const string &start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    int checkMove(string move, bool checkmateV);
    Engine &operator=(const Engine &) = delete;
    string printBoard();
    void movePiece(int x_from, int y_from, int x_to, int y_to, bool castlingRook);


//    ~Engine();
//    void run();

};