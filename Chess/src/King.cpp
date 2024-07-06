#include "King.h"

char King::getSymbol() const {
    return isWhite() ? 'K' : 'k';
}

bool King::isPossibleMove(int x, int y) const {
    return (abs(x - getX()) <= 1 && abs(y - getY()) <= 1);
}

vector<pair<int, int>> King::getPotentialRoadblocks(int x, int y) const {
    return {};
}
