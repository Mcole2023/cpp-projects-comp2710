/*
 * Michael Cole
 * mzc0216
 * DataProcessor.cpp
 */

#include "DataProcessor.h"
#include <map>
#include <cstddef>

void DataProcessor::merge(std::vector<double>& data, int left, int mid, int right) {
    std::vector<double> leftHalf(data.begin() + left, data.begin() + mid + 1);
    std::vector<double> rightHalf(data.begin() + mid + 1, data.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftHalf.size() && j < rightHalf.size()) {
        if (leftHalf[i] <= rightHalf[j]) {
            data[k++] = leftHalf[i++];
        } else {
            data[k++] = rightHalf[j++];
        }
    }
    while (i < leftHalf.size()) data[k++] = leftHalf[i++];
    while (j < rightHalf.size()) data[k++] = rightHalf[j++];
}

void DataProcessor::mergeSortHelper(std::vector<double>& data, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(data, left, mid);
    mergeSortHelper(data, mid + 1, right);
    merge(data, left, mid, right);
}

void DataProcessor::mergeSort(std::vector<double>& data) {
    if (data.size() < 2) return;
    mergeSortHelper(data, 0, static_cast<int>(data.size()) - 1);
}

double DataProcessor::mean(const std::vector<double>& sortedData) {
    if (sortedData.empty()) return 0.0;
    double sum = 0.0;
    for (double v : sortedData) sum += v;
    return sum / sortedData.size();
}

double DataProcessor::median(const std::vector<double>& sortedData) {
    if (sortedData.empty()) return 0.0;
    size_t n = sortedData.size();
    if (n % 2 == 1) {
        return sortedData[n / 2];
    }
    return (sortedData[n / 2 - 1] + sortedData[n / 2]) / 2.0;
}

std::vector<double> DataProcessor::modes(const std::vector<double>& sortedData) {
    std::vector<double> result;
    if (sortedData.empty()) return result;

    std::map<double, int> counts;
    for (double v : sortedData) counts[v]++;

    int maxCount = 0;
    for (const auto& pair : counts) {
        if (pair.second > maxCount) maxCount = pair.second;
    }

    for (const auto& pair : counts) {
        if (pair.second == maxCount) result.push_back(pair.first);
    }
    return result;
}
