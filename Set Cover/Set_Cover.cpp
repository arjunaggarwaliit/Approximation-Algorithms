#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Subset {
    int index;
    set<int> elements;
    double weight;
};

class SetCover {
private:
    vector<Subset> subsets;
    int universe_size;
    vector<bool> covered;
    vector<bool> selected;

public:
    SetCover(int n, const vector<pair<set<int>, double>>& sets) : universe_size(n) {
        subsets.resize(sets.size());
        covered.resize(n, false);
        selected.resize(sets.size(), false);

        for(int i = 0; i < sets.size(); i++) {
            subsets[i].index = i;
            subsets[i].elements = sets[i].first;
            subsets[i].weight = sets[i].second;
        }
    }

    vector<int> greedy_unweighted() {
        vector<bool> temp_covered = covered;
        vector<bool> temp_selected = selected;
        vector<int> solution;

        while(true) {
            int best_subset = -1;
            int max_uncovered = 0;

            for(int i = 0; i < subsets.size(); i++) {
                if(temp_selected[i]) continue;

                int uncovered_count = 0;
                for(int elem : subsets[i].elements) {
                    if(!temp_covered[elem]) {
                        uncovered_count++;
                    }
                }

                if(uncovered_count > max_uncovered) {
                    max_uncovered = uncovered_count;
                    best_subset = i;
                }
            }

            if(best_subset == -1 || max_uncovered == 0) break;

            solution.push_back(best_subset);
            temp_selected[best_subset] = true;

            for(int elem : subsets[best_subset].elements) {
                temp_covered[elem] = true;
            }
        }

        return solution;
    }

    vector<int> greedy_weighted() {
        vector<bool> temp_covered = covered;
        vector<bool> temp_selected = selected;
        vector<int> solution;

        while(true) {
            int best_subset = -1;
            double best_ratio = -1.0;

            for(int i = 0; i < subsets.size(); i++) {
                if(temp_selected[i]) continue;

                int uncovered_count = 0;
                for(int elem : subsets[i].elements) {
                    if(!temp_covered[elem]) {
                        uncovered_count++;
                    }
                }

                if(uncovered_count > 0) {
                    double ratio = uncovered_count / subsets[i].weight;
                    if(ratio > best_ratio) {
                        best_ratio = ratio;
                        best_subset = i;
                    }
                }
            }

            if(best_subset == -1) break;

            solution.push_back(best_subset);
            temp_selected[best_subset] = true;

            for(int elem : subsets[best_subset].elements) {
                temp_covered[elem] = true;
            }
        }

        return solution;
    }

    vector<int> lp_rounding() {
        int m = subsets.size();
        int n = universe_size;
        vector<double> x(m, 0.0);
        vector<int> solution;

        for(int i = 0; i < m; i++) {
            x[i] = 1.0 / (subsets[i].elements.size());
        }

        for(int i = 0; i < m; i++) {
            if(x[i] >= 1.0 / (sqrt(m * n))) {
                solution.push_back(i);
            }
        }

        return solution;
    }
};
