// Chess
#include "Chess.h"
#include "Engine.h"
#include <Windows.h>
#include <iostream>



int main() {
//    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "RNBQKBNR################################################rnbqkbnr";
    string board = "####K#########R####################Q##bk############r###########";
//    string board = "####K#########R#####################Q#bk############r###########";
//	string board = "##########K#############################################r#r#####";
    Engine e(board);
    Chess a(board);

//    int codeResponse;
//    string res;
//
//    // Ходы для быстрого шахмата (дурацкий мат)
//    string moves[] = {"b6c6", "g5e5", "b7d7", "h4d8", };
//    int moveIndex = 0;
//    cout<< e.printBoard() <<endl;
//    cout<<"Best Move "<< e.getBestMove()<<endl;
//
//
//    while (moveIndex < 4) {
//        res = moves[moveIndex++];
//        codeResponse = e.checkMove(res, false);
//        cout<< res << " " << codeResponse <<endl;
//        cout << e.printBoard()<<endl;
//        cout<<"Best Move "<< e.getBestMove()<<endl;
//    }

    int codeResponse;
    string res = a.getInput(e.getBestMove());
    Sleep(1000);

//    string res = a.getInput("");
    while (res != "exit") {
        /*
        codeResponse value :
        Illegal movements :
        11 - there is not piece at the source
        12 - the piece in the source is piece of your opponent
        13 - there one of your pieces at the destination
        21 - illegal movement of that piece
        31 - this movement will cause you checkmate

        legal movements :
        41 - the last movement was legal and cause check
        42 - the last movement was legal, next turn
        43 - the last movement was legal and cause castling
         44 - the last movement was legal and cause checkmate
        */

        /**/
        { // put your code here instead that code
            codeResponse = e.checkMove(res, false);
        }
        /**/

        a.setCodeResponse(codeResponse);
        res = a.getInput(e.getBestMove());
        Sleep(1000);
//        res = a.getInput("");
    }

    cout << endl << "Exiting " << endl;
    return 0;
}

