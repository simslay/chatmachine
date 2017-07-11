#include "aimlstar.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Star::toString() {
	return "<star index=\"" + to_string(m_iIndex) + "\"/>";
}

unsigned int Star::index() {	
	return m_iIndex;
}
