#ifndef __CHATMACHINE_H__
#define __CHATMACHINE_H__

#include <string>
#include <vector>

using namespace std;

class Chatmachine {
public:
    Chatmachine (string str)
        :m_sChatBotName(str), m_sInput(""), m_bInput_prepared(0), m_nFileIndex(0), m_sPrevResponse("")
    {
        init_random();
    }

    void listen();
    void respond();

private:
    void init_random();
    void normalize(string &input);
    string get_response(string input);
    string get_best_response(string input);
    void setResponse(string sResponse);
    void prepare_response(string &resp);

private:
    string m_sChatBotName;
    string m_sInput;
    string m_sResponse;
    string m_sPrevInput;
    string m_sPrevResponse;
    string m_sSubject;
    string m_sAimlFile;
    vector<string> m_vsInputTokens;
    bool m_bInput_prepared;
    unsigned int m_nFileIndex;
    vector<string> response_list;
};

#endif
