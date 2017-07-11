#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "strings.h"
#include "aimltemplateelement.h"
#include "aimltext.h"

using namespace std;
using namespace aiml;

TemplateElement::TemplateElement(vector<TemplateElement*> elements) {
	for (int i=0, s=elements.size(); i<s; ++i) {
        //cout << "TemplateElement(elements) : elements[" << i << "][" << elements[i] << "]" << endl;
		if(elements[i]) {
			if (TemplateElement* te = dynamic_cast<TemplateElement*>(elements[i])) {
	            m_vtChildren.push_back(te);
			} else {
				Text* text = new Text(elements[i]->toString());

	            m_vtChildren.push_back(text);
	        }
    	}
	}
}

vector<TemplateElement*> TemplateElement::getChildren() {
	return m_vtChildren;
}

void TemplateElement::appendChild(AIMLElement* element) {
	m_vtChildren.push_back((TemplateElement*) element);
}

void TemplateElement::appendChildren(vector<AIMLElement*> elements) {
	for (int i=0, s=elements.size(); i<s; ++i)
		m_vtChildren.push_back((TemplateElement*) elements[i]);
}

vector<TemplateElement*> TemplateElement::children() {
	return m_vtChildren;
}

void TemplateElement::setChildren(vector<TemplateElement*> elements) {
	m_vtChildren.clear();

	for(int i=0, s=elements.size(); i<s; ++i) {
		m_vtChildren.push_back(elements[i]);
	}
}
