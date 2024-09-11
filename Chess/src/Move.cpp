#include "Move.h"

int Move::operator<(const Move &other) const {
    return value < other.value;
}
