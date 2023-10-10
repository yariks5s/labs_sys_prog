#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class FiniteAutomation
{
public:
    FiniteAutomation(vector<string> alphabet_,
                vector<string> states_,
                unordered_map<string, vector<tuple<string, string>>> transitions_,
                string start_state_,
                vector<string> final_states_)
    {
        alphabet = alphabet_;
        states = states_;
        transitions = transitions_;
        start_state = start_state_;
        final_states = final_states_;
    }

    bool acceptsImpl(string firstState, const string word, size_t pos)
    {
        pos ++;
        bool ok = false;
        for(auto states : transitions[word.substr(pos, 1)])
        {
            if (pos == word.length() - 1)
            {
                for (string elem : final_states)
                {
                    if (elem == get<1>(states))
                        return true;
                }
            }
            ok = acceptsImpl(get<1>(states), word, pos);
        }
        if (ok)
            return true;
        return false;
    }


    bool accepts(const string& input)
    {
        string state = start_state;
        return acceptsImpl(state, input, 0);
    }

private:
    vector<string> alphabet;
    vector<string> states;
    unordered_map<string, vector<tuple<string, string>>> transitions;
    string start_state;
    vector<string> final_states;
};

vector<string> preprocessor_directives = {
    "#include", "#define", "#undef", "#if",
    "#ifdef", "#ifndef", "#else", "#elif",
    "#endif", "#line", "#error", "#pragma"
};

vector<string> comments = {"//"};

vector<string> operators = {"+", "-", "/", "*", "&&", "||", "%"};

vector<string> p_signs = {";", ":", ","};

vector<string> reserved_words = {
                                "auto", "else", "long", "switch",
                                "break", "enum", "register", "typedef",
                                "case",	"extern", "return",	"union",
                                "char",	"float", "short", "unsigned",
                                "const", "for", "signed", "void",
                                "continue",	"goto",	"sizeof", "volatile",
                                "default", "if", "static", "while",
                                "do", "int", "struct", "_Packed",
                                "double"
                                };

vector<string> states = {
    "number", "constant", "preprocessor directives", "comments",
    "reserved_words", "operators", "punctuations signs",
    "identifiers"
};

int main()
{

    return 0;
}