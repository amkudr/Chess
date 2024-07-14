
#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(int x, int y, bool isWhite);

    char getSymbol() const override;

    bool isPossibleMove(int x, int y) const override;

    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;

    int getValue() const override;
};

#endif //CHESS_QUEEN_H
