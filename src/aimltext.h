#ifndef __AIMLTEXT_H__
#define __AIMLTEXT_H__

#include <vector>
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Text : public TemplateElement {
    public:
        Text() {}
        Text(string value) :m_sValue(value) {}

        string toString();
    private:
    private:
    	string m_sValue;
    };
}

#endif
