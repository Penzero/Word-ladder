#include "WordPatternGraph.h"
#include <unordered_map>
#include <list>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <algorithm>

using std::string, std::vector;


vector<string> generatePatterns(const std::string& word){
    vector<string> patterns;
    for(size_t i = 0; i < word.size(); i++){
        string pattern = word.substr(0, i) + '*' + word.substr(i + 1);
        patterns.push_back(pattern);    
    }
    return patterns;
}

void populateGraph(Graph<string>& graph, const vector<string>& dictionary){
    std::unordered_map<string, std::unordered_set<string>> patternToWord;
    for(const string& word: dictionary){
        graph.addVertex(word);
        vector<string> patterns = generatePatterns(word);
        for(const string& pattern: patterns){
            patternToWord[pattern].insert(word);
        }
    }

    for(const auto& pair: patternToWord){
        const std::unordered_set<string>& words = pair.second;
        for(const string& word1: words){
            for(const string& word2: words){
                if(word1 != word2){
                    graph.addEdge(word1, word2);
                }
            }
        }
    }
}
vector<string> BFS(Graph<string>& graph, const string& start, const string& target){
    std::unordered_map<std::string, std::string> parent;
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;

    queue.push(start);
    visited.insert(start);
    parent[start] = ""; // Mark the start node's parent as an empty string indicating no parent

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();

        if (current == target) {
            std::vector<std::string> path;
            for (std::string at = target; !at.empty(); at = parent[at])
                path.push_back(at);
            std::reverse(path.begin(), path.end());
            return path;
        }

        std::list<std::string> neighbors = graph.getNeighbors(current);
        for (const std::string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                queue.push(neighbor);
                parent[neighbor] = current;
            }
        }
    }
    return {};
}

bool isInDictionary(const string& word, const vector<string>& dictionary){
    return std::find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}
