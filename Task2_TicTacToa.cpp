#include <iostream>
#include <vector>

const int BOARD_SIZE = 3;

// Function to initialize the game board
void initializeBoard(std::vector<std::vector<char> >& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::vector<char> row(BOARD_SIZE, ' ');
        board.push_back(row);
    }
}

// Function to display the game board
void displayBoard(const std::vector<std::vector<char> >& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j];
            if (j < BOARD_SIZE - 1) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
        if (i < BOARD_SIZE - 1) {
            std::cout << "---------" << std::endl;
        }
    }
}

// Function to check for a win
bool checkWin(const std::vector<std::vector<char> >& board, char mark) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) {
            return true; // Horizontal win
        }
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) {
            return true; // Vertical win
        }
    }
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) {
        return true; // Diagonal win (top-left to bottom-right)
    }
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) {
        return true; // Diagonal win (top-right to bottom-left)
    }
    return false; // No win
}

// Function to check for a draw
bool checkDraw(const std::vector<std::vector<char> >& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return false; // At least one empty cell
            }
        }
    }
    return true; // All cells filled (draw)
}

// Function to display the winner or a draw message
void displayResult(const std::vector<std::vector<char> >& board, char mark) {
    system("clear"); // Clear the screen (Linux/macOS)
    displayBoard(board);
    if (mark == ' ') {
        std::cout << "It's a draw!" << std::endl;
    } else {
        std::cout << "Player " << ((mark == 'X') ? "1" : "2") << " wins!" << std::endl;
    }
}

int main() {
    std::vector<std::vector<char> > board;
    initializeBoard(board);

    bool player1Turn = true;
    char winner = ' ';
    int moves = 0;

    while (winner == ' ') {
        system("clear"); // Clear the screen (Linux/macOS)
        displayBoard(board);

        int row, col;
        char mark = (player1Turn) ? 'X' : 'O';
        std::cout << "Player " << (player1Turn ? "1" : "2") << ", enter your move (row and column): ";
        std::cin >> row >> col;

        if (row >= 1 && row <= BOARD_SIZE && col >= 1 && col <= BOARD_SIZE && board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = mark;
            moves++;
            player1Turn = !player1Turn; // Switch players

            if (checkWin(board, mark)) {
                winner = mark;
                displayResult(board, mark);
            } else if (checkDraw(board)) {
                winner = 'D';
                displayResult(board, ' ');
            }
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    return 0;
}
