#include "lexer.cpp"

bool str_assert(string expected, string actual) {
    return expected == actual;
}

struct test_case
{
    string name;
    string input;
    vector<string> expected;

    void lex() {
        cout << "<" << name << ">" << endl;
        cout << "case: " << name << endl;
        cout << "input: `" << input << "`" << endl;
        
        auto tokens = jsonc::lex(input);
        int c = 0;
        for (auto token: tokens) {
            bool ok = str_assert(expected[c], token.to_string());
            if (!ok) {
                cout << "[FAIL] expected: " << expected[c] << ", but actual: " << token.to_string() << endl;
                exit(1);
            } else {
                cout << "[OK] " << expected[c] << " = " << token.to_string() << endl;
            }
            c++;
        }
        cout << endl;
    }
};


namespace test_lexer {
    void empty_cub() {
        test_case case_ = {
            "empty_cub",
            "{}",
            {
                "{0:1 TLCUB `{`}",
                "{1:2 TRCUB `}`}",
            },
        };
        case_.lex();
    }

    void only_white() {
        test_case case_ = {
            "only_white",
            " ",
            {
                "{0:1 TWHITE ` `}",
            }
        };
        case_.lex();
    }
}


int main(int argc, char *argv[]) {
    test_lexer::empty_cub();
    test_lexer::only_white();

    return 0;
}