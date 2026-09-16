/*
 * Michael Cole
 * mzc0216
 * DataProcessor.h
 *
 * Custom merge sort and statistical summary (mean/median/mode)
 * for a dataset of doubles.
 */

#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>

class DataProcessor {
public:
    // O(N log N) merge sort, sorts 'data' in place ascending. No STL sort used.
    static void mergeSort(std::vector<double>& data);

    static double mean(const std::vector<double>& sortedData);
    static double median(const std::vector<double>& sortedData);

    // Returns every value tied for the highest frequency (averaged mode
    // when the assignment calls for a single number, that average is
    // computed by the caller from this vector).
    static std::vector<double> modes(const std::vector<double>& sortedData);

private:
    static void merge(std::vector<double>& data, int left, int mid, int right);
    static void mergeSortHelper(std::vector<double>& data, int left, int right);
};

#endif
