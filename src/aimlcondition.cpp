#include "aimlcondition.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Condition::name() {
	return m_sName;
}

string Condition::value() {
	return m_sValue;
}

string Condition::toString() {
	return "<condition></condition>";
}
