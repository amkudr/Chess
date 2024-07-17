#include "CustExceptions.h"

const char *UnknownPieceException::what() const noexcept {
    return &"Unknown piece " [ piece];
}

const char *NoKingException::what() const noexcept {
    return "No king found";
}
