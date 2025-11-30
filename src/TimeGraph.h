#ifndef ADVANCE_OOP_HW2_TIMEGRAPH_H
#define ADVANCE_OOP_HW2_TIMEGRAPH_H

#include "Port.h"
#include "CustomException.h"
#include <memory>
#include <map>

class TimeGraph {
private:
    // src port --to--> (dest port,travel time)
    std::map<std::shared_ptr<Port>, std::map<std::shared_ptr<Port>, int>> graph;

public:
    void addPort(const std::shared_ptr<Port> &port);

    void addRoute(const std::shared_ptr<Port> &srcPort, const std::shared_ptr<Port> &destPort, int time);

    void printInboundPorts(const std::string &portName);

    void printOutboundPorts(const std::string &portName);

    void print(const std::string &filename);

    std::shared_ptr<Port> findPortByName(const std::string &name) const;
};

#endif //ADVANCE_OOP_HW2_TIMEGRAPH_H
