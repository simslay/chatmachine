#include "aimlpattern.h"
#include "aimlelement.h"
#include <string>
#include <vector>

using namespace std;
using namespace aiml;


vector<string> Pattern::getElements() {
    return m_vPattern;
}

void Pattern::appendChild(AIMLElement* child) {

}

void Pattern::appendChildren(vector<AIMLElement*> children) {

}

string Pattern::toString() {
	string buffer = "";

    for (int i = 0, n = m_vPattern.size();;) {
		buffer.append(m_vPattern[i]);

		//cout << "toString() : " << m_vPattern[i] << endl;

		if (++i >= n)
			break;

		buffer.append(" ");
	}

    return buffer;
}
