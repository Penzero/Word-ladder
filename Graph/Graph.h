#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T>
class Graph
{
private:
    std::unordered_map<T, std::list<T>> adjList;

public:
    void addVertex(const T& vertex) {
        // Ensures vertex is added to the adjacency list
        adjList[vertex];
    }

    void addEdge(const T& src, const T& dest) {
        // Adds an undirected edge between src and dest
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    std::list<T> getNeighbors(const T& vertex) {
        // Returns the list of neighbors of the vertex
        return adjList[vertex];
    }

    bool hasEdge(const T& src, const T& dest) {
        // Returns true if an edge exists between src and dest
        return std::find(adjList[src].begin(), adjList[src].end(), dest) != adjList[src].end();
    }

    void printGraph() {
        // Prints each vertex and its adjacency list
        for (const auto& pair : adjList) {
            std::cout << pair.first << " -> ";
            for (const auto& neighbor : pair.second) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }
};
