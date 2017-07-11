#ifndef __AIMLTHINK_H__
#define __AIMLTHINK_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "aimltemplateelement.h"
#include <vector>

using namespace std;

namespace aiml {
    class Think : public TemplateElement {
    public:
        Think(vector<TemplateElement*> elements) :TemplateElement(elements) {}

        string toString();
    private:
    };
}

#endif
