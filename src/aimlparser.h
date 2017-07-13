#ifndef __AIMLPARSER_H__
#define __AIMLPARSER_H__

#include "tinyxml.h"
#include "chatmachine.h"
#include "categorylist.h"
#include "aimlsrai.h"
#include "aimlsr.h"
#include "aimlstar.h"
#include "aimlrandom.h"
#include "aimlli.h"
#include "aimlthat.h"
#include "aimlset.h"
#include "aimlget.h"
#include "aimlbot.h"
#include "aimlthink.h"
#include "aimlcondition.h"
#include "aimlbr.h"
#include "aimlcategory.h"
#include "xml.h"
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace aiml;

#define TIXML_USE_STL

void loadData(string aimlFiles[], unsigned int aimlFilesSize, vector<lex_field> &vLexFields, string dir);
lev_pat_templ parse_categoryList(CategoryList* cl, string input, string prevTemplate, map<string, string> &mVars);
lev_pat_templ parse_category(CategoryList* cl, Category* nCategory, string input, string prevTemplate, map<string, string> &mVars);
string parse_template(CategoryList* cl, Pattern* pattern, Template* templ, string input, string prevTemplate, map<string, string> &mVars);
string parse_bot(CategoryList* cl, Bot* bot, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars);
string parse_srai(CategoryList* cl, Srai* srai, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars);
string parse_star(CategoryList* cl, Star* star, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars);
void createCategoryList(CategoryList* cl, TiXmlElement* root);
void createCategories(CategoryList* cl, TiXmlElement* eCategory, string sTopic);
TemplateElement* createTemplateElement(TiXmlNode* nTemplateElement);
Srai* createSrai(TiXmlNode* nSrai);
Sr* createSr(TiXmlNode* nSr);
Star* createStar(TiXmlNode* nStar);
Random* createRandom(TiXmlNode* nRandom);
Li* createLi(TiXmlNode* nLi);
That* createThat(TiXmlNode* nThat);
Set* createSet(TiXmlNode* nSet);
Get* createGet(TiXmlNode* nGet);
Bot* createBot(TiXmlNode* nBot);
Think* createThink(TiXmlNode* nThink);
Condition* createCondition(TiXmlNode* nCond);
Br* createBr();

#endif
