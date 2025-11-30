#ifndef ADVANCE_OOP_HW2_CUSTOMEXCEPTION_H
#define ADVANCE_OOP_HW2_CUSTOMEXCEPTION_H

#include <iostream>

class FileException : public std::exception {
private:
    std::string message;
public:
    explicit FileException(const std::string &filename, int line = 0) {
        if (line == 0) {
            message = "Invalid input in file " + filename + " at line 0.\n";
        } else {
            message = "Invalid input in file " + filename + " at line " + std::to_string(line) + ".\n";
        }
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class FileOpenException : public std::exception {
private:
    std::string message;
public:
    FileOpenException() : message("ERROR opening/reading the specified file.\n") {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class PortNotFoundException : public std::exception {
private:
    std::string message;
public:
    explicit PortNotFoundException(const std::string &portName)
            : message(portName + " does not exist in the database.\n") {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

class InvalidCommandException : public std::exception {
private:
    std::string message;
public:
    InvalidCommandException() : message(
            "USAGE: 'load' <file> *or*\n<node>,'inbound' *or*\n<node>,'outbound' *or*\n<node>,'containersBalance',dd/mm HH:mm *or*\n'print' *or*\n'exit' *to terminate*\n") {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif //ADVANCE_OOP_HW2_CUSTOMEXCEPTION_H
