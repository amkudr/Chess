#pragma once

#include "string"
#include "Rook.h"
#include "King.h"
#include <memory>

using namespace std;
const int SIZE_B = 8;

class Engine {
    shared_ptr<Piece> m_board[SIZE_B][SIZE_B] = {nullptr};
    bool white_turn = true;
    shared_ptr<King> white_king;
    shared_ptr<King> black_king;
    bool isCheck(bool goodCheck);
    bool isCheckmate();




public:
    explicit Engine(const string &start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    int checkMove(string move);
    Engine &operator=(const Engine &) = delete;
    string printBoard();
    void movePiece(int x_from, int y_from, int x_to, int y_to);


//    ~Engine();
//    void run();

};