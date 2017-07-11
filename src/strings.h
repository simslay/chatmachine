#ifndef __STRING_H__
#define __STRING_H__

#include <vector>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

typedef struct {
    string input;
    string sub;
} subsitution_t;

typedef vector<string> vecstr;

void replace(std::string &s, const std::string toReplace, const std::string replaceWith);
void insert_spaces(string &str);
void toUpper(string &str);
void shrink(string &str);
void subsitute(string &input, vector<subsitution_t> subs);
bool isPunc(char c);
void transfer(char const *array[], vecstr &vs, int size);
vecstr split(string str);
int Split(vecstr& vecteur, string chaine, char separateur);
unsigned int edit_distance(const string& s1, const string& s2);
string trim(const string& str);
// supposition : dest size is greater or equal to desPos + length
void arraycopy(vector<string> src, int srcPos, vector<string> &dest, int destPos, int length);
// In MinGW std::to_string() does not exist
string to_string(int i);

#endif
