// Chess
#include "Chess.h"
#include "Engine.h"
#include <Windows.h>
#include <iostream>
#include "CustExceptions.h"


int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "RNBQKBNR################################################rnbqkbnr";
//    string board = "##############R####################Q##bk############r###########";
//    string board = "####K#########R####################Q##bk############r###########";
//	string board = "##########K#############################################r#r#####";
    Engine *e = nullptr;


    try {
        e = new Engine(board);
    } catch (UnknownPieceException &e) {
        cerr << e.what() << endl;
        return 3;

    } catch (NoKingException &e) {
        cerr << e.what() << endl;
        return 2;
    }

    Chess a(board);


    int codeResponse;
    string res = a.getInput(e->getBestMove());

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
            codeResponse = e->checkMove(res, false);
        }
        /**/

        a.setCodeResponse(codeResponse);
        res = a.getInput(e->getBestMove());
    }

    cout << endl << "Exiting " << endl;
    delete e;

    return 0;
}

