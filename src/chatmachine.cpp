//
// Program Name: chatmachine
// Description: a chatbot in c++ using an AIML base
//
// Author: Simon Grandsire
//

#include "chatmachine.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

string basicAimlFiles[] = {
    "bot",
    "condition",
    "default",
    "random",
    "setget",
    "srai",
    "star",
    "that",
    "think",
    "topic"
};

size_t basicAimlFilesSize = sizeof(basicAimlFiles)/sizeof(basicAimlFiles[0]);

string dataDir = "database/Basic/";

string sUserPrompt = "USER> ";
string sBotPrompt = "CHATMACHINE> ";

int main()
{
    cout << "Chatmachine v2.0 Copyright (C) 2017 Simon Grandsire\n" << endl;

    Chatmachine cm("Chatmachine");

    cout << "Loading data..." << endl;

    while(1) {
        try {
            cm.listen();
            cm.respond();
        } catch(std::string message) {
            cerr << message << endl;
        } catch(...) {
            cerr << "Unexpected error." << endl;
        }
    }

    return 0;
}

void Chatmachine::init_random() {
    srand((unsigned) time(NULL));
}

void Chatmachine::listen() {
    cout << sUserPrompt;
    getline(cin, m_sInput);

    if (m_sInput != "")
        normalize(m_sInput);
}

void Chatmachine::respond() {
    string response;

    init_random();

    if (m_sInput == "") {
        cout << sBotPrompt << "Hmm." << endl;
        return;
    }

    if (m_sPrevInput != "" && m_sInput == m_sPrevInput) {
        cout << sBotPrompt << "You have already said that." << endl;
        return;
    }

    response = get_response(m_sInput);

    if (response.empty()) {
        cout << sBotPrompt <<  "I don't understand what you're saying." << endl;
    } else {
        setResponse(response);

        cout << sBotPrompt << m_sResponse << endl;
    }
}

string Chatmachine::get_response(string input) {
    string bestResponse;

    bestResponse = get_best_response(input);
    
    return bestResponse;
}

string Chatmachine::get_best_response(string input) {
    return "";
}

void Chatmachine::setResponse(string response) {
    m_sResponse = response;
    prepare_response(m_sResponse);

    m_sPrevResponse = m_sResponse;
    m_sPrevInput = m_sInput;
}

void Chatmachine::prepare_response(string &resp) {

}

void Chatmachine::normalize(string &input) {
    //subsitute(input, subs);
    //toUpper(input);
    //shrink(input);
    //insert_spaces(input);

    //m_sInput = input;

    //m_bInput_prepared = 1;
}
