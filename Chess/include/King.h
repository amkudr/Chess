#ifndef KING_H
#define KING_H

#include "Piece.h"

class King: public Piece {
public:
    King(int x, int y, bool isWhite) : Piece(x, y, isWhite) {

    }

    char getSymbol() const override;

    bool isPossibleMove(int x, int y) const override;

    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;
};
#endif // KING_H
