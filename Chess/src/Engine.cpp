
#include <sstream>
#include <iostream>
#include "Engine.h"
#include "Queen.h"
#include "Bishop.h"
#include "Pawn.h"
#include "Knight.h"

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
                case 'P':
                    m_board[col][row] = make_shared<Pawn>(col, row, true);
                    break;
                case 'p':
                    m_board[col][row] = make_shared<Pawn>(col, row, false);
                    break;
                case 'N':
                    m_board[col][row] = make_shared<Knight>(col, row, true);
                    break;
                case 'n':
                    m_board[col][row] = make_shared<Knight>(col, row, false);
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


    int curX = move[0] - 'a';
    int curY = move[1] - '1';
    int nextX = move[2] - 'a';
    int nextY = move[3] - '1';

    shared_ptr<Piece> piece = m_board[curX][curY];
    if (piece == nullptr) {
        return 11;
    }
    if (piece->isWhite() != white_turn) {
        return 12;
    }
    if (m_board[nextX][nextY] != nullptr &&
        m_board[nextX][nextY]->isWhite() == white_turn) {
        return 13;
    }
    if (!piece->isPossibleMove(nextX, nextY)) {
        return 21;
    }
    if (piece->getSymbol() == 'P' || piece->getSymbol() == 'p') {
        // Check pawn's movement
        if (nextY != curY) {
            // Pawn moves diagonally
            if (m_board[nextX][nextY] == nullptr) {
                // If the pawn moves diagonally but there's no piece to capture
                return 21;
            }
        } else {
            // Pawn moves straight
            if (m_board[nextX][nextY] != nullptr) {
                // If the pawn moves straight but there's a piece in the destination
                return 21;
            }
        }
    }

    vector<pair<int, int>> way = piece->getPotentialRoadblocks(nextX, nextY);
    for (auto &p: way) {
        if (m_board[p.first][p.second] != nullptr) {
            return 21; //illegal movement
        }

    }
    //Make the move
    movePiece(curX, curY, nextX, nextY);

    if (isCheck(false)) {
        //if check undo
        movePiece(nextX, nextY, curX, curY);

        return 31;
    }
    //Check if the move will cause check
    bool causeCheck = isCheck(true);
    if (causeCheck) {
        if (isCheckmate()) {
            return 43;
        }
        else return 41;

    }
    white_turn = !white_turn;
    return 42;
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
        king = white_turn ? black_king : white_king;
        enemyColor = white_turn;
    } else king = white_turn ? white_king : black_king;
    if (king != nullptr) {
        for (auto &i: m_board) {
            for (const auto &j: i) {
                if (j != nullptr && j->isWhite() == enemyColor) { //Check all enemy pieces
                    if (j->isPossibleMove(king->getX(), king->getY())) { //If enemy piece can attack king
                        vector<pair<int, int>> way = j->getPotentialRoadblocks(king->getX(),
                                                                               king->getY()); //check if there is a flap fot the king
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
    if (piece->getSymbol() == ('P' | 'p')) { //If the piece is a pawn
        dynamic_pointer_cast<Pawn>(piece)->setFirstMove(false);
    }
}

bool Engine::isCheckmate() {
    /**
     * Check if the king is in checkmate
     * @return true if the king is in checkmate
     */
    white_turn = !white_turn;
    for (int xi = 0; xi < SIZE_B; xi++) {
        for (int yi = 0; yi < SIZE_B; yi++) {
            if (m_board[xi][yi] != nullptr && m_board[xi][yi]->isWhite() == white_turn) {
                for (int xj = 0; xj < SIZE_B; xj++) {
                    for (int yj = 0; yj < SIZE_B; yj++) {
                        string moveCheck =
                                string(1, xi + 'a') + to_string(yi + 1) + string(1, xj + 'a') + to_string(yj + 1);
                        int res = checkMove(moveCheck);
                        if (res == 42 || res == 41) {
                            movePiece(xj, yj, xi, yi); //undo the move
                            white_turn = !white_turn;
                            std::cout << "All good " << moveCheck << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    white_turn = !white_turn;
    return true;
}
