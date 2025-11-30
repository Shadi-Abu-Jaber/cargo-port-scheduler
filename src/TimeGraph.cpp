#include "TimeGraph.h"
#include <iostream>
#include <fstream>

void TimeGraph::addPort(const std::shared_ptr<Port> &port) {
    graph[port];
}

void TimeGraph::addRoute(const std::shared_ptr<Port> &srcPort, const std::shared_ptr<Port> &destPort, int time) {
    addPort(srcPort);
    addPort(destPort);

    auto &innerMap = graph[srcPort];
    auto it = innerMap.find(destPort);
    if (it != innerMap.end()) {
        it->second = (it->second + time) / 2;
    } else {
        innerMap[destPort] = time;
    }

}

std::shared_ptr<Port> TimeGraph::findPortByName(const std::string &name) const {
    for (const auto &entry : graph) {
        const std::shared_ptr<Port> &port = entry.first;
        if (port && port->getName() == name) {
            return port;
        }
    }
    return nullptr;
}

void TimeGraph::printInboundPorts(const std::string &portName) {
    auto target = findPortByName(portName);
    if (!target) {
        throw PortNotFoundException(portName);
    }

    bool found = false;
    for (const auto &source: graph) {
        for (const auto &dest: source.second) {
            if (dest.first->getName() == target->getName()) {
                std::cout << source.first->getName() << "," << dest.second << "\n";
                found = true;
            }
        }
    }
    if (!found) {
        std::cout << portName << ": " << "No inbound ports" << std::endl;
    }
}

void TimeGraph::printOutboundPorts(const std::string &portName) {
    auto source = findPortByName(portName);
    if (!source) {
        throw PortNotFoundException(portName);
    }

    auto it = graph.find(source);
    if (it != graph.end() && !it->second.empty()) {
        for (const auto &dest: it->second) {
            std::cout << dest.first->getName() << "," << dest.second << "\n";
        }
    } else {
        std::cout << portName << ": " << "No outbound ports" << std::endl;
    }
}

void TimeGraph::print(const std::string &filename) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile) {
        throw FileOpenException();
    }

    if (graph.empty()) {
        outputFile << "TimeGraph is empty.\n";
        return;
    }

    outputFile << "========== Time TimeGraph ==========\n";
    for (const auto &source : graph) {
        outputFile << source.first->getName() << ": ";
        size_t count = 0;
        for (const auto &dest : source.second) {
            int time = dest.second;
            outputFile << dest.first->getName() << "(" << time << ")";
            if (++count < source.second.size()) {
                outputFile << ", ";
            }
        }

        outputFile << "\n";
    }
}
