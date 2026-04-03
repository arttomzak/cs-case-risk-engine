// skingroup.hpp

#pragma once

#include "drop.hpp"

#include <string>
#include <vector>

using namespace std;

class SkinGroup {

public:

    string name;
    string rarity;
    vector<Drop> drops;

    SkinGroup(string& name, string& rarity, vector<Drop>& drops) : name(name), rarity(rarity), drops(drops) {}

    void addDrop(const Drop& drop) {
        drops.push_back(drop);
    }

};
