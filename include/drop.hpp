// drop.hpp

#pragma once

#include <string>

using namespace std;

class Drop {

public:

    // fields
    string slug;
    string rarity; // 
    string wear;
    double price; // pricereal - cash price NICE!
    bool isstattrak;

    // constructor
    Drop(string& slug, string& rarity, string& wear, double& price, bool& isstattrak)
        : slug(slug), rarity(rarity), wear(wear), price(price), isstattrak(isstattrak) {}
        
    
    string getRarity() const { // this const returns a read-only reference, allowing us to call it on a const Drop
        return rarity;
    }

};
