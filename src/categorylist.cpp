#include "categorylist.h"
#include <map>

using namespace std;
using namespace aiml;

void CatgeoryList::append(Category* category) {
    m_vChildren.push_back(category);
    m_uSize++;
}

Category* CatgeoryList::child(int index) {
	return m_vChildren[index];
}

string CatgeoryList::file() {
	return m_sFile;
}

unsigned int CatgeoryList::size() {
	return m_uSize;
}
