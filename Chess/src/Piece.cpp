#include "Piece.h"

Piece::Piece(int x, int y, bool isWhite) {
    this->isWhite_ = isWhite;
    this->x = x;
    this->y = y;
}

bool Piece::isWhite() const {
    return isWhite_;
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

void Piece::setX(int x) {
    Piece::x = x;
}

void Piece::setY(int y) {
    Piece::y = y;
}

char Piece::getSymbol() const {
    return '0';
}

bool Piece::isPossibleMove(int x, int y) const {

    return false;
}

vector<pair<int, int>> Piece::needToCheckWay(int x, int y) const {
    return {};
}
