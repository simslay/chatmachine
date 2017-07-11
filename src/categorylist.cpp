#include "categorylist.h"
#include <map>

using namespace std;
using namespace aiml;

void CategoryList::append(Category* category) {
    m_vChildren.push_back(category);
    m_uSize++;
}

Category* CategoryList::child(int index) {
	return m_vChildren[index];
}

string CategoryList::file() {
	return m_sFile;
}

unsigned int CategoryList::size() {
	return m_uSize;
}
