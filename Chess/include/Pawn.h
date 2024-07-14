#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite){};

    char getSymbol() const override;

    bool isPossibleMove(int x, int y) const override;

    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;

    int getValue() const override;
private:
};

#endif //CHESS_PAWN_H

