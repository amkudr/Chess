#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <string>

using namespace std;


class Move {
public:

    string move;
    int value;


    Move(string move, int value) : move(std::move(move)), value(value) {}
    int operator<(const Move &other) const;

    string getMove() const { return move; }

    int getValue() const { return value; }


};

#endif //CHESS_MOVE_H
