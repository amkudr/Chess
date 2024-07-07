#include "Pawn.h"

char Pawn::getSymbol() const {
    return isWhite() ? 'P' : 'p';
}

bool Pawn::isFirstMove() const {
    return isFM;
}

bool Pawn::isPossibleMove(int x, int y) const {
    int x1 = getX();
    int y1 = getY();
    int direction = isWhite() ? 1 : -1;

    if (y == y1 && x == x1 + 2 * direction && isFirstMove()) {  //First move
        return true;
    }
    if (x == x1 + direction && (y == y1 || y == y1 + 1 || y == y1 - 1)) {
        return true;
    }
    return false;
}

vector<pair<int, int>> Pawn::getPotentialRoadblocks(int x, int y) const {
    if (!isPossibleMove(x, y)) {
        return {};
    }
    vector<pair<int, int>> way;
    int x1 = getX();
    int y1 = getY();
    int direction = isWhite() ? 1 : -1;

    if (isFirstMove() && x == x1 + 2 * direction) {
        way.emplace_back(x1 + direction, y);
    }

    return way;
}
