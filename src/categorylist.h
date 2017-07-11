#ifndef __CATEGORYLIST_H__
#define __CATEGORYLIST_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include "aimlelement.h"
#include "aimlcategory.h"

using namespace std;

namespace aiml {
    class CatgeoryList {
    public:
        CatgeoryList() :m_uSize(0) {}
        CatgeoryList(string file) :m_uSize(0), m_sFile(file) {}

        void append(Category* category);
        Category* child(int index);
        string file();
        unsigned int size();

    private:

    private:
        vector<Category*> m_vChildren;
        string m_sFile;
        unsigned int m_uSize;
    };
}
#endif
