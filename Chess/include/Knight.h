#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight: public Piece{
public:
    Knight(int x, int y, bool isWhite);
    char getSymbol() const override;
    bool isPossibleMove(int x, int y) const override;
    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;
    int getValue() const override;
};


#endif //CHESS_KNIGHT_H
