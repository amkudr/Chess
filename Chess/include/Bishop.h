
#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(int x, int y, bool isWhite);

    char getSymbol() const override;

    bool isPossibleMove(int x, int y) const override;

    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;

    int getValue() const override;
};



#endif //CHESS_BISHOP_H
