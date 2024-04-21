#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>

using std::cout, std::cin, std::endl, std::string, std::ifstream, std::set, std::vector, std::istringstream, std::stoi, std::accumulate;

void analytic(const string& username) {
    ifstream fin(username + ".csv");
    if (!fin.is_open()) {
        cout << "No previous data found for " << username << ". Starting a new game." << endl;
        return;
    }

    string line;
    set<string> uniqueWords;
    vector<int> movesPerGame;
    vector<int> hintsPerGame;
    int currentHighestMove = 0;
    int currentHints = 0;
    bool isFirstLine = true;

    while (getline(fin, line)) {
        if (line.empty() || line == "Move,Word,Action") { 
            if (!isFirstLine) {
                movesPerGame.push_back(currentHighestMove);
                hintsPerGame.push_back(currentHints); // Reset counters for a new game
                currentHighestMove = 0;
                currentHints = 0;
            }
           
            isFirstLine = false;
            continue;
        }

        istringstream iss(line);
        vector<string> tokens;
        string token;

        // Parse the CSV line
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 3) continue; // Skip malformed lines

        int moveNumber = stoi(tokens[0]);
        string word = tokens[1];
        string action = tokens[2];

        if(action != "Invalid move" && word != "hint")
            uniqueWords.insert(word);

        // Update highest move number observed for current game
        if (moveNumber > currentHighestMove) {
            currentHighestMove = moveNumber;
        }

        if (word.find("hint") != string::npos) {
            currentHints++;
        }

        if (action == "Found target") {
            movesPerGame.push_back(currentHighestMove); // Include this move
            hintsPerGame.push_back(currentHints);
            currentHighestMove = 0;
            currentHints = 0;
            isFirstLine = true; // Indicate a new game can start
        }
    }

    if(!isFirstLine) {
        movesPerGame.push_back(currentHighestMove);
        hintsPerGame.push_back(currentHints);
    }

    // Close file
    fin.close();

    // Calculate and display statistics
    cout << "Total unique words used by " << username << ": " << uniqueWords.size() << endl;
    cout << "Total games played: " << movesPerGame.size() << endl;
    if (!movesPerGame.empty()) {
        double avgMoves = accumulate(movesPerGame.begin(), movesPerGame.end(), 0.0) / movesPerGame.size();
        cout << "Average moves per game: " << avgMoves << endl;
    }
    if (!hintsPerGame.empty()) {
        double avgHints = accumulate(hintsPerGame.begin(), hintsPerGame.end(), 0.0) / hintsPerGame.size();
        cout << "Average hints requested per game: " << avgHints << endl;
    }
}
