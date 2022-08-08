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
    // cout << pos << "/" << json.size() << endl;
    if (is_eof()) {
        cout << "out-of-bounds access: " << pos << "/" << json.size() << endl;
        exit(1);
    }
    return json[pos];
}

void go_next() {
    pos++;
}

bool is_eof() {
    return pos >= json.size();
}

bool is_ws() {
    // todo
    // ""
    // 0020
    // 000A
    // 000D
    // 0009
    return curt() == ' ' || curt() == '\n';
}

void t_json() {
    t_element();
}

void t_value() {
    if ( curt() == '{' ) {
        t_object();
    } else if ( curt() == '[' ) {
        t_array();
    } else if ( curt() == '"' ) {
        t_string();
    } else if (curt() == '-' ||
            curt() == '0' || curt() == '1' || 
            curt() == '2' || curt() == '3' ||
            curt() == '4' || curt() == '5' ||
            curt() == '6' || curt() == '7' ||
            curt() == '8' || curt() == '9') {
        t_number();
    } else if ( curt() == 't' || curt() == 'f' || curt() == 'n') {
        t_keyword();
    } else {
        cout << "unexpected: " << pos << "/" << json.size() << ": `" << string({curt()}) << "`" << endl;
        exit(1);
    }
}

void t_object() {
    assert( curt() == '{' );
    jsonc::Token lcub = { .s_pos = pos, .e_pos=pos+1, .kind=TLCUB, .data="{" };
    tokens.push_back(lcub);
    go_next();

    // ws or members
    // if ( is_ws() ) {
        // t_ws();
    // } else {
        // t_members();
    // }
    t_ws();
    if ( curt() == '}' ) {
        // empty
    } else {
        t_members();
    }

    assert( curt() == '}');
    jsonc::Token rcub = { .s_pos=pos, .e_pos=pos+1, .kind=TRCUB, .data="}"};
    tokens.push_back(rcub);
    go_next();
}

void t_members() {
    t_member();
    
    if ( curt() == ',' ) {
        jsonc::Token comma = { .s_pos=pos, .e_pos=pos+1, .kind=TCOMMMA, .data="." };
        tokens.push_back(comma);
        go_next();

        t_members();
    }
}

void t_member() {
    t_ws();
    t_string();
    t_ws();

    jsonc::Token colon = { .s_pos=pos, .e_pos=pos+1, .kind=TCOLON, .data=":" };
    tokens.push_back(colon);
    go_next();

    t_element();
}

void t_array() {
    assert( curt() == '[' );
    jsonc::Token lsqb = { .s_pos=pos, .e_pos=pos+1, .kind=TLSQB, .data="[" };
    tokens.push_back(lsqb);
    go_next();

    if ( is_ws() ) {
        t_ws();
    } else {
        t_elements();
    }

    assert( curt() == ']' );
    jsonc::Token rsqb = { .s_pos=pos, .e_pos=pos+1, .kind=TRSQB, .data="]" };
    tokens.push_back(rsqb);
    go_next();
}

void t_elements() {
    t_element();

    if ( curt() == ',' ) {
        jsonc::Token comma = { .s_pos=pos, .e_pos=pos+1, .kind=TCOMMMA, .data="." };
        tokens.push_back(comma);
        go_next();

        t_elements();
    }
}

void t_element() {
    t_ws();
    if (is_eof()) {
        // only white
        return;
    }
    t_value();
    t_ws();
}

void t_string() {
    string data = "";
    jsonc::Token str = { .s_pos=pos, .kind=TSTRING };
    assert( curt() == '"' );
    go_next();

    // todo escape
    while (!is_eof()) {
        if ( curt() != '"' ) {
            data += string({curt()});
            go_next();
        } else {
            break;   
        }
    }

    assert( curt() == '"' );
    go_next();

    str.data = data;
    str.e_pos= pos;
    tokens.push_back(str);
}

// todo
void t_characters() {}

// todo
void t_character() {}

// todo
void t_escape() {}

// todo
void t_hex() {}

void  t_number() {
    string data = "";
    jsonc::Token num = { .s_pos=pos, .kind=TNUMBER };
    while ( !is_eof() )
    {
        if (curt() == '-' || curt() == '.' ||
            curt() == '0' || curt() == '1' || 
            curt() == '2' || curt() == '3' ||
            curt() == '4' || curt() == '5' ||
            curt() == '6' || curt() == '7' ||
            curt() == '8' || curt() == '9') {
                data += string({curt()});
                go_next();
            } else {
                break;
            }
    }

    num.data = data;
    num.e_pos= pos;
    tokens.push_back(num);
}

// todo
void t_integer() {}

// todo
void t_digits() {}

// todo
void t_digit() {}

// todo
void t_onenine() {}

// todo
void t_fraction() {}

// todo
void t_exponent() {}

// todo
void t_sign() {}

void t_ws() {
    string data = "";
    jsonc::Token ws = { .s_pos=pos, .kind=TWHITE };

    while ( !is_eof() ) {
        if ( is_ws() ) {
            data += string({curt()});
            go_next();
        } else {
            break;
        }
    }

    // [FAIL] expected: {0:1 TLCUB `{`}, but actual: {0:0 TWHITE ``}
    if ( data == "" ) {
        return;
    }

    ws.data = data;
    ws.e_pos=pos;
    tokens.push_back(ws);
}

void t_keyword() {
    string data = "";
    jsonc::Token keyword = { .s_pos=pos };

    if ( curt() == 't' ) {
        assert( curt() == 't' );
        go_next();
        assert( curt() == 'r' );
        go_next();
        assert( curt() == 'u' );
        go_next();
        assert( curt() == 'e' );
        go_next();
        keyword.data = "true";
        keyword.kind = TTRUE;
        keyword.e_pos = pos;
    } else if ( curt() == 'f' ) {
        assert( curt() == 'f' );
        go_next();
        assert( curt() == 'a' );
        go_next();
        assert( curt() == 'l' );
        go_next();
        assert( curt() == 's' );
        go_next();
        assert( curt() == 'e' );
        go_next();
        keyword.data = "false";
        keyword.kind = TFALSE;
        keyword.e_pos = pos;
    } else if ( curt() == 'n' ) {
        assert( curt() == 'n' );
        go_next();
        assert( curt() == 'u' );
        go_next();
        assert( curt() == 'l' );
        go_next();
        assert( curt() == 'l' );
        go_next();
        keyword.data = "null";
        keyword.kind = TNULL;
        keyword.e_pos = pos;
    }

    tokens.push_back(keyword);
}

vector<jsonc::Token> lex(string text) {
    json = {};
    pos = 0;
    tokens = {};

    vector<char> v(text.begin(), text.end());
    json = v;
    t_json();
    return tokens;
}

} // namespace jsonc