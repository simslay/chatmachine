#ifndef __AIMLLI_H__
#define __AIMLLI_H__

#include <vector>
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Li : public TemplateElement {
    public:
        Li(string name, string value, vector<TemplateElement*> children)
        	:TemplateElement(children), m_sName(name), m_sValue(value) {}

        string name();
        string value();
        string toString();
    private:
    private:
    	string m_sName;
    	string m_sValue;
    };
}

#endif
