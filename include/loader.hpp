// loader.hpp

#pragma once

#include "case.hpp"
#include "json.hpp"
#include "drop.hpp"
#include "skingroup.hpp"

#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json; 

Case loadCase(const string& filepath) {
  ifstream file(filepath);
  json data = json::parse(file);
  
  string casename = "revolver";
  Case curCase = Case(casename); // hardcoded for now

  for (auto& item : data["items"]) {
    string name = item["groupname"];
    string rarity = item["tag6"];
    vector<Drop> drops;
    SkinGroup curSkinGroup = SkinGroup(name, rarity, drops);
    curCase.addSkinGroup(curSkinGroup);

    for (auto& groupitem : item["groupitems"]) {
      string slug = groupitem["slug"];
      string rarity = groupitem["tag6"];
      string wear = groupitem["wear"];
      double price = groupitem["pricereal"];
      bool isstattrak = groupitem["isstattrak"];

      Drop curDrop = Drop(slug, rarity, wear, price, isstattrak);
      curSkinGroup.addDrop(curDrop);
    }

  }
  cout << "loaded" << endl;
  return curCase;
}
