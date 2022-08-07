#include <iostream>
#include <string>
#include <vector>
#include "token.cpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;

namespace jsonc {

vector<char> json;
int pos;

vector<jsonc::Token> tokens;


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

// 現在のキャラクタが空白、改行である間削除し続けます
void t_white() {
    jsonc::Token token;
    token.kind = TWHITE;
    token.s_pos = pos;
    char c;

    while (!is_eof()) {
        c = curt();
        if( c == ' ' || c == '\n' ) {
            token.data += string({c});
            go_next();
        } else {
            break;
        }
    }

    token.e_pos = pos;
    if (token.data == "") {
        return;
    }

    tokens.push_back(token);
}

void t_object() {
    // cout << "t_object" << endl;

    if (curt() != '{'){
        throw std::invalid_argument( "expected: {, but found: " + string{curt()} ); }
    
    jsonc::Token t_lcub;
    t_lcub.s_pos = pos;
    t_lcub.kind = TLCUB;
    t_lcub.data += string({curt()});
    go_next();
    t_lcub.e_pos = pos;
    tokens.push_back(t_lcub);
    
    t_white();

    if (curt() != '}') {
        // members
    }

    jsonc::Token t_rcub;
    t_rcub.s_pos = pos;
    t_rcub.kind = TRCUB;
    t_rcub.data += string({curt()});
    go_next();
    t_rcub.e_pos = pos;
    tokens.push_back(t_rcub);
}


void t_array() {}
void t_string() {}
void t_number() {}
void t_true() {}
void t_false() {}
void t_null() {}

void t_value() {
    // cout << "t_value" << endl;

    if (curt() == '{') {
        t_object();
    } else if (curt() == '[') {
        t_array();
    } else if (curt() == '"') {
        t_string();
    } else if (curt() == 't') {
        t_true();
    } else if (curt() == 'f') {
        t_false();
    } else if (curt() == 'n') {
        t_null();
    } else if (string("-0123456789").find(curt()) != string::npos) {
        t_number();
    } else {
        string msg = "unexpected char: " + string{curt()};
        throw std::invalid_argument( msg );
    }
}


void t_element() {
    // cout << "t_element" << endl;

    t_white();
    if (is_eof()) {
        return;
    }
    t_value();
     if (is_eof()) {
        return;
    }
    t_white();
}

void t_json() {
    t_element();
}


vector<jsonc::Token> lex(string text) {
    vector<char> v(text.begin(), text.end());
    json = v;
    pos = 0;
    tokens = {};

    // while ( !is_eof() ) {
    //     // cout << curt() << endl;
    //     t_json();
    //     go_next();
    // }

    t_json();

    return tokens;
}


} // namespace jsonc