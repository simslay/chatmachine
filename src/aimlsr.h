#ifndef __AIMLSR_H__
#define __AIMLSR_H__

#include <vector>
#include "aimltemplateelement.h"
#include "aimlsrai.h"
#include "aimlstar.h"
#include "tinyxml.h"

#define TIXML_USE_STL

using namespace std;

namespace aiml {
    class Sr : public Srai {
    public:
        Sr(vector<const char*> attributes) :Srai(attributes) {
        	Star* star = new Star(attributes);
		    vector<TemplateElement*> elements;

		    elements.push_back(star);

		    setChildren(elements);
        }
    private:
    private:
    	
    };
}

#endif
