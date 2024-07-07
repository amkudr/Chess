#include "Rook.h"

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite) {


}

char Rook::getSymbol() const {
    return isWhite() ? 'R' : 'r';
}

bool Rook::isPossibleMove(int x, int y) const {
    if ((x == getX() && y != getY()) || (y == getY() && x != getX())) {
        return true;
    }
    return false;
}

vector<pair<int, int>> Rook::getPotentialRoadblocks(int x, int y) const {
    if (!isPossibleMove(x, y)) {
        return {};
    }
    vector<pair<int, int>> way;
    if (y == getY()) {
        if (x < getX())
            for (int i_x = getX() - 1; i_x > x; i_x--)
                way.emplace_back(i_x, y);

        else {
            for (int i_x = getX() + 1; i_x < x; i_x++)
                way.emplace_back(i_x, y);
        }
    }
    else {
        if (y < getY())
            for (int i_y = getY() - 1; i_y > y; i_y--)
                way.emplace_back(x, i_y);
        else {
            for (int i_y = getY() + 1; i_y < y; i_y++)
                way.emplace_back(x, i_y);
        }
    }
    return way;
}


