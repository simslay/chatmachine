#ifndef __AIMLSTAR_H__
#define __AIMLSTAR_H__

#include <vector>
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Star : public TemplateElement {
    public:
        Star(vector<const char*> attributes) {
    		string value = attributes.size() == 0 ? "" : string(attributes.at(0));

    		m_iIndex = value.empty() ? 1 : stoi(value);
  		}
        Star(int index) :m_iIndex(index) {}

        string toString();
        
        unsigned int index();
    private:
    private:
    	unsigned int m_iIndex;
    };
}

#endif
