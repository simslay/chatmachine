#ifndef __AIMLBR_H__
#define __AIMLBR_H__

#include <vector>
#include "aimltemplateelement.h"

using namespace std;

namespace aiml {
    class Br : public TemplateElement {
    public:
        Br() {}

        string toString();
    private:
    private:
    };
}

#endif
