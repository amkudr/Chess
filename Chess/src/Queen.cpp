
#include "Queen.h"

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite) {

}

char Queen::getSymbol() const {
    return isWhite() ? 'Q' : 'q';
}

bool Queen::isPossibleMove(int x, int y) const {
    if (getX() == x || getY() == y) {
        return true;
    }
    return abs(getX() - x) == abs(getY() - y);
}

vector<pair<int, int>> Queen::getPotentialRoadblocks(int x, int y) const {
    vector<pair<int, int>> result;
    int x1 = getX();
    int y1 = getY();

    //Choose direction to move
    int dirX = (x > x1) ? 1 : (x < x1) ? -1 : 0;
    int dirY = (y > y1) ? 1 : (y < y1) ? -1 : 0;
    //Current position of the cursor
    int curX = x1 + dirX;
    int curY = y1 + dirY;

    while (curX != x || curY != y) {
        result.emplace_back(curX, curY);
        curX += dirX;
        curY += dirY;
    }

    return result;
}
