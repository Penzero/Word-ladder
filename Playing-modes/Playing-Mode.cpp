#include "Playing-Mode.h"
#include <iostream>

using std::string, std::vector, std::cout, std::endl, std::cin;

void game(const std::vector<std::string>& dictionary){
    Graph<string> graph;
    populateGraph(graph, dictionary);
    string start, target;
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Hello " << name << "!" << endl;
    cout << "Enter the number of letters the word should have: ";
    int length;
    cin >> length;
    //Choose a random word of the given length
    do{
        start = dictionary[rand() % dictionary.size()];
        target = dictionary[rand() % dictionary.size()];
    } while(start.size() != length);
    
    cout << "The start word is: " << start << " and the target word is: " << target << endl;
    vector<string> path = BFS(graph, start, target);
    string lastWord, word;
    lastWord = start;
    while(true){
        cout << "Enter the next word: ";
        cout << "If you want a hint, type 'hint' and press enter." << endl;
        cin >> word;
        if(word == "hint"){
            vector<string> path = BFS(graph, lastWord, target);
            if(path.size() == 0){
                cout << "No path found" << endl;
            } else {
                cout << "Hint: " << path[1] << endl;
            }
            continue;
        }
        else if(word == target){
            cout << "Congratulations! You found the target word!" << endl;
            break;
        }
        else if(lastWord == word){
            cout << "You entered the same word as the last one. Try again." << endl;
            continue;
        }
        else if(lastWord.size() != word.size()){
            cout << "The word should have " << length << " letters. Try again." << endl;
            continue;
        }
        else if(!isInDictionary(word, dictionary)){
            cout << "The word is not in the dictionary. Try again." << endl;
            continue;
        }
        else if(!graph.hasEdge(lastWord, word)){
            cout << "The new word has top have only one letter changed from the last one. Try again." << endl;
            continue;
        }
        
    }

}
