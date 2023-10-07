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
        else if((piece == 'Q' || piece == 'q') && isValidQueenMove(fromRow, fromCol, toRow, toCol)){
            return true;
        }
        else if((piece == 'K' || piece == 'k') && isValidKingMove(fromRow, fromCol, toRow, toCol)){
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
        if(board[fromRow][fromCol] == 'N'){
            if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && board[toRow][toCol] == '#' ) {
             return true;
            }else if((dx == 1 && dy == 2) || (dx == 2 && dy == 1) && islower(board[toRow][toCol])) {
            return true;
            }//these code check that attacking knight is larger(white)
        }
        else if (board[fromRow][fromCol] == 'n'){
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
            if((dy<=5) && (fromCol != toCol) && targetPiece == '#'){
            return true;  //these code check that attacking knight is larger(white)
            }
            else if((dy<=5) && (fromCol != toCol) && islower(targetPiece)){
                return true;
            }
        }else if(board[fromRow][fromCol] == 'b'){
           if((dy<=5) && (fromCol != toCol) && targetPiece == '#'){
            return true;  //these code check that attacking knight is larger(white)
            }
            else if((dy<=5) && (fromCol != toCol) && isupper(targetPiece)){
                return true;
            }
        }
            return false;
    }
    
    bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        char piece = board[fromRow][fromCol];
        char targetPiece = board[toRow][toCol];
        if(piece == 'Q'){
            if(((dx == dy || dx == 0 || dy == 0) && (dx != 0 || dy != 0)) && (targetPiece == '#' || islower(targetPiece))){
                return true;
            }
        }
        else if(piece == 'q'){
            if(((dx == dy || dx == 0 || dy == 0) && (dx != 0 || dy != 0)) && (targetPiece == '#' || islower(targetPiece))){
                return true;
            }
        }
        return false;
    }
    
    bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol){
        int dx = abs(toCol - fromCol);
        int dy = abs(toRow - fromRow);
        char piece = board[fromRow][fromCol];
        char targetPiece = board[toRow][toCol];
        if(piece == 'K'){
            if((dx==1 || toRow==fromRow)&&(targetPiece == '#' || islower(targetPiece))){
            return true;
            }
        }
        else if(piece == 'k'){
            if((dx == dy || dx == 0 || dy == 0)&&(targetPiece == '#' || isupper(targetPiece))){
            return true;
            }
        }
        return false;
    }
    
    bool isKingInCheck(char color) {
    // Find the position of the king of the specified color
      char king = (color == 'w') ? 'K' : 'k';
      int kingRow = -1, kingCol = -1;
      for (int row = 0; row < 8; row++) {
          for (int col = 1; col <= 8; col++) {
              if (board[row][col] == king) {
                kingRow = row;
                kingCol = col;
                break;
              }
          }
          if (kingRow != -1) {
            break;
          }
      }
      // Check if the king is under threat from any opponent's piece
      char opponentColor = (color == 'w') ? 'b' : 'w';
      // Check for knight attacks
      int knightDeltas[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
      for (int i = 0; i < 8; i++) {
          int newRow = kingRow + knightDeltas[i][0];
          int newCol = kingCol + knightDeltas[i][1];
          if (isValidMove(kingRow, kingCol, newRow, newCol) && board[newRow][newCol] == opponentColor + 'n') {
              return true; // King is under threat from a knight
              }
      }
      // Check for pawn attacks
      int pawnDeltas[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
      for (int i = 0; i < 4; i++) {
          int newRow = kingRow + pawnDeltas[i][0];
          int newCol = kingCol + pawnDeltas[i][1];
          if (isValidMove(kingRow, kingCol, newRow, newCol) && board[newRow][newCol] == opponentColor + 'p') {
              return true; // King is under threat from a pawn
              }
      }
      // Check for threats from diagonals (queen, bishop)
      int diagDeltas[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
      for (int i = 0; i < 4; i++) {
          for (int dist = 1; dist < 8; dist++) {
              int newRow = kingRow + dist * diagDeltas[i][0];
              int newCol = kingCol + dist * diagDeltas[i][1];
              if (!isValidMove(kingRow, kingCol, newRow, newCol)) {
                  break;
              }
              char piece = board[newRow][newCol];
              if (piece == opponentColor + 'q' || piece == opponentColor + 'b') {
                  return true; // King is under threat from a queen or bishop
                  } else if (piece != '#') {
                      break; // Blocked by another piece
                      }
          }
      }

       // Check for threats in vertical and horizontal directions (queen, rook)
      int straightDeltas[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};\
       for (int i = 0; i < 4; i++) {
           for (int dist = 1; dist < 8; dist++) {
               int newRow = kingRow + dist * straightDeltas[i][0];
               int newCol = kingCol + dist * straightDeltas[i][1];
               if (!isValidMove(kingRow, kingCol, newRow, newCol)) {
                   break;
               }
               char piece = board[newRow][newCol];
               if (piece == opponentColor + 'q' || piece == opponentColor + 'r') {
                   return true; // King is under threat from a queen or rook
               } else if (piece != '#') {
                   break; // Blocked by another piece
               }
           }
       }
       return false; // King is not in check
    }

    
    bool isCheckmate(char color) {
    // Find the king's position
    int kingRow = -1, kingCol = -1;
    char king = (color == 'w') ? 'K' : 'k';
    for (int row = 0; row < 8; row++) {
        for (int col = 1; col <= 8; col++) {
            if (board[row][col] == king) {
                kingRow = row;
                kingCol = col;
                break;
            }
        }
    }
    if (kingRow == -1 || kingCol == -1) {// King not found, something is wrong
        return false;
    }
    // Check if the king can move to an empty square
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) {
                continue; // Skip the current position
            }
            int newRow = kingRow + dy;
            int newCol = kingCol + dx;
            if (isValidMove(kingRow, kingCol, newRow, newCol) && board[newRow][newCol] == '#') {
                return false; // King can escape check
            }
        }
    }
    // Check if any piece can capture the checking piece or block its path (for queen, rook, bishop)
    for (int row = 0; row < 8; row++) {
        for (int col = 1; col <= 8; col++) {
            char piece = board[row][col];
            if ((color == 'w' && isupper(piece)) || (color == 'b' && islower(piece))) {// This piece is of the same color as the king
                for (int newRow = 0; newRow < 8; newRow++) {
                    for (int newCol = 1; newCol <= 8; newCol++) {
                        if (isValidMove(row, col, newRow, newCol)) {
                            char targetPiece = board[newRow][newCol];
                            // Simulate the move and check if it removes the threat
                            char temp = board[newRow][newCol];
                            board[newRow][newCol] = board[row][col];
                            board[row][col] = '#';

                            bool inCheck = isKingInCheck(color);

                            // Undo the move
                            board[row][col] = board[newRow][newCol];
                            board[newRow][newCol] = temp;

                            if (!inCheck) {
                                return false; // The threat can be removed
                            }
                        }
                    }
                }
            }
        }
    }
    // If none of the above conditions are met, it's checkmate
    return true;
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

        // Check for checkmate after each move
        if (chess.isCheckmate('w')) {
            cout << "Checkmate! Black wins!" << endl;
            break;
        } else if (chess.isCheckmate('b')) {
            cout << "Checkmate! White wins!" << endl;
            break;
        }
    }
    return 0;
}
