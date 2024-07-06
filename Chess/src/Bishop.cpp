#include "Bishop.h"

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite) {

}

char Bishop::getSymbol() const {
    return isWhite() ? 'B' : 'b';
}

bool Bishop::isPossibleMove(int x, int y) const {
    if (abs(x - getX()) == abs(y - getY())) {
        return true;
    }
    return false;
}

vector<pair<int, int>> Bishop::getPotentialRoadblocks(int x, int y) const {
    vector<pair<int, int>> result;
    int x1 = getX();
    int y1 = getY();
    if (x1 < x && y1 < y) {
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
