#ifndef __AIMLGET_H__
#define __AIMLGET_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "aimltemplateelement.h"
#include <vector>

using namespace std;

namespace aiml {
    class Get : public TemplateElement {
    public:
        Get(string name) :m_sName(name) {}

        string name();
        string toString();
    private:
    private:
        string m_sName;
    };
}

#endif
