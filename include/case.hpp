// case.hpp

#pragma once

#include "skingroup.hpp"

#include <string>
#include <unordered_map>

using namespace std;

class CS_Case { // apparently case is a restricted keyword

public:
    // fields
    string name;
    double price = 0.0;

    unordered_map<string, vector<SkinGroup>> rarityToSkinGroup;

    CS_Case(string& name) : name(name) {}

    void addSkinGroup(const SkinGroup& group) {
      rarityToSkinGroup[group.rarity].push_back(group);
    }
};
