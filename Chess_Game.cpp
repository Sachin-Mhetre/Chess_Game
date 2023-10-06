#include <iostream>
#include <cstdlib>
using namespace std;

class chess {
private:
    char board[9][11];

public:
    chess() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 11; col++) {
                board[row][col] = ' ';
            }
        }

        // Initialize row labels (12345678)
        for (int row = 0; row <= 8; row++) {
            board[8 - row][0] = '0' + row;
        }

        // Initialize column labels (abcdefgh)
        for (int col = 0; col < 8; col++) {
            board[8][col + 1] = 'a' + col;
        }

        for (int row = 2; row < 8; row++) {
            for (int col = 1; col < 9; col++) {
                board[row][col] = '#';
            }
        }

        // Initialize pawn positions
        for (int col = 1; col < 9; col++) {
            board[6][col] = 'P'; // white pawns
            board[1][col] = 'p'; // black pawns
        }

        // Initialize other pieces as needed
        board[0][1] = 'r'; // black rooks
        board[0][8] = 'r';
        board[7][1] = 'R'; // white rooks
        board[7][8] = 'R';

        board[0][2] = 'n'; // black knights
        board[0][7] = 'n';
        board[7][2] = 'N'; // white knights
        board[7][7] = 'N';

        board[0][3] = 'b'; // black bishops
        board[0][6] = 'b';
        board[7][3] = 'B'; // white bishops
        board[7][6] = 'B';

        board[0][4] = 'q'; // black queen
        board[7][4] = 'Q'; // white queen

        board[0][5] = 'k'; // black king
        board[7][5] = 'K'; // white king
    }

    void display() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 11; col++) {
                char piece = board[row][col];
                if (piece != ' ') {
                    cout << piece << ' ';
                } else {
                    cout << board[row][col] << ' ';
                }
            }
            cout << endl;
        }
    }

    void makeMove(int fromRow, int fromCol, int toRow, int toCol) {
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = '#';
    }

    void readMove(const char move[]) {
        int fcol = (move[0] - 'a') + 1;
        int frow = 8 - (move[1] - '0');
        int tcol = (move[6] - 'a') + 1;
        int trow = 8 - (move[7] - '0');

        if (isValidMove(frow, fcol, trow, tcol)) {
            makeMove(frow, fcol, trow, tcol);
        } else {
            cout << "Invalid move!" << endl;
        }
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (fromRow < 0 || fromRow > 8 || fromCol < 1 || fromCol > 8 ||
            toRow < 1 || toRow > 8 || toCol < 1 || toCol > 8) {
            return false; // Check if coordinates are within bounds
        }

        char piece = board[fromRow][fromCol];
        char targetPiece = board[toRow][toCol];

        if ((piece == 'P' || piece == 'p') && isValidPawnMove(fromRow, fromCol, toRow, toCol)) {
            return true;
        } else if ((piece == 'N' || piece == 'n') && isValidKnightMove(fromRow, fromCol, toRow, toCol)) {
            return true;
        }
        else if((piece == 'R' || piece == 'r') && isValidRookMove(fromRow, fromCol, toRow, toCol)){
            return true;
        }
        else if((piece == 'B' || piece == 'b') && isValidBishopMove(fromRow, fromCol, toRow, toCol)){
            return true;
        }
        // Add cases for other pieces as needed
        // ...

        // Default case: invalid piece or unknown piece
        return false;
    }

    bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (board[fromRow][fromCol] == 'P') {
            // White Pawn
            if ((fromRow - toRow) == 1 && fromCol == toCol && board[toRow][toCol] == '#') {
                return true; // Valid one-step forward move
            } else if (fromRow == 6 && (fromRow - toRow) == 2 && fromCol == toCol && board[toRow][toCol] == '#' && board[fromRow - 1][fromCol] == '#') {
                return true; // Valid two-step forward move from the starting position
            } else if ((fromRow - toRow) == 1 && abs(fromCol - toCol) == 1 && islower(board[toRow][toCol])) {
                return true; // Valid capture move
            }
        } else if (board[fromRow][fromCol] == 'p') {
            // Black Pawn
            if ((toRow - fromRow) == 1 && fromCol == toCol && board[toRow][toCol] == '#') {
                return true; // Valid one-step forward move
            } else if (fromRow == 1 && (toRow - fromRow) == 2 && fromCol == toCol && board[toRow][toCol] == '#' && board[fromRow + 1][fromCol] == '#') {
                return true; // Valid two-step forward move from the starting position
            } else if ((toRow - fromRow) == 1 && abs(toCol - fromCol) == 1 && isupper(board[toRow][toCol])) {
                return true; // Valid capture move
            }
        }

        return false;
    }

    bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        if(board[fromRow][fromCol] == 'K'){
            if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && board[toRow][toCol] == '#' ) {
             return true;
            }else if((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && islower(board[toRow][toCol])) {
            return true;
            }//these code check that attacking knight is larger(white)
        }
        else if (board[fromRow][fromCol] == 'k'){
            if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && board[toRow][toCol] == '#' ) {
             return true;
            }
            else if((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && isupper(board[toRow][toCol])) {
            return true; //these code check that attacking knight is smaller(black)
            }
        }
        return false;
    }
    
    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol){
        if(board[fromRow][fromCol] == 'K'){
            if((fromCol == toCol) || (fromRow == toRow) && board[toRow][toCol] == '#'){
                return true;
            }else if((fromCol == toCol) || (fromRow == toRow) && islower(board[toRow][toCol])) {
            return true;  //these code check that attacking knight is larger(white)
            }
        }else if (board[fromRow][fromCol] == 'k'){
            if((fromCol == toCol) || (fromRow == toRow) && board[toRow][toCol] == '#'){
                return true;
            }
            else if((fromCol == toCol) || (fromRow == toRow) && isupper(board[toRow][toCol])) {
            return true; //these code check that attacking knight is smaller(black)
            }
        }
            return false;
    }
    
    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        char piece = board[fromRow][fromCol];
        char targetPiece = board[toRow][toCol];
        if(board[fromRow][fromCol] == 'B'){
            if(((dy == 1) || (dy==2) || (dy==3) || (dy==4) || (dy==5)) && targetPiece != '#' && islower(piece) && isupper(targetPiece)){
            return true;  //these code check that attacking knight is larger(white)
            }
        }else if(board[fromRow][fromCol] == 'b'){
           if(((dy == 1) || (dy==2) || (dy==3) || (dy==4) || (dy==5)) && targetPiece != '#' && islower(targetPiece) && isupper(piece)){
            return true; //these code check that attacking knight is smaller(black)
            }
        }
            return false;
    }
};

int main() {
    char movearr[10];
    chess chess;
    cout << "Game has started!" << endl;
    while (1) {
        chess.display();
        cout << "Enter Move: ";
        cin.getline(movearr, sizeof(movearr));
        chess.readMove(movearr);
    }
    return 0;
}
