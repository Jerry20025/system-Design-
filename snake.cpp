#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

class SnakeAndLadder {
private:
    int playerPosition[2];  // Two players
    int board[101];  // Board with 100 squares

public:
    SnakeAndLadder() {
        // Initialize players' positions to 0
        playerPosition[0] = playerPosition[1] = 0;

        // Initialize board
        for (int i = 1; i <= 100; i++) {
            board[i] = i;
        }

        // Adding some snakes
        board[16] = 6;
        board[47] = 26;
        board[49] = 11;
        board[87] = 24;
        board[56] = 53;

        // Adding some ladders
        board[3] = 22;
        board[5] = 8;
        board[15] = 25;
        board[48] = 59;
        board[77] = 96;
    }

    void rollDice(int player) {
        int dice = (rand() % 6) + 1;  // Dice roll between 1 to 6
        cout << "Player " << player + 1 << " rolled a " << dice << endl;
        
        // Move player by dice value
        playerPosition[player] += dice;

        // Check if player goes beyond board (100)
        if (playerPosition[player] > 100) {
            playerPosition[player] = 100;
        }

        // Add delay before checking snake or ladder
        this_thread::sleep_for(chrono::seconds(1));

        // Check if landed on snake or ladder
        if (board[playerPosition[player]] != playerPosition[player]) {
            cout << "Player " << player + 1 << " encountered a ";
            if (board[playerPosition[player]] < playerPosition[player]) {
                cout << "snake! Sliding down to " << board[playerPosition[player]] << endl;
            } else {
                cout << "ladder! Climbing up to " << board[playerPosition[player]] << endl;
            }
            playerPosition[player] = board[playerPosition[player]];
        }

        // Add delay before printing position
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Player " << player + 1 << " is now at position " << playerPosition[player] << endl;
    }

    bool isGameWon(int player) {
        return playerPosition[player] == 100;
    }
};

int main() {
    srand(time(0));  // Initialize random seed

    SnakeAndLadder game;
    int currentPlayer = 0;  // Player 1 starts first

    while (true) {
        game.rollDice(currentPlayer);

        // Check if the current player won
        if (game.isGameWon(currentPlayer)) {
            cout << "Player " << currentPlayer + 1 << " wins!" << endl;
            break;
        }

        // Switch playerw
        currentPlayer = 1 - currentPlayer;

        // Add delay before next player's turn
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
