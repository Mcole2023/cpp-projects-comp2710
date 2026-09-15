/*
 * Michael Cole
 * mzc0216
 * FileReader.h
 *
 * Reads and validates numeric data from input files.
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class FileReader {
public:
    // Reads all valid numbers from the given file into 'out'.
    // Malformed lines (non-numeric tokens) are skipped, not fatal.
    // Returns true if the file opened successfully.
    static bool readFile(const std::string& filename, std::vector<double>& out);
};

#endif
