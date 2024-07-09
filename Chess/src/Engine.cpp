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

int Engine::checkMove(string move, bool checkmateV) {
    /**
     * Check if the move is legal
     * @param move - string with the move
     * @param checkmateV - if true check if the move called from isCheckmate
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

    bool isCastling = false;
    if ((piece->getSymbol() == 'K' && curY == 4 && curX == 0 &&
         ((nextY == 6 && nextX == 0 &&
           m_board[0][5] == nullptr && m_board[0][6] == nullptr &&
           m_board[0][7] != nullptr && m_board[0][7]->getSymbol() == 'R' &&
           !m_board[0][7]->isMoved() && !piece->isMoved()) ||
          (nextY == 1 && nextX == 0 &&
           m_board[0][1] == nullptr && m_board[0][2] == nullptr && m_board[0][3] == nullptr &&
           m_board[0][0] != nullptr && m_board[0][0]->getSymbol() == 'R' &&
           !m_board[0][0]->isMoved() && !piece->isMoved()))) ||
        (piece->getSymbol() == 'k' && curY == 4 && curX == 7 &&
         ((nextY == 6 && nextX == 7 &&
           m_board[7][5] == nullptr && m_board[7][6] == nullptr &&
           m_board[7][7] != nullptr && m_board[7][7]->getSymbol() == 'r' &&
           !m_board[7][7]->isMoved() && !piece->isMoved()) ||
          (nextY == 1 && nextX == 7 &&
           m_board[7][1] == nullptr && m_board[7][2] == nullptr && m_board[7][3] == nullptr &&
           m_board[7][0] != nullptr && m_board[7][0]->getSymbol() == 'r' &&
           !m_board[7][0]->isMoved() && !piece->isMoved())))) {
        isCastling = true;
        movePiece(curX, curY, nextX, nextY);

        if (nextY == 6 && nextX == 0) {
            movePiece(0, 7, 0, 5); // White short castling
        } else if (nextY == 1 && nextX == 0) {
            movePiece(0, 0, 0, 3); // White long castling
        } else if (nextY == 6 && nextX == 7) {
            movePiece(7, 7, 7, 5); // Black short castling
        } else if (nextY == 1 && nextX == 7) {
            movePiece(7, 0, 7, 3); // Black long castling
        }
    } else if ((piece->getSymbol() == 'k' | piece->getSymbol() == 'K') && (abs(nextY - curY) > 1) || abs(nextX - curX) > 1){
        return 21; //Castling is not possible
    } else {
        vector<pair<int, int>> way = piece->getPotentialRoadblocks(nextX, nextY);
        for (auto &p: way) {
            if (m_board[p.first][p.second] != nullptr) {
                return 21; //illegal movement
            }
        }
        // Make the move
        movePiece(curX, curY, nextX, nextY);
    }

    if (isCheck(false)) {
        // if check, undo the move and castling if applicable
        movePiece(nextX, nextY, curX, curY);
        piece->setIsMoved(false);
        if (isCastling) {
            if (nextY == 6 && nextX == 0) {
                movePiece(0, 5, 0, 7); // Undo white short castling
                m_board[0][7]->setIsMoved(false);
            } else if (nextY == 2 && nextX == 0) {
                movePiece(0, 3, 0, 0); // Undo white long castling
                m_board[0][0]->setIsMoved(false);
            } else if (nextY == 6 && nextX == 7) {
                m_board[7][7]->setIsMoved(false);
                movePiece(7, 5, 7, 7); // Undo black short castling
            } else if (nextY == 2 && nextX == 7) {
                m_board[7][0]->setIsMoved(false);
                movePiece(7, 3, 7, 0); // Undo black long castling
            }
        }
        return 31;
    }

    // Check if the move causes check
    bool causeCheck = isCheck(true);
    if (causeCheck) {
        if (!checkmateV && isCheckmate()) { // Check if the move causes checkmate only if checkmateV is true(not called from isCheckmate)
            return 44; // checkmateV
        } else {
            piece->setIsMoved(true);
            return isCastling? 43:41; // Check
        }
    }

    white_turn = !white_turn;
    piece->setIsMoved(true);

    return isCastling ? 43 : 42; // Castling or regular move
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
    } else {
        king = white_turn ? white_king : black_king;
    }
    if (king != nullptr) {
        for (auto &col: m_board) {
            for (auto &piece: col) {
                if (piece != nullptr && piece->isWhite() == enemyColor) {
                    if (piece->isPossibleMove(king->getX(), king->getY())) {
                        vector<pair<int, int>> way = piece->getPotentialRoadblocks(king->getX(), king->getY());
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
    piece->setIsMoved(true);

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
                        bool isFirstMove = m_board[xi][yi]->isMoved();
                        int res = checkMove(moveCheck, true);
                        if (res == 42 || res == 41 || res == 43) {
                            movePiece(xj, yj, xi, yi); // Undo the move
                            m_board[xi][yi]->setIsMoved(isFirstMove);
                            white_turn = !white_turn;
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
