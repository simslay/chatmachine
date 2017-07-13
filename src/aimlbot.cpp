#include "aimlbot.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Bot::name() {
	return m_sName;
}

string Bot::toString() {
	return "<bot" + m_sName + "/>";
}
