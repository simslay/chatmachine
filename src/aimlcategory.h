#ifndef __AIMLCATEGORY_H__
#define __AIMLCATEGORY_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"
#include "aimlelement.h"
#include "aimltopic.h"
#include "aimlpattern.h"
#include "aimltemplate.h"
#include "aimlthat.h"

using namespace std;

namespace aiml {
    class Pattern;
    class Template;
    class That;
    class Topic;

    class Category : public AIMLElement {
    public:
        Category() {}
        Category(Pattern* pattern, That* that, Topic* topic, Template* templ)
        :m_pPattern(pattern), m_tThat(that), m_tTopic(topic), m_tTemplate(templ) {}
        Category(Pattern* pattern, Template* templ);

        ~Category() {
            delete(m_pPattern);
            delete(m_tTemplate);
            delete(m_tThat);
            delete(m_tTopic);
        }

        vector<string> getMatchPath();
        void appendChild(AIMLElement* child);
        void appendChildren(vector<AIMLElement*> children);

        void setTopic(Topic* topic);
        string toString();

        Pattern* pattern();
        Template* templ();
    private:

    private:
        Pattern* m_pPattern;
        Template* m_tTemplate;
        That* m_tThat;
        Topic* m_tTopic;
    };
}

#endif
