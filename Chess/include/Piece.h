#ifndef PIECE_H
#define PIECE_H
#include "vector"
#include <utility>
using namespace std;
class Piece{
    int x;
    int y;
    bool isWhite_;
    bool isMoved_ = false;


public:
    Piece(int x, int y, bool isWhite);

    bool isWhite() const;

    int getX() const;

    int getY() const;

    void setX(int x);

    void setY(int y);

    bool isMoved() const;

    void setIsMoved(bool isMoved);

    virtual char getSymbol() const;

    virtual bool isPossibleMove(int x_, int y_) const;

    virtual vector<pair<int, int>> getPotentialRoadblocks(int x, int y) const;

//    ~Piece();

};
#endif // PIECE_H
