#ifndef ADVANCE_OOP_HW2_CONTAINERSGRAPH_H
#define ADVANCE_OOP_HW2_CONTAINERSGRAPH_H

#include "Port.h"
#include "CustomException.h"
#include <map>
#include <memory>

class ContainersGraph {
private:
    // src port --to--> (dest port,containers)
    std::map<std::shared_ptr<Port>, std::map<std::shared_ptr<Port>, int>> graph;

public:
    void addPort(const std::shared_ptr<Port> &port);

    void addRoute(const std::shared_ptr<Port> &srcPort, const std::shared_ptr<Port> &destPort, int containers);

    void print(const std::string& filename);

};

#endif //ADVANCE_OOP_HW2_CONTAINERSGRAPH_H
