
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <climits>

// Check whether the remaining packages can be
// divided into the required number of groups.
bool canPartition(
    const std::vector<int>& packages,
    std::vector<bool>& used,
    int index,
    int sum,
    int target,
    int groups
) {
    // The final group automatically has the
    // correct weight if all previous groups do.
    if (groups == 1) {
        return true;
    }

    if (sum == target) {
        return canPartition(
            packages, used, 0, 0, target, groups - 1
        );
    }

    for (int i = index; i < static_cast<int>(packages.size()); i++) {
        if (used[i] || sum + packages[i] > target) {
            continue;
        }

        used[i] = true;

        if (canPartition(
            packages,
            used,
            i + 1,
            sum + packages[i],
            target,
            groups
        )) {
            used[i] = false;
            return true;
        }

        used[i] = false;
    }

    return false;
}

// Find the first group with the minimum
// number of packages and lowest QE.
void findGroup(
    const std::vector<int>& packages,
    std::vector<bool>& used,
    int index,
    int count,
    int maxCount,
    int sum,
    int target,
    int groups,
    uint64_t qe,
    uint64_t& best
) {
    if (count == maxCount) {
        if (sum != target || qe >= best) {
            return;
        }

        if (canPartition(
            packages, used, 0, 0, target, groups - 1
        )) {
            best = qe;
        }

        return;
    }

    for (int i = index; i < static_cast<int>(packages.size()); i++) {
        if (sum + packages[i] > target) {
            continue;
        }

        if (qe > best / static_cast<uint64_t>(packages[i])) {
            continue;
        }

        used[i] = true;

        findGroup(
            packages,
            used,
            i + 1,
            count + 1,
            maxCount,
            sum + packages[i],
            target,
            groups,
            qe * packages[i],
            best
        );

        used[i] = false;
    }
}

uint64_t solve(
    const std::vector<int>& packages,
    int groups
) {
    int total = std::accumulate(
        packages.begin(), packages.end(), 0
    );

    if (total % groups != 0) {
        return UINT64_MAX;
    }

    int target = total / groups;

    std::vector<bool> used(packages.size(), false);

    for (int size = 1; size <= static_cast<int>(packages.size()); size++) {
        uint64_t best = UINT64_MAX;

        findGroup(
            packages,
            used,
            0,
            0,
            size,
            0,
            target,
            groups,
            1,
            best
        );

        if (best != UINT64_MAX) {
            std::cout << "Minimum packages: "
                      << size << '\n';

            return best;
        }
    }

    return UINT64_MAX;
}

int main() {
    std::cout << "AOC 2015 - Day 24\n";

    std::ifstream day24_input("data/2015/day24.txt");

    if (!day24_input) {
        std::cout << "Could not open file!\n";
        return -1;
    }

    std::vector<int> packages;
    int weight;

    while (day24_input >> weight) {
        packages.push_back(weight);
    }

    if (packages.empty()) {
        std::cout << "No packages found!\n";
        return -1;
    }

    std::sort(packages.rbegin(), packages.rend());

    std::cout << "\nPart 1:\n";
    uint64_t part1 = solve(packages, 3);

    if (part1 != UINT64_MAX) {
        std::cout << "Quantum entanglement: "
                  << part1 << '\n';
    }

    std::cout << "\nPart 2:\n";
    uint64_t part2 = solve(packages, 4);

    if (part2 != UINT64_MAX) {
        std::cout << "Quantum entanglement: "
                  << part2 << '\n';
    }

    return 0;
}