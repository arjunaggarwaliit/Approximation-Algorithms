#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class BinPacking {
public:
    static std::vector<std::vector<double>> firstFitDecreasing(const std::vector<double>& items, double capacity) {
        std::vector<double> sortedItems = items;
        std::sort(sortedItems.begin(), sortedItems.end(), std::greater<double>());

        std::vector<std::vector<double>> bins;
        bins.push_back(std::vector<double>());
        std::vector<double> binSpace;
        binSpace.push_back(capacity);

        for (double item : sortedItems) {
            bool placed = false;

            for (size_t i = 0; i < bins.size(); ++i) {
                if (binSpace[i] >= item) {
                    bins[i].push_back(item);
                    binSpace[i] -= item;
                    placed = true;
                    break;
                }
            }

            if (!placed) {
                std::vector<double> newBin;
                newBin.push_back(item);
                bins.push_back(newBin);
                binSpace.push_back(capacity - item);
            }
        }

        return bins;
    }

    static std::vector<std::vector<double>> bestFitDecreasing(const std::vector<double>& items, double capacity) {
        std::vector<double> sortedItems = items;
        std::sort(sortedItems.begin(), sortedItems.end(), std::greater<double>());

        std::vector<std::vector<double>> bins;
        std::vector<double> binSpace;

        for (double item : sortedItems) {
            int bestBin = -1;
            double minSpace = capacity + 1;

            for (size_t i = 0; i < bins.size(); ++i) {
                if (binSpace[i] >= item && binSpace[i] - item < minSpace) {
                    bestBin = i;
                    minSpace = binSpace[i] - item;
                }
            }

            if (bestBin != -1) {
                bins[bestBin].push_back(item);
                binSpace[bestBin] -= item;
            } else {
                std::vector<double> newBin;
                newBin.push_back(item);
                bins.push_back(newBin);
                binSpace.push_back(capacity - item);
            }
        }

        return bins;
    }
};

