#ifndef __AIMLTOPIC_H__
#define __AIMLTOPIC_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "strings.h"
#include "aimlelement.h"
#include "aimlcategory.h"

using namespace std;

namespace aiml {
    class Category;

    class Topic : public AIMLElement {
    public:
        Topic() {}
        Topic(string name, vector<Category*> children)
            :m_sName(name), m_vCategories(children) {}

        vector<string> elements();

        string toString();

        vector<Category*> categories();

        void appendChild(AIMLElement* child);
        void appendChildren(vector<AIMLElement*> children);
    private:
        
    private:
        vector<Category*> m_vCategories;
        string m_sName;
    };
}

#endif
