// Chess 
#include "Chess.h"
#include "Engine.h"

int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
//    string board = "RNBQKBNR################################################rnbqkbnr";
//	string board = "##########K#############################################r#r#####";
    Engine e(board);
    Chess a(board);

    int codeResponse;
    string res = a.getInput();
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
        */

        /**/
        { // put your code here instead that code
            codeResponse = e.checkMove(res);
        }
        /**/

        a.setCodeResponse(codeResponse);
        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}

