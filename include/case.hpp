// case.hpp

#pragma once

#include "drop.hpp"

#include <string>
#include <unordered_map>

using namespace std;

class Drop {

public:
    // keeping these as public for now
    string name;
    unordered_map<string, vector<Drop>> rarityToSkinVec;
    vector<Drop> skinVec;

    // constructor
    Drop(string& name);

    // adds a drop to the case object
    // MEANT FOR USE DURING THE DATA LOADING PHASE
    void addDrop(const Drop& drop);

};




// // imagine something like this when loading data 

// #include "Case.hpp"
// #include "Drop.hpp"
// #include "nlohmann/json.hpp"
// #include <fstream>

// Case prismaCase("Prisma Case");

// std::ifstream file("data/cases.json");
// nlohmann::json data;
// file >> data;

// for (const auto& item : data["Prisma Case"]) {
//     std::string name = item["name"];
//     std::string rarity = item["rarity"];
//     std::string wear = item["wear"];

//     prismaCase.addDrop(Drop(name, rarity, wear));
// }