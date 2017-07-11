#include "aimlcategory.h"
#include "strings.h"
#include "aimltopic.h"
#include "aimlthat.h"
#include "aimltext.h"
#include <typeinfo>

using namespace std;
using namespace aiml;

Category::Category(Pattern* pattern, Template* templ)
:m_pPattern(pattern), m_tTemplate(templ) {
    m_tThat = new That();
    m_tTopic = new Topic();
}

vector<string> Category::getMatchPath() {
    vector<string> pattPath = m_pPattern->getElements();
    vector<string> thatPath = m_tThat->elements();
    vector<string> topicPath = m_tTopic->elements();
    int m = pattPath.size();
    int n = thatPath.size();
    int o = topicPath.size();
    vector<string> matchPath(m + 1 + n + 1 + o);

    matchPath[m] = "<THAT>";
    matchPath[m + 1 + n] = "<TOPIC>";

    arraycopy(pattPath, 0, matchPath, 0, m);
    arraycopy(thatPath, 0, matchPath, m + 1, n);
    arraycopy(topicPath, 0, matchPath, m + 1 + n + 1, o);

    return matchPath;
}

void Category::appendChild(AIMLElement* child) {
    if (Pattern* p = dynamic_cast<Pattern*>(child))
        m_pPattern = (Pattern*) child;
    else if (That* p = dynamic_cast<That*>(child))
        m_tThat = (That*) child;
    else if (Template* p = dynamic_cast<Template*>(child))
        m_tTemplate = (Template*) child;
    else
        throw new string("Invalid element of type " + string(typeid(child).name()) + ": (" + child->toString() + ")");
}

void Category::appendChildren(vector<AIMLElement*> children) {
    for (int i=0, s=children.size(); i<s; ++i)
        appendChild(children[i]);
    
    if (m_tThat == NULL) {
        vector<TemplateElement*> elements;

        elements.push_back(new Text("*"));
        m_tThat = new That(elements);
    }
}

void Category::setTopic(Topic* topic) {
    m_tTopic = topic;
}

string Category::toString() {
    return "[" + m_pPattern->toString() + "][" + m_tThat->toString() + "][" + m_tTemplate->toString() + "]";
}

Pattern* Category::pattern() {
    return m_pPattern;
}

Template* Category::templ() {
    return m_tTemplate;
}
