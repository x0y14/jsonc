#include <vector>
#include <string>
#include <stdio.h>

namespace jsonc {

enum TokenKind {
    TILLEGAL,
    TLCUB,     // {
    TRCUB,     // }
    TLSQB,     // [
    TRSQB,     // ]
    TCOLON,    // :
    TCOMMMA,   // ,
    TSTRING,   // "aaa"
    TNUMBER,   // -123, 23
    TTRUE,     // true
    TFALSE,    // false
    TNULL,     // NULL,
    TWHITE,    // " ", "\n"
};

const std::string kind_to_string(TokenKind tk) {
    switch(tk) {
        case TLCUB: return "TLCUB";
        case TRCUB: return "TRCUB";
        case TLSQB: return "TLSQB";
        case TRSQB: return "TRSQB";
        case TCOLON: return "TCOLON";
        case TCOMMMA: return "TCOMMMA";
        case TSTRING: return "TSTRING";
        case TNUMBER: return "TNUMBER";
        case TTRUE: return "TTRUE";
        case TFALSE: return "TFALSE";
        case TNULL: return "TNULL";
        case TWHITE: return "TWHITE";
        default: return "TILLEGAL";
    }
}


struct Token
{
    int s_pos;
    int e_pos;
    TokenKind kind;
    std::string data;

    std::string to_string() {
        std::string str;
        str += "{";
        str += std::to_string(s_pos) + ":" + std::to_string(e_pos);
        str += " ";
        str += kind_to_string(kind);
        str += " ";
        str += "`" + data + "`";
        str += "}";
        return str;
        // {0:0 TKIND DATA}
    }
};

} // namespace jsonc