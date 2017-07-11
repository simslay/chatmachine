#include "aimlsrai.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Srai::toString() {
	vector<TemplateElement*> children = TemplateElement::children();
	string res = "";

	for(int i=0, l=children.size(); i<l; ++i) {
		res += children[i]->toString();
	}

	return res;
}
