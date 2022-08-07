#include "lexer.cpp"

void str_assert(string expected, string actual) {
    cout << "expected: " << expected << endl;
    cout << "actual: " << actual << endl;
    assert(expected == actual);
}


namespace test_lexer {
    void empty_cub() {
        cout << "\ntest empty_cub" << endl;
        auto tokens = jsonc::lex("{}");
        vector<string> expected = {
            "{0:1 TLCUB `{`}",
            "{1:2 TRCUB `}`}",
        };

        int c = 0;
        for (auto token: tokens) {
            str_assert(expected[c], token.to_string());
            c++;
        }
    }

    void only_white() {
        cout << "\ntest only_white" << endl;
        auto tokens = jsonc::lex(" ");
        vector<string> expected = {
            "{0:1 TWHITE ` `}",
        };
        int c = 0;
        for (auto token: tokens) {
            str_assert(expected[c], token.to_string());
            c++;
        }
    }
}


int main(int argc, char *argv[]) {
    test_lexer::empty_cub();
    test_lexer::only_white();

    return 0;
}