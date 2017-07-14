#include "aimlli.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Li::name() {
	return m_sName;
}

string Li::value() {
	return m_sValue;
}

string Li::toString() {
	return "<li></li>";
}
