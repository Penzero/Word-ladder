#include "Automatic-Mode.h"

void automatic(const std::string start, const std::string target, const std::vector<std::string>& dictionary){
    Graph<std::string> graph;
    populateGraph(graph, dictionary);
    std::vector<std::string> path = BFS(graph, start, target);
    if(path.size() == 0){
        std::cout << "No path found" << std::endl;
    } else {
        std::cout << "Path found: ";
        for(auto& word : path){
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}
