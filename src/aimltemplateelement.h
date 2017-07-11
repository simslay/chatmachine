#ifndef __AIMLTEMPLATEELEMENT_H__
#define __AIMLTEMPLATEELEMENT_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"
#include "aimlelement.h"

using namespace std;
using namespace aiml;

namespace aiml {
    class TemplateElement : public AIMLElement {
    public:
        TemplateElement() {}
        TemplateElement(vector<TemplateElement*> elements);

        vector<TemplateElement*> getChildren();

        void appendChild(AIMLElement* child);
		void appendChildren(vector<AIMLElement*> children);

        virtual string toString() = 0;

        vector<TemplateElement*> children();

        void setChildren(vector<TemplateElement*> elements);
    private:
        /*const */vector<TemplateElement*> m_vtChildren;
    };
}

#endif
