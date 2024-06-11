
#include <sstream>
#include "Engine.h"
#include "Queen.h"
#include "Bishop.h"

Engine::Engine(const string &start) {
    int index = 0;

    for (int col = 0; col < SIZE_B; col++) {
        for (int row = 0; row < SIZE_B; row++) {
            switch (start[index]) {
                case 'R':
                    m_board[col][row] = make_shared<Rook>(col, row, true);
                    break;
                case 'r':
                    m_board[col][row] = make_shared<Rook>(col, row, false);
                    break;
                case '#':
                    m_board[col][row] = nullptr;
                    break;
                case 'p':
                    m_board[col][row] = make_shared<Piece>(col, row, false);
                    break;
                case 'K':
                    m_board[col][row] = make_shared<King>(col, row, true);
                    white_king = dynamic_pointer_cast<King>(m_board[col][row]);
                    break;
                case 'k':
                    m_board[col][row] = make_shared<King>(col, row, false);
                    black_king = dynamic_pointer_cast<King>(m_board[col][row]);
                    break;
                case 'Q':
                    m_board[col][row] = make_shared<Queen>(col, row, true);
                    break;
                case 'q':
                    m_board[col][row] = make_shared<Queen>(col, row, false);
                    break;
                case 'B':
                    m_board[col][row] = make_shared<Bishop>(col, row, true);
                    break;
                case 'b':
                    m_board[col][row] = make_shared<Bishop>(col, row, false);
                    break;

                default:
                    m_board[col][row] = make_shared<Piece>(col, row, true); //TODO later
            }
            index++;
        }
    }

}

string Engine::printBoard() {
    ostringstream os;
    for (auto &col: m_board) {
        for (auto &row: col) {
            if (row == nullptr) {
                os << "#";
            } else {
                os << row->getSymbol();
            }
        }
        os << endl;
    }
    return os.str();
}

int Engine::checkMove(string move) {
    /**
     * Check if the move is legal
     * @param move - string with the move
     * @return code response
     */
    shared_ptr<Piece> piece = m_board[move[0] - 'a'][move[1] - '1'];
    if (piece == nullptr) {
        return 11;
    }
    if (piece->isWhite() != white_turn) {
        return 12;
    }
    if (m_board[move[2] - 'a'][move[3] - '1'] != nullptr &&
        m_board[move[2] - 'a'][move[3] - '1']->isWhite() == white_turn) {
        return 13;
    }
    if (!piece->isPossibleMove(move[2] - 'a', move[3] - '1')) {
        return 21;
    }
    vector<pair<int, int>> way = piece->needToCheckWay(move[2] - 'a', move[3] - '1');
    for (auto &p: way) {
        if (m_board[p.first][p.second] != nullptr) {
            return 21; //illegal movement
        }
    }
    //Make the move
    movePiece(move[0] - 'a', move[1] - '1', move[2] - 'a', move[3] - '1');

    if (isCheck(false)) {
        //if check undo
        movePiece(move[2] - 'a', move[3] - '1', move[0] - 'a', move[1] - '1');
        return 31;
    }
    //Check if the move will cause check
    bool causeCheck = isCheck(true);

    white_turn = !white_turn;
    return causeCheck ? 41 : 42;

}

bool Engine::isCheck(bool goodCheck) {
    /**
     * Check if the king is in check
     * @param goodCheck - if true check if the enemy king is in check after the move
     * @return true if the king is in check
     */
    shared_ptr<King> king;
    bool enemyColor = !white_turn;
    if (goodCheck) {
        king = white_turn ? black_king:white_king;
        enemyColor = white_turn;
    }
    else king = white_turn ? white_king : black_king;
    if (king != nullptr){
        for (auto & i : m_board) {
            for (const auto & j : i) {
                if (j != nullptr && j->isWhite() == enemyColor) { //Check all enemy pieces
                    if (j->isPossibleMove(king->getX(), king->getY())) { //If enemy piece can attack king
                        vector<pair<int, int>> way = j->needToCheckWay(king->getX(), king->getY()); //check if there is a flap fot the king
                        bool isCheck = true;
                        for (auto &p: way) {
                            if (m_board[p.first][p.second] != nullptr) {
                                isCheck = false;
                                break;
                            }
                        }
                        if (isCheck) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

void Engine::movePiece(int x_from, int y_from, int x_to, int y_to) {
    /**
     * Move piece from x_from, y_from to x_to, y_to
     * @param x_from - x coordinate of the piece
     * @param y_from - y coordinate of the piece
     * @param x_to - x coordinate of the destination
     * @param y_to - y coordinate of the destination
     */
    shared_ptr<Piece> piece = m_board[x_from][y_from];
    m_board[x_to][y_to] = piece;
    m_board[x_from][y_from] = nullptr;
    piece->setX(x_to);
    piece->setY(y_to);
}
