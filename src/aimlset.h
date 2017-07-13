#ifndef __AIMLSET_H__
#define __AIMLSET_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "aimltemplateelement.h"
#include <vector>

using namespace std;

namespace aiml {
    class Set : public TemplateElement {
    public:
        Set (string name, vector<TemplateElement*> elements)
            :TemplateElement(elements), m_sName(name) {}

        string name();
        string toString();
    private:
    private:
        string m_sName;
    };
}

#endif
