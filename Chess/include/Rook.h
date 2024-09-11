#include "Piece.h"

class Rook: public Piece {
    public:
    Rook(int x, int y, bool isWhite);
    char getSymbol() const override;
    bool isPossibleMove(int x, int y) const override;
    vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const override;
    int getValue() const override;



};