#pragma once

#include "Graph.h"
#include <vector>
#include <string>

void populateGraph(Graph<std::string>& graph, const std::vector<std::string>& dictionary);

std::vector<std::string> BFS(Graph<std::string>& graph, const std::string& start, const std::string& target);

bool isInDictionary(const std::string& word, const std::vector<std::string>& dictionary);