#include "Knight.h"

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite) {

}

char Knight::getSymbol() const {
    return isWhite() ? 'N' : 'n';
}

bool Knight::isPossibleMove(int x, int y) const {
    if (abs(x - getX()) == 2 && abs(y - getY()) == 1) {
        return true;
    }
    if (abs(x - getX()) == 1 && abs(y - getY()) == 2) {
        return true;
    }
    return false;
}

vector<pair<int, int>> Knight::getPotentialRoadblocks(int x, int y) const {
    return {};
}

int Knight::getValue() const {
    return 3;
}
