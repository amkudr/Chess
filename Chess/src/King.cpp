#include "King.h"

char King::getSymbol() const {
    return isWhite() ? 'K' : 'k';
}

bool King::isPossibleMove(int x_, int y_) const {
    return (abs(x_ - getX()) <= 1 && abs(y_ - getY()) <= 1)
           || (isWhite() && x_ == 0 && (y_ == 6 || y_ == 1))  // Castling
           || (!isWhite() && x_ == 7 && (y_ == 6 || y_ == 1));
}

vector<pair<int, int>> King::getPotentialRoadblocks(int x, int y) const {
    return {};
}

int King::getValue() const {
    return INT_MAX;
}
