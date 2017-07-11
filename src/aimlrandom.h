#ifndef __AIMLRANDOM_H__
#define __AIMLRANDOM_H__

#include <vector>
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Random : public TemplateElement {
    public:
        Random(vector<TemplateElement*> children) :TemplateElement(children) {}

        string toString();
    private:
    private:
    };
}

#endif
