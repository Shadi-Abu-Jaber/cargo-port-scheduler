#include "CargoSystem.h"

int main(int argc, char *argv[]) {
    if (argc < 3 || std::string(argv[1]) != "-i") {
        std::cerr << "Usage: " << argv[0] << " -i <infile1> [<infile2> ...] [-o <outfile>]" << std::endl;
        return 1;
    }

    CargoSystem cargoSystem;
    std::vector<std::string> inputFiles;
    std::string outputFile = "output.dat";

    for (int i = 2; i < argc; ++i) {
        if (std::string(argv[i]) == "-o") {
            if (i + 1 >= argc) {
                std::cerr << "Error: -o flag requires output filename" << std::endl;
                return 1;
            }
            outputFile = argv[++i];
        } else {
            inputFiles.emplace_back(argv[i]);
        }
    }

    try {
        cargoSystem.initialize(inputFiles);
        cargoSystem.setOutputFile(outputFile);
        cargoSystem.run();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }

    return 0;
}
