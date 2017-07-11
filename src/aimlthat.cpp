#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "strings.h"
#include "aimlthat.h"

using namespace std;
using namespace aiml;

vector<string> That::elements() {
    vector<TemplateElement*> children = getChildren();
	vector<string> elements;

	for (int i = 0, n = children.size(); i < n; i++) {
  		string text = children[i]->toString();
  		text = trim(text);
  		vector<string> vsText = split(text);

  		for(int j=0, m=vsText.size(); j<m; ++j) {
            elements.push_back(vsText[j]);
  		}
	}

	return elements;
}

string That::toString() {
    if (children().size() == 0)
		return "<that index=\"" + to_string(m_iResponseIndex) + ", " + to_string(m_iSentenceIndex) + "\"/>";
	else {
		string builder = "<that>";
		vector<TemplateElement*> children = TemplateElement::children();

		for (int i=0, s=children.size(); i<s; ++i)
			builder.append(children[i]->toString());

      	builder.append("</that>");

		return builder;
    }
}
