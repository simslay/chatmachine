#ifndef __AIMLBOT_H__
#define __AIMLBOT_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "aimltemplateelement.h"
#include <vector>

using namespace std;

namespace aiml {
    class Bot : public TemplateElement {
    public:
        Bot(string name) :m_sName(name) {}

        string toString();
        string name();
    private:
    private:
        string m_sName;
    };
}

#endif
