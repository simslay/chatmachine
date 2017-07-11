#include "aimltemplate.h"

using namespace std;

void Template::appendChild(AIMLElement* child) {

}

void Template::appendChildren(vector<AIMLElement*> children) {

}

string Template::toString() {
	string value = "";
	vector<TemplateElement*> childr = children();

    for (int i=0, s=childr.size();i<s; ++i) {
		value.append(childr[i]->toString());
    }

	return value;
}
