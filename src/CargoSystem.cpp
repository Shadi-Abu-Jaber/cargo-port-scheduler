#include "CargoSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool CargoSystem::initialize(const std::vector<std::string> &inputFiles) {
    for (const auto &filename: inputFiles) {
        loadFile(filename);
    }
    return true;
}

void CargoSystem::setOutputFile(std::string filename) {
    outputFile = std::move(filename);
}

void CargoSystem::loadFile(const std::string &file) {
    std::ifstream f(file);

    if (!f.is_open()) {
        throw FileOpenException();
    }

    std::string line;
    std::string srcPort;
    std::string destPort;
    std::string depTime;
    std::string arrTime;
    std::string con;
    int lineNumber = 1;

    if (!std::getline(f, line)) {
        throw FileException(file, lineNumber);
    }

    std::stringstream ss(line);
    if (!std::getline(ss, srcPort, ',') || !std::getline(ss, depTime)) {
        throw FileException(file, lineNumber);
    }

    if (!isValidPortName(srcPort) || !isValidDateTime(depTime)) {
        throw FileException(file, lineNumber);
    }

    std::shared_ptr<Port> src = timeGraph.findPortByName(srcPort);
    if (!src) {
        src = std::make_shared<Port>(std::move(srcPort));
        timeGraph.addPort(src);
        containersGraph.addPort(src);
    }

    int srcDepTime = parseDateTime(depTime);
    auto startPort = src;
    lineNumber++;

    while (std::getline(f, line)) {
        std::stringstream is(line);

        if (!std::getline(is, destPort, ',') ||
            !std::getline(is, arrTime, ',') ||
            !std::getline(is, con, ',')) {
            throw FileException(file, lineNumber);
        }

        if (!isValidPortName(destPort) || !isValidDateTime(arrTime) ||
            !isValidDateTime(depTime)) {
            throw FileException(file, lineNumber);
        }

        int containers;
        try {
            containers = std::stoi(con);
            if (containers <= 0) {
                throw FileException(file, lineNumber);
            }
        } catch (const std::invalid_argument &) {
            throw FileException(file, lineNumber);
        }

        std::shared_ptr<Port> dest = timeGraph.findPortByName(destPort);
        if (!dest) {
            dest = std::make_shared<Port>(std::move(destPort));
        }

        int depTimeInt = parseDateTime(depTime);
        int arrTimeInt = parseDateTime(arrTime);

        if (depTimeInt < 0 || arrTimeInt < 0 || arrTimeInt <= depTimeInt) {
            throw FileException(file, lineNumber);
        }

        int time = arrTimeInt - depTimeInt;
        timeGraph.addRoute(src, dest, time);
        containersGraph.addRoute(startPort, dest, containers);

        startPort->updateBalance(srcDepTime, -containers);
        dest->updateBalance(arrTimeInt, containers);

        std::getline(is, depTime);

        src = dest;
        lineNumber++;
    }
}

void CargoSystem::processCommand(const std::string &command) {
    std::vector<std::string> tokens = split(command, ',');

    if (tokens.empty()) {
        throw InvalidCommandException();
    }

    if (tokens[0] == "print") {
        if (tokens.size() != 1) {
            throw InvalidCommandException();
        }
        // clear file before writing
        std::ofstream ofs(outputFile);
        timeGraph.print(outputFile);
        containersGraph.print(outputFile);
        return;

    } else if (tokens[0].substr(0, 4) == "load") {
        tokens = split(tokens[0], ' ');

        if (tokens.size() != 2) {
            throw InvalidCommandException();
        }

        loadFile(tokens[1]);
        std::cout << "Update was successful." << std::endl;
        return;

    } else if (tokens.size() == 2) {
        std::string portName = tokens[0];
        std::string operation = tokens[1];

        if (!isValidPortName(portName)) {
            throw InvalidCommandException();
        }

        if (operation == "inbound") {
            timeGraph.printInboundPorts(portName);
            return;
        }

        if (operation == "outbound") {
            timeGraph.printOutboundPorts(portName);
            return;
        }

    } else if (tokens.size() == 3) {
        std::string portName = tokens[0];
        std::string operation = tokens[1];
        std::string dateTime = tokens[2];

        if (!isValidPortName(portName) || !isValidDateTime(dateTime) || operation != "balance") {
            throw InvalidCommandException();
        }

        auto port = timeGraph.findPortByName(portName);
        if (!port) {
            throw PortNotFoundException(portName);
        }

        int bal = port->getBalance(parseDateTime(dateTime));
        std::cout << bal << std::endl;
        return;
    }

    throw InvalidCommandException();
}

void CargoSystem::run() {
    while (true) {
        std::string command;
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        try {
            processCommand(command);
        } catch (const std::exception &e) {
            std::cerr << e.what();
        }

    }
}

std::vector<std::string> CargoSystem::split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(std::move(token));
    }

    return tokens;
}

bool CargoSystem::isValidPortName(const std::string &portName) {
    return !(portName.empty() || portName.length() > 16);
}

bool CargoSystem::isTwoDigitNumber(const std::string &s) {
    return s.length() == 2 && isdigit(s[0]) && isdigit(s[1]);
}

bool CargoSystem::isValidDateTime(const std::string &dateTime) {
    if (dateTime.length() != 11) {
        return false;
    }

    if (dateTime[2] != '/' || dateTime[5] != ' ' || dateTime[8] != ':') {
        return false;
    }

    std::string dd = dateTime.substr(0, 2);
    std::string MM = dateTime.substr(3, 2);
    std::string HH = dateTime.substr(6, 2);
    std::string mm = dateTime.substr(9, 2);

    if (!isTwoDigitNumber(dd) || !isTwoDigitNumber(MM) ||
        !isTwoDigitNumber(HH) || !isTwoDigitNumber(mm)) {
        return false;
    }

    int day = std::stoi(dd);
    int month = std::stoi(MM);
    int hour = std::stoi(HH);
    int minute = std::stoi(mm);

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    return true;
}

int CargoSystem::parseDateTime(const std::string &dateTime) {
    const int daysInMonth[] = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
    };

    int day, month, hour, minute;
    char slash, colon;
    std::istringstream ss(dateTime);
    ss >> day >> slash >> month >> hour >> colon >> minute;

    int totalDays = 0;
    for (int i = 0; i < month - 1; ++i) {
        totalDays += daysInMonth[i];
    }

    totalDays += day - 1;

    int totalMinutes = totalDays * 24 * 60 + hour * 60 + minute;
    return totalMinutes;
}
