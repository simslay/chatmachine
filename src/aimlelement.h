#ifndef __AIMLELEMENT_H__
#define __AIMLELEMENT_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"

using namespace std;

namespace aiml {
    class AIMLElement {
    public:
        virtual void appendChild(AIMLElement* child) = 0;
        virtual void appendChildren(vector<AIMLElement*> children) = 0;
        virtual string toString() = 0;
    protected:

    };
}

#endif
