// main.cpp

#include <iostream>
#include <string>
#include <optional>

#include "case.hpp"
#include "loader.hpp"

using namespace std;

int main() {
    string userInput;
    optional<Case> loadedCase;

    while (true) {

        cout << endl;
        cout << "Welcome to the Counter-Strike Case Profitability Simulator!" << endl;
        cout << "Enter 'q' at any time to close the program" << endl;
        cout << endl;
        cout << "Please enter the name of a case :)" << endl;
        cout << endl;
        
        getline(cin, userInput);

        if (userInput == "q") {
            break;
        }
        else if (userInput == "p") { // parse revolver case for now
            loadedCase = loadCase("data/the-revolver-case-collection.json");
            for (auto& entry : loadedCase.value().rarityToSkinGroup) {
                cout << entry.first << ": " << entry.second.size() << " groups" << endl;
            }
        }
        else if (userInput == "s") { // simulate 
        // if LoadedCase -> run simulation
        }
        else {
        // do nothing yo
        }
      
        cout << endl;

        cout << endl;

    }
    return 0;
}
