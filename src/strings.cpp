#include "strings.h"
#include "locale"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

void subsitute(string &input, vector<subsitution_t> subs) {
	for(int i=0, s=subs.size(); i<s; ++i) {
		replace(input, subs[i].input, subs[i].sub);
	}
}

void replace(std::string &s, const std::string toReplace, const std::string replaceWith) {
    regex re(toReplace);

    s = regex_replace(s, re, replaceWith);
}

void insert_spaces(std::string &str) {
	str.insert(str.begin(), ' ');
    str.insert(str.end(), ' ');
}

void toUpper(std::string &str)
{
	std::locale settings;
	std::string toUpper;

	for(unsigned int i = 0; i < str.size(); ++i)
		toUpper += (std::toupper(str[i], settings));

	str = toUpper;
}

// removes multi spaces and punctuations
void shrink(std::string &str) {
	std::string srk = "";
	char prevChar = ' ';

	for(int i=0, l=str.length(); i < l; ++i) {
	    if (str[i] == ' ' && prevChar == ' ')
	        continue;
	    else if (isPunc(str[i]) && !isPunc(prevChar))
	        srk += ' ';
	    else if (isPunc(str[i]) && isPunc(prevChar)) {
	        prevChar = str[i];
	        continue;
	    } else
    	    srk += str[i];

    	prevChar = str[i];
	}

	str = srk;
	srk = "";

	for(int i=0, l=str.length(); i < l; ++i) {
	    if (str[i] == ' ' && prevChar == ' ')
	        continue;
	    else if (i < l-1 || str[i] != ' ') {
    	    srk += str[i];
	    }

    	prevChar = str[i];
	}

	str = srk;
}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// split str with ' '
vector<string> split(std::string str) {
    vector<string> vs;

    Split(vs, str, ' ');

    return vs;
}

int Split(vector<string>& v, string str, char sep) {
	v.clear();

	string::size_type stTemp = str.find(sep);

	//cout << "Split() : str=" << str << endl;

	while(stTemp != string::npos)
	{
		v.push_back(str.substr(0, stTemp));
		str = str.substr(stTemp + 1);
		stTemp = str.find(sep);
	}

	v.push_back(str);

	return v.size();
}

bool isPunc(char c) {
    std::string puncs = "?!,;.";

    return puncs.find(c) != std::string::npos;
}

void transfer(char const *array[], vecstr &vs, int size) {
    for (int i=0; i<size; ++i) {
        if (array[i] == NULL) {
			break;
		} else
			vs.push_back(array[i]);
    }
}

// wikibooks.org
// Levenshtein distance
unsigned int edit_distance(const std::string& s1, const std::string& s2)
{
	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int> > d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j)
                      // note that std::min({arg1, arg2, arg3}) works only in C++11,
                      // for C++98 use std::min(std::min(arg1, arg2), arg3)
                      d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
	return d[len1][len2];
}

void arraycopy(vector<string> src, int srcPos, vector<string> &dest, int destPos, int length) {
	for(int i=destPos, j=srcPos; i<destPos+length; ++i, ++j) {
		dest[i] = src[j];
	}
}

// In MinGW std::to_string() does not exist
//string to_string(int i) {
//    stringstream ss;
//    ss << i;
//    return ss.str();
//}
