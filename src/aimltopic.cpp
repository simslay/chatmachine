#include "aimltopic.h"
#include "strings.h"

using namespace std;
using namespace aiml;

vector<string> Topic::elements()
{
	return split(m_sName);
}

string Topic::toString() {
    string result = "";

    for (int i=0, s=m_vCategories.size(); i<s; ++i) {
		result.append(m_vCategories[i]->toString());
		result.append("\n");
    }
    
	return result;
}

vector<Category*> Topic::categories() {
	return m_vCategories;
}

void Topic::appendChild(AIMLElement* child) {
    Category* category = (Category*) child;

    category->setTopic(this);

    m_vCategories.push_back(category);
}
  
void Topic::appendChildren(vector<AIMLElement*> children) {
	for(int i=0, s=children.size(); i<s; ++i)
  		appendChild(children[i]);
}
