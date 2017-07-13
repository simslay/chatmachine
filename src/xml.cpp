#include "xml.h"
#include "aimlparser.h"
#include "strings.h"
#include "chatmachine.h"
#include "tinyxml.h"
#include <string>
#include <iostream>
#include <limits.h>
#include <regex>
#include <map>

using namespace std;

#define TIXML_USE_STL

string thinkText = "";

bool patternMatches(string pattern, string input) {
    vecstr vsInput;
    vecstr vsPattern;
    vecstr vsPat;
    vecstr vsInp;
    bool star = pattern.find("*") != string::npos;

    if (pattern.find(input) != std::string::npos) {
        //cout << "patternMatches(" << pattern << ", " << input << ")" << endl;
        return true;
    }

    vsInput = split(input); // sep=' '
    vsPattern = split(pattern); // sep=' '

    if (star) {
        regex re(R"(^\s*\*\s*$)");
        smatch sm;

        //cout << "patternMatches : pattern[" << pattern << "]" << endl;

        if (regex_match(pattern, re)) {
            //cout << "patternMatches(string pattern, string input) : true" << endl;
            return true;
        }

        split(pattern, input, vsPat, vsInp);
    }

    if (vsPattern.size() > vsInput.size()) {
        return false;
    }

    if (star) {
        if (vsInp.size() == 0) {
            //cout << "patternMatches(" << pattern << ", " << input << ") : vsInp.size() = 0" << endl;
            return false;
        }

        for(int i=0, l=vsPat.size(); i<l; ++i) {
            //cout << "vsPat[" << i << "][" << vsPat[i] << "]" << endl;
            //cout << "vsInp[" << i*2 << "][" << vsInp[i*2] << "]" << endl;
            if (i*2 < vsInp.size()) {
                if (vsPat[i] != vsInp[i*2]) {
                    //cout << "patternMatches() : false" << endl;
                    return false;
                }
            }
        }

        //cout << "patternMatches() : true" << endl;
        return true;
    }

    return false;
}

// A * IS A * OK
// A MANGO IS A FRUIT OK
// vsInp={"A", "MANGO", "IS A", "FRUIT", "OK"}
//
// DO YOU KNOW WHO * IS
// DO YOU KNOW WHO ALBERT IS
// vsPat={"DO YOU KNOW WHO", "IS"}
// vsInp={"DO YOU KNOW WHO", "ALBERT", "IS"}
bool split(string pattern, string input, vector<string> &vsPat, vector<string> &vsInp) {
    vector<string> vsPattern;
    int cur = 0;
    string patternRegexString;
    string result;
    unsigned int cumul = 0;

    if (pattern.size() > input.size()) {
        return false;
    }

    Split(vsPattern, pattern, '*');

    cout << "split() : pattern=" << pattern << endl;

    vsPat = vsPattern;

    //cout << "split() : vsPat.size()[" << vsPat.size() << "]" << endl;

    for(int i=0; i<vsPat.size(); ++i) {
        string p = vsPat[i];

        shrink(p);
        vsPat[i] = p;
        vsPattern[i] = p;
        //cout << "split() : vsPat[" << i << "][" << vsPat[i] << "]" << endl;
    }

    for(int i=0, s1=vsPattern.size(); i<s1; ++i) {
        if (pattern[0] == '*' && vsPattern[i] != "") {
            patternRegexString.append("(.*)");
            patternRegexString.append(vsPattern[i]);
            //cout << "split() : vsPattern[i][" << vsPattern[i] << "]" << endl;
        } else if (vsPattern[i] != "") {
            patternRegexString.append(vsPattern[i]);
            if (i < s1-1)
                patternRegexString.append("(.*)");
        }
    }

    try {
        regex re(patternRegexString);
        smatch sm;

        /*cout << "split" << endl;
        for(int i=0; i<vsPattern.size(); i++) {
            cout << "vsPattern[" << i << "][" << vsPattern[i] << "]" << endl;
        }*/

        //cout << "split() : patternRegexString[" << patternRegexString << "]" << endl;
        //cout << "split() : input[" << input << "]" << endl;

        bool b = regex_search(input, sm, re);

        //cout << "split() : b[" << b << "]" << endl;
        //cout << "split() : sm.size()[" << sm.size() << "]" << endl;

        if (b && sm.size() > 1) {
            //cout << "sm.size()[" << sm.size() << "]" << endl;
            for(int i=0, s=vsPattern.size(); i<s; ++i) {
                //cout << cumul << endl;
                string pat = vsPattern[i];
                //cout << "pat=" << pat << endl;
                //cout << "pat.size()=" << pat.size() << endl;
                string token = input.substr(cumul, pat.size()+1);

                shrink(token);
                vsInp.push_back(token);

                //cout << token << endl;

                cumul += pat.size();

                if (i+1 < sm.size() && sm[i+1] != "") {
                    string tok = sm[i+1];

                    shrink(tok);

                    vsInp.push_back(tok);
                    cumul += string(sm[i+1]).size();
                }
            }
        } else {
            return false;
        }
    } catch (regex_error& e) {
        return false;
    }

    //cout << "split() : return true" << endl;
    //for(int i=0, s=vsInp.size(); i<s; ++i) {
    //    cout << vsInp[i] << endl;
    //}

    return true;
}
