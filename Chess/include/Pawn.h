#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite){
        isFM = true;
    }

    char getSymbol() const override;

    bool isPossibleMove(int x, int y) const override;

    bool isFirstMove() const;

    void setFirstMove(bool isFM_){
        this->isFM = isFM_;
    }

    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;
private:
    bool isFM;
};

#endif //CHESS_PAWN_H

