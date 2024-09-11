#ifndef CHESS_CUSTEXCEPTIONS_H
#define CHESS_CUSTEXCEPTIONS_H
#include "exception"

class NoKingException : public std::exception {
public:
    const char *what() const noexcept override;
};

class UnknownPieceException : public std::exception {
private:
    char piece;
public:
    explicit UnknownPieceException(char piece) : piece(piece) {}

    const char *what() const noexcept override;

};



#endif //CHESS_CUSTEXCEPTIONS_H
