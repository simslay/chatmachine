//
// Program Name: chatmachine
// Description: a rudimentary chatbot in c++
//
// Author: Simon Grandsire
//

#include "chatmachine.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string sInput = "";
string sResponse = "";
string sUserPrompt = "USER> ";
string sBotPrompt = "CHATMACHINE> ";

int main()
{
    cout << "Chatmachine v1.0 Copyright (C) 2017 Simon Grandsire\n" << endl;

    while(1) {
        try {
            listen();
            respond();
        } catch(std::string message) {
            cerr << message << endl;
        } catch(...) {
            cerr << "Unexpected error." << endl;
        }
    }

    return 0;
}

void listen()
{
    cout << sUserPrompt;
    getline(std::cin, sInput);
}

void respond() {
    string response;

    if (sInput == "") {
        std::cout << sBotPrompt << "Hmm." << std::endl;
        return;
    }

    if (response.empty()) {
        cout << sBotPrompt <<  "I don't understand what you're saying." << std::endl;
    } else {
        std::cout << sBotPrompt << sResponse << std::endl;
    }
}
