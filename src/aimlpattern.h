#ifndef __AIMLPATTERN_H__
#define __AIMLPATTERN_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"
#include "aimlelement.h"

using namespace std;

namespace aiml {
    class Pattern : public AIMLElement {
    public:
        Pattern() {}
        Pattern(string pattern) {
            m_vPattern = split(trim(pattern));
        }

        vector<string> getElements();

        void appendChild(AIMLElement* child);
        void appendChildren(vector<AIMLElement*> children);

        string toString();
    private:
        vector<string> m_vPattern;
    };
}

#endif
