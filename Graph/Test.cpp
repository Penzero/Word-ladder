#include <cassert>
#include <iostream>
#include "Graph.h"
#include "WordPatternGraph.h"

void testBFS(){
    Graph<std::string> wordGraph;
    std::vector<std::string> dictionary = {"CAME", "LAME", "NAME", "SAME", "SOME", "SAGE", "SALE", "SANE", "SASE"};
    populateGraph(wordGraph, dictionary);

    // Test basic functionality
    auto path = BFS(wordGraph, "CAME", "SANE");
    assert((path.size() == 3) && (path[0] == "CAME" && path[1] == "SAME" && path[2] == "SANE"));

    // Test when no path exists
    path = BFS(wordGraph, "CAME", "XXXX");
    assert(path.empty());

    // Test when start and target are the same
    path = BFS(wordGraph, "CAME", "CAME");
    assert((path.size() == 1) && (path[0] == "CAME"));

    // Test single step transformation
    path = BFS(wordGraph, "CAME", "SAME");
    assert((path.size() == 2) && (path[0] == "CAME" && path[1] == "SAME"));

    std::cout << "All tests passed." << std::endl;
}

int main(){
    testBFS();
    return 0;
}