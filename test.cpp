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
        if (tokens.size() != expected.size()) {
            cout << "vector size is not matched" << endl;
            cout << "tokens.size() => " << tokens.size() << endl;
            cout << "expected.size() => " << expected.size() << endl;
            exit(1);
        }

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

    void kv_str1() {
        // {      (1)  0 <= x < 1
        // "key"  (5)  1 <= x < 6
        // :      (1)  6 <= x < 7
        // "value"(7)  7 <= x < 14
        // }      (1) 14 <= x < 15
        test_case case_ = {
            "kv_str1",
            R"({"key":"value"})",
            {
                "{0:1 TLCUB `{`}",
                "{1:6 TSTRING `key`}",
                "{6:7 TCOLON `:`}",
                "{7:14 TSTRING `value`}",
                "{14:15 TRCUB `}`}",
            }
        };
        case_.lex();
    }
}


int main(int argc, char *argv[]) {
    test_lexer::empty_cub();
    test_lexer::only_white();
    test_lexer::kv_str1();

    return 0;
}