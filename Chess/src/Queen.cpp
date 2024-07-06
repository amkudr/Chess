
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
    if (x1 == x) {
        if (y1 < y) {
            for (int i = y1 + 1; i < y; i++) {
                result.emplace_back(x, i);
            }
        } else {
            for (int i = y1 - 1; i > y; i--) {
                result.emplace_back(x, i);
            }
        }
    } else if (y1 == y) {
        if (x1 < x) {
            for (int i = x1 + 1; i < x; i++) {
                result.emplace_back(i, y);
            }
        } else {
            for (int i = x1 - 1; i > x; i--) {
                result.emplace_back(i, y);
            }
        }
    } else if (x1 < x && y1 < y) {
        for (int i = 1; i < abs(x - x1); i++) {
            result.emplace_back(x1 + i, y1 + i);
        }
    } else if (x1 < x && y1 > y) {
        for (int i = 1; i < abs(x - x1); i++) {
            result.emplace_back(x1 + i, y1 - i);
        }
    } else if (x1 > x && y1 < y) {
        for (int i = 1; i < abs(x - x1); i++) {
            result.emplace_back(x1 - i, y1 + i);
        }
    } else if (x1 > x && y1 > y) {
        for (int i = 1; i < abs(x - x1); i++) {
            result.emplace_back(x1 - i, y1 - i);
        }
    }
    return result;
}
