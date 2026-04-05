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

    // this maps from a rarity to a vector of SkinGroup
    // objects which will aid in pulling a random skip 
    unordered_map<string, vector<SkinGroup>> rarityToSkinGroup;

    // constructor
    CS_Case(string& name) : name(name) {}

    void addSkinGroup(const SkinGroup& group) {
      rarityToSkinGroup[group.rarity].push_back(group);
    }
};
