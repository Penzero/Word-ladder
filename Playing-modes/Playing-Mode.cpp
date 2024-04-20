#include "Playing-Mode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using std::string, std::vector, std::cout, std::endl, std::cin, std::ofstream;

void game(const vector<string>& dictionary) {
    Graph<string> graph;
    populateGraph(graph, dictionary);
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number generator

    string start, target, name;
    cout << "Enter your name: ";
    cin >> name;

    ofstream fout(name + ".csv", std::ios::app);
    if (!fout.is_open()) {
        cout << "Failed to open file to record game progress." << endl;
        return;
    }

    fout << "Move,Word,Action" << endl; // CSV header

    cout << "Hello " << name << "!" << endl;
    cout << "Enter the number of letters the word should have: ";
    int length;
    cin >> length;

    do {
        start = dictionary[rand() % dictionary.size()];
        target = dictionary[rand() % dictionary.size()];
    } while (start.size() != length || target.size() != length || start == target);

    cout << "The start word is: " << start << " and the target word is: " << target << endl;
    vector<string> path = BFS(graph, start, target);
    string lastWord = start, word;
    vector<string> wordsUsed; 
    wordsUsed.push_back(start); 
    int hints = 0, moves = 1;

    while (true) {
        cout << "Enter the next word (type 'hint' for a hint or 'quit' to quit): ";
        cin >> word;

        fout << moves << "," << word << ",";

        if (word == "quit") {
            cout << "You quit the game." << endl;
            fout << "Quit" << endl;
            break;
        } else if (word == "hint") {
            hints++;
            fout << "Requested hint,";
            path = BFS(graph, lastWord, target);
            if (path.size() <= 1) {
                cout << "No path found." << endl;
                fout << "No path available" << endl;
            } else {
                cout << "Hint: ";
                for (int i = 0; i < path[1].length(); ++i) {
                    if (lastWord[i] != path[1][i]) {
                        cout << "\033[1;31m" << path[1][i] << "\033[0m"; // Red color for different letter
                    } else {
                        cout << path[1][i];
                    }
                }
                cout << endl;
                fout << "Given hint," << path[1] << endl;
            }
        } else if (word == target) {
            cout << "Congratulations! You found the target word!" << endl;
            wordsUsed.push_back(word);
            fout << "Found target" << endl;
            break;
        } else if (lastWord == word || word.size() != length || !isInDictionary(word, dictionary) || !graph.hasEdge(lastWord, word)) {
            if (lastWord == word) cout << "You entered the same word as the last one. Try again." << endl;
            else if (word.size() != length) cout << "The word should have " << length << " letters. Try again." << endl;
            else if (!isInDictionary(word, dictionary)) cout << "The word is not in the dictionary. Try again." << endl;
            else cout << "The new word must have only one letter changed from the last one. Try again." << endl;
            fout << "Invalid move" << endl;
            continue;
        } else {
            lastWord = word;
            wordsUsed.push_back(word);
            fout << "Valid move" << endl;
        }
        moves++;
    }

    fout.close();

    // Print game summary
    cout << "Game summary:" << endl;
    cout << "Start word: " << start << " | Target word: " << target << endl;
    cout << "Total moves: " << moves << " | Total hints: " << hints << endl;
    cout << "Words used: ";
    for (const auto& usedWord : wordsUsed) cout << usedWord << " ";
    cout << endl;
    cout << "The optimal number of moves was: " << path.size() - 1 << endl;
}

