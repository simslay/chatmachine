#include "aimlparser.h"
#include "strings.h"
#include "chatmachine.h"
#include "aimltext.h"
#include "aimltopic.h"
#include "aimlsrai.h"
#include "aimlrandom.h"
#include "aimlsr.h"
#include "aimlstar.h"
#include "aimlli.h"
#include "aimlthat.h"
#include "aimlset.h"
#include "aimlget.h"
#include "aimlbot.h"
#include "aimlthink.h"
#include "aimlcondition.h"
#include "aimlbr.h"
#include "aimlcategory.h"
#include "tinyxml.h"
#include "xml.h"
#include <string>
#include <iostream>
#include <limits.h>
#include <map>

using namespace std;

#define TIXML_USE_STL

Topic* topic;

lev_pat_templ parse_categoryList(CategoryList* cl, string input, string prevTemplate, map<string, string> &mVars) {
    unsigned int bestLev = UINT_MAX;
    lev_pat_templ levPatTempl;

    //to do
    //if (cl->size() > 0)
    //    response = cl->child(0)->templ()->toString();

    //cout << "parse_graph input=" << input << endl;

    for (int i=0, s=cl->size(); i<s; ++i) {
        Category* category = cl->child(i);
        lev_pat_templ lt = parse_category(cl, category, input, prevTemplate, mVars);

        //cout << bestLev << endl;
        //cout << lt.bestResponse << endl;

        if (bestLev > lt.patternLevDist) {
            bestLev = lt.patternLevDist;
            levPatTempl = {lt.patternLevDist, lt.pat, lt.templ};
        }
    }

    //cout << bestLev << endl;

    return levPatTempl;
}

lev_pat_templ parse_category(CategoryList* cl, Category* category, string input, string prevTemplate, map<string, string> &mVars) {
    string sPattern = "";
    TiXmlNode* bestPattern = NULL;
    TiXmlNode* bestTemplate = NULL;
    TiXmlNode* nPattern = NULL;
    TiXmlNode* bestThat = NULL;

    sPattern = category->pattern()->toString();

    //cout << "parse_category sPattern=" << sPattern << endl;

    lev_pat_templ levTempl = {edit_distance(input, sPattern), category->pattern(), category->templ()};

    return levTempl;
}

string parse_template(CategoryList* cl, Pattern* pattern, Template* templ, string input, string prevTemplate, map<string, string> &mVars) {
    string response = "";
    vector<TemplateElement*> children;
    string sPattern = pattern->toString();

    children = templ->children();

    for (int i=0, s=children.size(); i<s; ++i) {
        TemplateElement* te = children[i];

        if (Text* t = dynamic_cast<Text*>(te)) {
            //cout << response << endl;
            response += t->toString() + " ";
        } else if (Srai* srai = dynamic_cast<Srai*>(te)) {
            //cout << "parse_template srai" << endl;
            response += parse_srai(cl, srai, pattern, input, prevTemplate, mVars) + " ";
            //cout << "parse_template srai response=" << response << endl;
        } else if (Star* star = dynamic_cast<Star*>(te)) {
            //cout << "parse_template star" << endl;
            response += parse_star(cl, star, pattern, input, prevTemplate, mVars) + " ";
        } else if (Bot* bot = dynamic_cast<Bot*>(te)) {
            response += parse_bot(cl, bot, pattern, input, prevTemplate, mVars) + " ";
        } else if (Get* get = dynamic_cast<Get*>(te)) {
            response += parse_get(cl, get, pattern, input, prevTemplate, mVars) + " ";
        } else if (Set* set = dynamic_cast<Set*>(te)) {
            Template* templ = new Template(te->children());

            response += parse_set(cl, set, parse_template(cl, pattern, templ, input, prevTemplate, mVars), pattern, input, prevTemplate, mVars) + " ";
        } else if (Think* think = dynamic_cast<Think*>(te)) {
            response += parse_think(cl, think, pattern, input, prevTemplate, mVars) + " ";
        } else if (Condition* condition = dynamic_cast<Condition*>(te)) {
            vector<TemplateElement*> childr = te->children();

            //<condition>
            //  <li name="state" value="happy">I am happy!</li>
            //  <li name="state" value="sad">I am sad!</li>
            //</condition>
            //or
            //<condition name="state">
            //  <li value="happy">I am happy!</li>
            //  <li value="sad">I am sad!</li>
            //</condition>
            if (childr.size() > 0 && dynamic_cast<Li*>(childr[0])) {
                response += parse_condition(cl, childr, pattern, input, prevTemplate, mVars);
            //<condition name="state" value="happy">I am happy!</condition>
            //<condition name="state" value="sad">I am sad!</condition>
            } else {
                while(i<s && dynamic_cast<Condition*>(children[i])) {
                    response += parse_condition(cl, dynamic_cast<Condition*>(children[i]), pattern, input, prevTemplate, mVars);
                    i++;
                }
            }

            //do other cases:
            //<condition name="gender">
            //<li value="female"> attractive.</li>
            //<li value="male"> handsome.</li>
            //</condition>
            //and
            //<condition>
            //<li name="gender" value="female"> attractive.</li>
            //<li> handsome.</li>
            //</condition>
        }
    }

    //cout << response << endl;

    return response;
}

string parse_condition(CategoryList* cl, vector<TemplateElement*> lis, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    string response = "";

    for (int i=0, s=lis.size(); i<s; ++i) {
        Li* li = dynamic_cast<Li*>(lis[i]);
        Condition* cond = new Condition(li->name(), li->value(), li->children());

        response += parse_condition(cl, cond, pattern, input, prevTemplate, mVars);
    }

    return response;
}

string parse_condition(CategoryList* cl, Condition* condition, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    string name = condition->name();
    string value = condition->value();
    string getValue = parse_get(cl, new Get(name), pattern, input, prevTemplate, mVars);
    vector<TemplateElement*> children = condition->children();

    //cout << (getValue == value ? "true" : "false") << endl;

    return getValue == value ? parse_template(cl, pattern, new Template(children), input, prevTemplate, mVars) : "";
}

string parse_think(CategoryList* cl, Think* think, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    vector<TemplateElement*> children = think->children();
    Template* templ = new Template(children);

    parse_template(cl, pattern, templ, input, prevTemplate, mVars);

    return "";
}

string parse_bot(CategoryList* cl, Bot* bot, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    TiXmlDocument doc;
    TiXmlElement* root;
    string botPath = "database/bot.xml";

    if (!doc.LoadFile(botPath.c_str())) {
        cerr << doc.ErrorDesc() << " " << botPath << endl;
        return "";
    }

    root = doc.FirstChildElement();

    if (root == NULL) {
        cerr << "Failed to load file: No root element. " << botPath << endl;
        doc.Clear();
        return "";
    }

    TiXmlElement* elem = root->FirstChildElement();

    for(TiXmlElement* e = elem; e; e = e->NextSiblingElement()) {
        if (e->Attribute("name") == bot->name()) {
            return e->FirstChild()->ToText()->Value();
        }
    }

    return "";
}

string parse_get(CategoryList* cl, Get* get, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    TiXmlDocument doc;
    TiXmlElement* root;
    string varsPath = "database/vars.xml";

    if (!doc.LoadFile(varsPath.c_str())) {
        cerr << doc.ErrorDesc() << " " << varsPath << endl;
        return "";
    }

    root = doc.FirstChildElement();

    if (root == NULL) {
        cerr << "Failed to load file: No root element. " << varsPath << endl;
        doc.Clear();
        return "";
    }

    TiXmlElement* elem = root->FirstChildElement();

    for(TiXmlElement* e = elem; e; e = e->NextSiblingElement()) {
        if (e->Attribute("name") == get->name()) {
            return e->FirstChild()->ToText()->Value();
        }
    }

    return "";
}

string parse_set(CategoryList* cl, Set* set, string value, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    TiXmlDocument doc;
    TiXmlElement* root;
    string varsPath = "database/vars.xml";

    //cout << "parse_set() : " << value << endl;

    if (!doc.LoadFile(varsPath.c_str())) {
        cerr << doc.ErrorDesc() << " " << varsPath << endl;
        return "";
    }

    root = doc.FirstChildElement();

    if (root == NULL) {
        cerr << "Failed to load file: No root element. " << varsPath << endl;
        doc.Clear();
        return "";
    }

    TiXmlDocument doc2;
    TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "UTF-8", "");
    TiXmlElement * element = new TiXmlElement("vars");

    TiXmlElement * e = new TiXmlElement("var");
    e->SetAttribute("name", set->name().c_str());
    e->LinkEndChild(new TiXmlText(value.c_str()));

    element->LinkEndChild(e);
    doc2.LinkEndChild(decl);
    doc2.LinkEndChild(element);

    for(TiXmlElement* txe = root->FirstChildElement(); txe; txe = txe->NextSiblingElement()) {
        TiXmlElement* txe2 = new TiXmlElement(txe->Value());

        txe2->SetAttribute("name", txe->Attribute("name"));
        string text = txe->GetText();
        txe2->LinkEndChild(new TiXmlText(text.c_str()));

        element->LinkEndChild(txe2);
    }

    doc2.SaveFile(varsPath.c_str());

    return value;
}

string parse_srai(CategoryList* cl, Srai* srai, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    string response = "";
    unsigned int bestLev = UINT_MAX;
    vector<TemplateElement*> children;
    Template* templ;
    string sTempl;

    children = srai->children();
    templ = new Template(children);

    sTempl = parse_template(cl, pattern, templ, input, prevTemplate, mVars);

    lev_pat_templ lpt = parse_categoryList(cl, sTempl, prevTemplate, mVars);

    response = lpt.templ->toString();

    return response;
}

// DO YOU KNOW WHO * IS
// DO YOU KNOW WHO ALBERT IS
// vsPattern={"DO YOU KNOW WHO", "*", "IS"}
// vsInput={"DO YOU KNOW WHO", "ALBERT", "IS"}
string parse_star(CategoryList* cl, Star* star, Pattern* pattern, string input, string prevTemplate, map<string, string> &mVars) {
    string response = "";
    string sPattern = pattern->toString();
    vector<string> vsPattern;
    vector<string> vsInput;
    unsigned int index = star->index();
    int i = 0;

    //cout << "parse_star() : sPattern=" << sPattern << endl;
    //cout << "parse_star() : input=" << input << endl;
    //cout << "parse_star() : index=" << index << endl;

    split(sPattern, input, vsPattern, vsInput);

    if (vsPattern[0] != vsInput[0]) {
        index--;
    } else if (index > 1) {
        index += 1 + index - 2;
    }

    response = vsInput[index];

    //cout << "parse_star() : response=" << response << endl;

    return response;
}

void createCategoryList(CategoryList* cl, TiXmlElement* root) {
    TiXmlElement* elem = root->FirstChildElement();
    string elemName = elem == NULL ? "" : elem->Value();

    if (elemName == "category") {
        //cout << "elemName == \"category\"" << endl;
        createCategories(cl, elem, "");
    } else if (elemName == "topic") {
        //cout << "elemName == \"topic\"" << endl;
        topic = new Topic();
        createCategories(cl, elem->FirstChildElement(), static_cast<TiXmlElement *>(elem)->Attribute("name"));
    } else if (elemName.empty()) {
        //do nothing
    }
}

void createCategories(CategoryList* cl, TiXmlElement* eCategory, string sTopic) {
    TiXmlNode* nPattern = NULL;

    //cout << "create category" << endl;

    for(TiXmlElement* cat = eCategory; cat; cat = cat->NextSiblingElement()) {
        string elemName = cat->Value();

        if (elemName == "category") {
            //cout << "elemName == \"category\"" << endl;
            nPattern = cat->FirstChild();
            TiXmlNode* nTemplate = nPattern->NextSibling();
            TiXmlNode* nThat = NULL;

            if (string(nTemplate->Value()) == "that") {
                nThat = nTemplate;
                nTemplate = nThat->NextSibling();
            }

            TiXmlNode* n = nPattern->FirstChild();
            TiXmlText* txt = n->ToText();
            if (txt == NULL)
                continue;

            string pattern = txt->Value();

            //cout << "createCategories() : " << pattern << endl;

            Pattern* pat = new Pattern(pattern);
            vector<TemplateElement*> elements;
            Template* templ;
            Category* cat;

            for(TiXmlNode* nTemplElt = nTemplate->FirstChild(); nTemplElt; nTemplElt=nTemplElt->NextSibling()) {
                elements.push_back(createTemplateElement(nTemplElt));
            }

            templ = new Template(elements);
            cat = new Category(pat, templ);

            if (0 == sTopic.empty()) {
                topic->appendChild(cat);
                //cat->setTopic(topic); // done in topic->appendChild(cat)
            }

            cl->append(cat);
        } else if (elemName == "topic") {
            //cout << "elemName == \"topic\"" << endl;
            topic = new Topic();
            createCategories(cl, cat->FirstChildElement(), static_cast<TiXmlElement *>(cat)->Attribute("name"));
        }
    }
}

TemplateElement* createTemplateElement(TiXmlNode* nTemplateElement) {
    TemplateElement* teTemplateElement;

    if (nTemplateElement->ToText() != NULL) {
        //cout << "create Text : " << nTemplateElement->ToText()->Value() << endl;
        teTemplateElement = new Text(nTemplateElement->ToText()->Value());
    } else if (std::string(nTemplateElement->Value()) == "srai") {
        teTemplateElement = createSrai(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "sr") {
        teTemplateElement = createSr(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "star") {
        teTemplateElement = createStar(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "random") {
        teTemplateElement = createRandom(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "that") {
        teTemplateElement = createThat(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "set") {
        teTemplateElement = createSet(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "get") {
        teTemplateElement = createGet(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "bot") {
        teTemplateElement = createBot(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "think") {
        teTemplateElement = createThink(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "condition") {
        teTemplateElement = createCondition(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "li") {
        teTemplateElement = createLi(nTemplateElement);
    } else if (std::string(nTemplateElement->Value()) == "br") {
        teTemplateElement = createBr();
    } else {
        //cout << std::string(nTemplateElement->Value()) << endl;
        teTemplateElement = new Text(std::string(nTemplateElement->Value()));
    }

    //cout << "createTemplateElement() : return " << teTemplateElement << endl;
    return teTemplateElement;
}

Srai* createSrai(TiXmlNode* nSrai) {
    Srai* srai;
    vector<TemplateElement*> children;

    //cout << "createSrai()" << endl;

    for(TiXmlNode* n=nSrai->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    srai = new Srai(children);

    return srai;
}

// <srai><star/></srai>
Sr* createSr(TiXmlNode* nSr) {
    Sr* sr;
    vector<const char*> attributes;

    //cout << "createSr()" << endl;

    sr = new Sr(attributes);

    return sr;
}

Star* createStar(TiXmlNode* nStar) {
    Star* star;
    string sIndex = "1";

    //cout << "createStar()" << endl;

    if (static_cast<TiXmlElement *>(nStar)->Attribute("index")) {
        sIndex = static_cast<TiXmlElement *>(nStar)->Attribute("index");
    }

    star = new Star(stoi(sIndex));

    return star;
}

Random* createRandom(TiXmlNode* nRandom) {
    Random* random;
    vector<TemplateElement*> children;

    //cout << "createRandom()" << endl;

    for(TiXmlNode* n=nRandom->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    random = new Random(children);

    return random;
}

Li* createLi(TiXmlNode* nLi) {
    Li* li;
    vector<TemplateElement*> children;
    const char* name = static_cast<TiXmlElement *>(nLi)->Attribute("name");
    const char* value = static_cast<TiXmlElement *>(nLi)->Attribute("value");

    //cout << "createLi()" << endl;

    for(TiXmlNode* n=nLi->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    li = new Li(name == NULL ? "" : string(name), value == NULL ? "" : string(value), children);

    return li;
}

That* createThat(TiXmlNode* nThat) {
    That* that;
    vector<TemplateElement*> children;

    //cout << "createThat()" << endl;

    for(TiXmlNode* n=nThat->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    that = new That(children);

    return that;
}

Set* createSet(TiXmlNode* nSet) {
    Set* set;
    vector<TemplateElement*> children;

    //cout << "createSet()" << endl;

    for(TiXmlNode* n=nSet->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    set = new Set(static_cast<TiXmlElement *>(nSet)->Attribute("name"), children);

    return set;
}

Get* createGet(TiXmlNode* nGet) {
    Get* get;

    //cout << "createGet()" << endl;

    get = new Get(static_cast<TiXmlElement *>(nGet)->Attribute("name"));

    return get;
}

Bot* createBot(TiXmlNode* nBot) {
    Bot* bot;

    //cout << "createBot()" << endl;

    bot = new Bot(string(static_cast<TiXmlElement *>(nBot)->Attribute("name")));

    return bot;
}

Think* createThink(TiXmlNode* nThink) {
    Think* think;
    vector<TemplateElement*> children;

    //cout << "createThink()" << endl;

    for(TiXmlNode* n=nThink->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    think = new Think(children);

    return think;
}

Condition* createCondition(TiXmlNode* nCond) {
    Condition* cond;
    vector<TemplateElement*> children;
    const char* name = static_cast<TiXmlElement *>(nCond)->Attribute("name");
    const char* value = static_cast<TiXmlElement *>(nCond)->Attribute("value");
    string sName = name == NULL ? "" : string(name);
    string sValue = value == NULL ? "" : string(value);

    //cout << "createCondition()" << endl;

    for(TiXmlNode* n=nCond->FirstChild(); n; n=n->NextSibling()) {
        children.push_back(createTemplateElement(n));
    }

    cond = new Condition(sName, sValue, children);

    //cout << "return cond" << endl;
    return cond;
}

Br* createBr() {
    Br* br;

    br = new Br();

    return br;
}
