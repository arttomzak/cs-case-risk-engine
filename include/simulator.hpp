// simulator.hpp

#pragma once

#include "case.hpp"

#include <optional>
#include <random>
#include <thread>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <iomanip>

using namespace std;

struct SimResult {
    long long totalOpenings = 0;
    long long knifeCount = 0;
    double totalValue = 0.0;
    unordered_map<string, long long> rarityCounts;
    unordered_map<string, double> rarityValues;
};

class Simulator {
public:

    optional<Drop> openCase(const CS_Case& cs_case, mt19937& rng) {
        static const unordered_map<string, double> BASE_WEIGHTS = {
            {"Mil-Spec Grade", 79.9227},
            {"Restricted",     15.9845},
            {"Classified",      3.1969},
            {"Covert",          0.6394},
            {"Rare Special",    0.2558},
        };

        vector<string> rarities;
        vector<double> weights;
        for (auto& [rarity, weight] : BASE_WEIGHTS) {
            rarities.push_back(rarity);
            weights.push_back(weight);
        }

        discrete_distribution<int> rarityDist(weights.begin(), weights.end());
        const string& chosenRarity = rarities[rarityDist(rng)];

        if (chosenRarity == "Rare Special") return nullopt;

        // Pick random SkinGroup
        const auto& groups = cs_case.rarityToSkinGroup.at(chosenRarity);
        uniform_int_distribution<size_t> groupDist(0, groups.size() - 1);
        const SkinGroup& group = groups[groupDist(rng)];

        bool useStattrak = bernoulli_distribution(0.1)(rng);
        vector<const Drop*> pool;
        for (auto& d : group.drops) {
            if (d.isstattrak == useStattrak) pool.push_back(&d);
        }
        if (pool.empty()) {
            for (auto& d : group.drops) {
                if (!d.isstattrak) pool.push_back(&d);
            }
        }

        float wearFloat = uniform_real_distribution<float>(0.0f, 1.0f)(rng);
        string wearTier;
        if      (wearFloat < 0.07f) wearTier = "fn";
        else if (wearFloat < 0.15f) wearTier = "mw";
        else if (wearFloat < 0.38f) wearTier = "ft";
        else if (wearFloat < 0.45f) wearTier = "ww";
        else                        wearTier = "bs";

        const Drop* chosen = nullptr;
        for (auto& d : pool) {
            if (d->wear == wearTier) { chosen = d; break; }
        }
        if (!chosen) {
            uniform_int_distribution<size_t> fallback(0, pool.size() - 1);
            chosen = pool[fallback(rng)];
        }
        return *chosen;
    }
    

    SimResult runSimulation(const CS_Case& cs_case, long long numOpenings, int numThreads = 4) {
        double caseCost = cs_case.price + 2.50;
        vector<SimResult> threadResults(numThreads);
        vector<thread> threads;

        long long perThread = numOpenings / numThreads;
        long long remainder = numOpenings % numThreads;

        for (int t = 0; t < numThreads; ++t) {
            long long count = perThread + (t == 0 ? remainder : 0);
            threads.emplace_back([this, &cs_case, &threadResults, t, count]() {
                mt19937 rng(random_device{}() ^ (t * 2654435761u));
                SimResult local;
                for (long long i = 0; i < count; ++i) {
                    local.totalOpenings++;
                    optional<Drop> d = openCase(cs_case, rng);
                    if (!d.has_value()) {
                        local.knifeCount++;
                        continue;
                    }
                    local.totalValue += d->price;
                    local.rarityCounts[d->rarity]++;
                    local.rarityValues[d->rarity] += d->price;
                }
                threadResults[t] = move(local);
            });
        }
        for (auto& th : threads) th.join();

        // Merge thread results
        SimResult result;
        for (auto& r : threadResults) {
            result.totalOpenings += r.totalOpenings;
            result.knifeCount += r.knifeCount;
            result.totalValue += r.totalValue;
            for (auto& [rarity, count] : r.rarityCounts) {
                result.rarityCounts[rarity] += count;
                result.rarityValues[rarity] += r.rarityValues.at(rarity);
            }
        }

        double totalCost = numOpenings * caseCost;
        double avgReturn = result.totalValue / result.totalOpenings;
        double roi = (result.totalValue - totalCost) / totalCost * 100.0;

        cout << fixed << setprecision(2);
        cout << "\n=== Simulation Results ===" << endl;
        cout << "Openings:     " << result.totalOpenings << endl;
        cout << "Case cost:    $" << caseCost << " each  ($" << totalCost << " total)" << endl;
        cout << "Total return: $" << result.totalValue << endl;
        cout << "Avg return:   $" << avgReturn << " per opening" << endl;
        cout << "ROI:          " << roi << "%" << endl;
        cout << "Knives:       " << result.knifeCount << " (" << 100.0 * result.knifeCount / result.totalOpenings << "%)" << endl;
        cout << "\nDrop distribution:" << endl;
        for (auto& [rarity, count] : result.rarityCounts) {
            double pct = 100.0 * count / result.totalOpenings;
            double avgVal = result.rarityValues.at(rarity) / count;
            cout << "  " << rarity << ": " << count
                 << " (" << pct << "%)  avg $" << avgVal << endl;
        }

        return result;
    }
};
