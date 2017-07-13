//
// Program Name: chatmachine
// Description: a chatbot in c++ using an AIML base
//
// Author: Simon Grandsire
//

#include "chatmachine.h"
#include "categorylist.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>
#include "tinyxml.h"
#include "aimlparser.h"
#include "xml.h"

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

CategoryList* cl;
vector<CategoryList*> cls;

map<string, string> mVars;

int main()
{
    cout << "Chatmachine v2.0 Copyright (C) 2017 Simon Grandsire\n" << endl;

    Chatmachine cm("Chatmachine");

    cout << "Loading data..." << endl;

    cm.createCategoryLists();

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
    vector<lev_pat_templ> levTempls;
    TiXmlDocument doc;
    TiXmlElement* root;
    Template* bestTemplate;
    Pattern* bestPattern;
    string bestResponse;
    unsigned int bestLevDist, bestIndex;

    for(unsigned int i=0, clss=cls.size(); i<clss; ++i) {
        levTempls.push_back(parse_categoryList(cls[i], input, m_sPrevResponse, mVars));
    }

    bestLevDist = levTempls[0].patternLevDist;
    bestIndex = 0;

    for(int i=1, s=levTempls.size(); i<s; ++i) {
        if (bestLevDist > levTempls[i].patternLevDist && levTempls[i].templ->toString() != "") {
            bestLevDist = levTempls[i].patternLevDist;
            bestIndex = i;
        }
    }

    bestTemplate = levTempls[bestIndex].templ;
    bestPattern = levTempls[bestIndex].pat;
    bestResponse = bestTemplate->toString();

    bestResponse = parse_template(cls[bestIndex], bestPattern, bestTemplate, input, m_sPrevResponse, mVars);

    return bestResponse;
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
    toUpper(input);
    shrink(input);
    insert_spaces(input);

    m_sInput = input;

    m_bInput_prepared = 1;
}

void Chatmachine::createCategoryLists() {
    TiXmlDocument doc;
    TiXmlElement* root;
    unsigned int aimlFilesSize = basicAimlFilesSize;
    string* aimlFiles = basicAimlFiles;

    while(m_nFileIndex < aimlFilesSize) {
        string sAimlFile;
        const char* aimlFile;

        sAimlFile = dataDir + aimlFiles[m_nFileIndex] + ".aiml";
        aimlFile = sAimlFile.c_str();

        cl = new CategoryList(aimlFiles[m_nFileIndex]);
        cls.push_back(cl);

        if (!doc.LoadFile(aimlFile)) {
            cerr << doc.ErrorDesc() << " " << aimlFile << endl;
            return;
        }

        root = doc.FirstChildElement();

        if (root == NULL) {
            cerr << "Failed to load file: No root element. " << aimlFile << endl;
            doc.Clear();
            return;
        }

        createCategoryList(cl, root);

        m_nFileIndex++;
    }

    //to do
    //cout << cl << endl;
}
