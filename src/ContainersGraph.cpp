#include "ContainersGraph.h"
#include <iostream>
#include <fstream>

void ContainersGraph::addPort(const std::shared_ptr<Port> &port) {
    graph[port];
}

void ContainersGraph::addRoute(const std::shared_ptr<Port> &srcPort, const std::shared_ptr<Port> &destPort, int containers) {
    addPort(srcPort);
    addPort(destPort);

    auto &innerMap = graph[srcPort];
    auto it = innerMap.find(destPort);
    if (it != innerMap.end()) {
        graph[srcPort][destPort] += containers;
    } else {
        graph[srcPort][destPort] = containers;
    }

}

void ContainersGraph::print(const std::string &filename) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile) {
        throw FileOpenException();
    }

    if (graph.empty()) {
        outputFile << "TimeGraph is empty.\n";
        return;
    }

    outputFile << "\n========== Containers TimeGraph ==========\n";
    for (const auto &source: graph) {
        outputFile << source.first->getName() << ": ";
        size_t count = 0;
        for (const auto &dest: source.second) {
            int containers = dest.second;
            outputFile << dest.first->getName() << "(" << containers << ")";
            if (++count < source.second.size()) {
                outputFile << ", ";
            }
        }
        outputFile << "\n";
    }
}
