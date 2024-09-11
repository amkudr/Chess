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

bool Piece::isPossibleMove(int x_, int y_) const {
    /**
     * Check if the move is possible by the piece
     */

    return false;
}

vector<pair<int, int>> Piece::getPotentialRoadblocks(int x, int y) const {
    /**
     * Check if the way is clear for the piece to move
     */
    return {};
}

bool Piece::isFirstMove() const {
    return isMoved_;
}

void Piece::setIsMoved(bool isMoved) {
    isMoved_ = isMoved;
}

int Piece::getValue() const {
    return 0;
}
