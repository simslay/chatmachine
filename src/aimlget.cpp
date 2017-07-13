#include "aimlget.h"
#include "aimltemplateelement.h"

using namespace std;
using namespace aiml;

string Get::name() {
	return m_sName;
}

string Get::toString() {
	return "<set></set>";
}
