#include "lexer.hpp"
#include <iostream>

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
};

char curt() {
    return json[pos];
}

void go_next() {
    pos++;
}

bool is_eof() {
    return pos >= json.size();
}

void t_json() {}

void t_value() {}

void t_object() {}

void t_members() {}

void t_member() {}

void t_array() {}

void t_elements() {}

void t_element() {}

void t_string() {}

void t_characters() {}

void t_character() {}

void t_escape() {}

void t_hex() {}

void t_number() {}

void t_integer() {}

void t_digits() {}

void t_digit() {}

void t_onenine() {}

void t_fraction() {}

void t_exponent() {}

void t_sign() {}

void t_ws() {}

vector<jsonc::Token> lex(string text) {
    return {};
}

} // namespace jsonc