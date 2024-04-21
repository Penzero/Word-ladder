#include "Playing-modes/Analytics-Mode.h"
#include "Playing-modes/Playing-Mode.h"
#include "Playing-modes/Automatic-Mode.h"
#include <iostream>
#include <fstream>

using std::cout, std::cin, std::endl, std::string, std::ifstream, std::vector;

int main(){
    cout << "Welcome to the Word Ladder Game!\n";
    ifstream fin("dictionary.txt");
    if (!fin.is_open()) {
        cout << "Failed to open dictionary file. Exiting.\n";
        return 1;
    }
    vector<string> dictionary;
    while (fin) {
        string word;
        fin >> word;
        if (fin) {
            dictionary.push_back(word);
        }
    }

    while (true) {
        cout << "\nSelect Game Mode:\n";
        cout << "1. Play Mode\n";
        cout << "2. Analytics Mode\n";
        cout << "3. Automatic Mode\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            playing(dictionary);
        } else if (choice == 2) {
            string username;
            cout << "Enter username: ";
            cin >> username;
            analytic(username);
        } else if (choice == 3) {
            string start, target;
            cout << "Enter start word: ";
            cin >> start;
            cout << "Enter target word: ";
            cin >> target;
            automatic(start, target, dictionary);
        } else if (choice == 4) {
            cout << "Exiting.\n";
            return 1;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

    }
    
}