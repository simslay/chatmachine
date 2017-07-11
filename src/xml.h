#ifndef __XML_H__
#define __XML_H__

#include "tinyxml.h"
#include "chatmachine.h"
#include "aimltemplate.h"
#include "aimlpattern.h"
#include <string>
#include <vector>
#include <map>

#define TIXML_USE_STL

using namespace std;

typedef struct {
    string file;
    vector<string> tokens;
} lex_field;

typedef struct {
	unsigned int patternLevDist;
	string bestResponse;
} lev_rep;

typedef struct {
	unsigned int patternLevDist;
	Pattern* pat;
	Template* templ;
} lev_pat_templ;

bool patternMatches(std::string pattern, std::string input);
bool split(std::string pattern, std::string input, vecstr &vsPat, vecstr &vsInp);

#endif
