#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace jsonc {

vector<char> json;
int pos;

char peek() {
    return json[pos+1];
}

char curt() {
    return json[pos];
}

void go_next() {
    pos++;
}

bool is_eof() {
    return pos >= json.size();
}

void lex(string text) {
    vector<char> v(text.begin(), text.end());
    json = v;

    while ( !is_eof() ) {
        cout << curt() << endl;
        go_next();
    }
}


} // jsonc