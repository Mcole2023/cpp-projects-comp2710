/*
 * Michael Cole
 * mzc0216
 * FileReader.cpp
 */

#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileReader::readFile(const std::string& filename, std::vector<double>& out) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Warning: could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(infile, line)) {
        lineNum++;
        if (line.empty()) continue;

        std::istringstream lineStream(line);
        std::string token;
        while (lineStream >> token) {
            try {
                size_t pos;
                double value = std::stod(token, &pos);
                // Reject tokens that are only partially numeric (e.g. "12abc")
                if (pos != token.size()) {
                    std::cerr << "Skipping malformed value \"" << token
                              << "\" in " << filename << " (line " << lineNum << ")" << std::endl;
                    continue;
                }
                out.push_back(value);
            } catch (const std::invalid_argument&) {
                std::cerr << "Skipping malformed value \"" << token
                          << "\" in " << filename << " (line " << lineNum << ")" << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << "Skipping out-of-range value \"" << token
                          << "\" in " << filename << " (line " << lineNum << ")" << std::endl;
            }
        }
    }

    infile.close();
    return true;
}
