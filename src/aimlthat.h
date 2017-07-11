#ifndef __AIMLTHAT_H__
#define __AIMLTHAT_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "aimltemplateelement.h"
#include <vector>

using namespace std;

namespace aiml {
    class That : public TemplateElement {
    public:
        That() {}
        That (vector<TemplateElement*> elements) :TemplateElement(elements) {}

        string toString();

        vector<string> elements();
    private:
    	int m_iResponseIndex = 1;
    	int m_iSentenceIndex = 1;
    };
}

#endif
