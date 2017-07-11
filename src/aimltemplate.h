#ifndef __AIMLTEMPLATE_H__
#define __AIMLTEMPLATE_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Template : public TemplateElement {
    public:
        Template() {}
        Template(vector<TemplateElement*> children) :TemplateElement(children) {}

        void appendChild(AIMLElement* child);
        void appendChildren(vector<AIMLElement*> children);

        string toString();
    private:
    private:

    };
}

#endif
