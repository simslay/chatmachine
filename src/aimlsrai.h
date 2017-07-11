#ifndef __AIMLSRAI_H__
#define __AIMLSRAI_H__

#include <vector>
#include "aimltemplateelement.h"
#include "tinyxml.h"

#define TIXML_USE_STL

using namespace std;

namespace aiml {
    class Srai : public TemplateElement {
    public:
        Srai() {}
        Srai(vector<TemplateElement*> elements) :TemplateElement(elements) {}
        Srai(vector<const char*> attributes) {}

        string toString();
    private:
    private:
    	
    };
}

#endif
