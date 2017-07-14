#include "aimlset.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Set::name() {
	return m_sName;
}

string Set::toString() {
	return "<set name=\""+m_sName+"\"></set>";
}
