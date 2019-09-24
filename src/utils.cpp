#include "../headers/utils.h"

vector<string> split_str(const string &txt, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    vector<string> strSet;

    while( pos != string::npos ) {
        strSet.push_back(txt.substr( initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }
    strSet.push_back(txt.substr( initialPos, min(pos, txt.size()) - initialPos + 1));

    return strSet;
}