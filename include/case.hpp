// case.hpp

#pragma once

#include "drop.hpp"

#include <string>
#include <unordered_map>

using namespace std;

class Case {

public:
    // fields
    string name;


    // RNG FLOW, determine rarity, get the equally weighted group name, access bottom dict, and get the float / ST or not
    
    unordered_map<string, vector<string>> rarityToGroupNames; // GROUP NAMES HERE
    unordered_map<string, vector<pair<Drop, Drop>>> skinGroupToSTPair;

    // !!!!!!!!!!

    vector<Drop> drops;


    // constructor
    Case(string& name) : name(name) {}


    // adds a drop to the case object (used during data ingestion)
    void addDrop(const Drop& drop) {
        string& rarity = drop.getRarity();

    }

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