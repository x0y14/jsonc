#pragma once
#include <vector>
#include <string>
#include "token.cpp"

namespace jsonc {
    char peek();
    char curt();
    void go_next();
    bool is_eof();

    void t_json();
    void t_value();
    void t_object();
    void t_members();
    void t_member();
    void t_array();
    void t_elements();
    void t_element();
    void t_string();
    void t_characters();
    void t_character();
    void t_escape();
    void t_hex();
    void t_number();
    void t_integer();
    void t_digits();
    void t_digit();
    void t_onenine();
    void t_fraction();
    void t_exponent();
    void t_sign();
    void t_ws();

    std::vector<jsonc::Token> lex(std::string);
}