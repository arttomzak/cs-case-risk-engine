#include <iostream>

using namespace std;

int main() {
    string userInput;

    while (true) {

        cout << endl;
        cout << "Welcome to the Counter-Strike Case Risk Engine!" << endl;
        cout << "Enter 'q' at any time to close the program" << endl;
        cout << endl;
        cout << "Please enter the name of a case :)" << endl;
        cout << endl;
        
        getline(cin, userInput);

        if (userInput == "q") {
            break;
        }

        

        cout << endl;

        cout << endl;



    }







    return 0;
}