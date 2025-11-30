#ifndef ADVANCE_OOP_HW2_CARGOSYSTEM_H
#define ADVANCE_OOP_HW2_CARGOSYSTEM_H

#include "TimeGraph.h"
#include "ContainersGraph.h"
#include "CustomException.h"
#include <vector>

class CargoSystem {
private:
    TimeGraph timeGraph;
    ContainersGraph containersGraph;
    std::string outputFile;

    static std::vector<std::string> split(const std::string &str, char delimiter);

    static bool isValidPortName(const std::string &portName);

    static bool isValidDateTime(const std::string& dateTime);

    static bool isTwoDigitNumber(const std::string& s);

    static int parseDateTime(const std::string &dateTime);

public:
    void loadFile(const std::string& file);

    void setOutputFile( std::string filename);

    void processCommand(const std::string &command);

    bool initialize(const std::vector<std::string>& inputFiles);

    void run();
};

#endif //ADVANCE_OOP_HW2_CARGOSYSTEM_H