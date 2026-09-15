/*
 * Michael Cole
 * mzc0216
 * DataAnalyzer.cpp
 *
 * Reads N input data files, validates and merges their contents,
 * sorts the combined dataset with a custom merge sort, computes
 * summary statistics, and exports the sorted data + stats to CSV.
 *
 * Compile: g++ DataAnalyzer.cpp FileReader.cpp DataProcessor.cpp -o DataAnalyzer
 * Run:     ./DataAnalyzer data1.txt data2.txt data3.txt
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FileReader.h"
#include "DataProcessor.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file 1> [input file 2] ..." << std::endl;
        return 1;
    }

    std::vector<double> allData;

    for (int i = 1; i < argc; i++) {
        std::vector<double> fileData;
        bool ok = FileReader::readFile(argv[i], fileData);
        if (!ok) {
            std::cerr << "Skipping unreadable file: " << argv[i] << std::endl;
            continue;
        }
        std::cout << "Read " << fileData.size() << " valid value(s) from " << argv[i] << std::endl;
        allData.insert(allData.end(), fileData.begin(), fileData.end());
    }

    if (allData.empty()) {
        std::cerr << "No valid data found across all input files. Exiting." << std::endl;
        return 1;
    }

    DataProcessor::mergeSort(allData);

    double meanVal = DataProcessor::mean(allData);
    double medianVal = DataProcessor::median(allData);
    std::vector<double> modeVals = DataProcessor::modes(allData);

    double modeAvg = 0.0;
    for (double m : modeVals) modeAvg += m;
    modeAvg /= modeVals.size();

    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "Count:  " << allData.size() << std::endl;
    std::cout << "Mean:   " << meanVal << std::endl;
    std::cout << "Median: " << medianVal << std::endl;
    std::cout << "Mode:   " << modeAvg;
    if (modeVals.size() > 1) std::cout << " (averaged across " << modeVals.size() << " tied values)";
    std::cout << std::endl;

    // Export sorted data + stats to CSV
    std::string outFile = "output.csv";
    std::ofstream out(outFile);
    if (!out.is_open()) {
        std::cerr << "Could not open " << outFile << " for writing." << std::endl;
        return 1;
    }

    out << "sorted_value\n";
    for (double v : allData) out << v << "\n";

    out << "\nstatistic,value\n";
    out << "count," << allData.size() << "\n";
    out << "mean," << meanVal << "\n";
    out << "median," << medianVal << "\n";
    out << "mode," << modeAvg << "\n";

    out.close();
    std::cout << "\nResults written to " << outFile << std::endl;

    return 0;
}
