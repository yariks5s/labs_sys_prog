#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

/// Here we define colours that will be used for painting words
#define BLACK "\033[30m" 
#define RED "\033[31m" //
#define GREEN "\033[32m" // comments
#define YELLOW "\033[33m" // operators
#define BLUE "\033[34m" // reserved words
#define MAGENTA "\033[35m" // names
#define CYAN "\033[36m" // preprocessor directives
#define RESET "\033[0m" // white colour, for punctuation

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

vector<string> operators = {"+", "-", "/", "*", "&&", "||", "%", "=", "==", "!="};

vector<string> p_signs = {";", ":", ",", "(", ")", "{", "}", "[", "]"};

vector<string> delimiters = {"//", "+", "-", "/", "*", "&&", "||", "%", "=", "==", "!=", ";", ":", ",", "(", ")", "{", "}", "[", "]", "endpos"};
vector<char> delimiters_char = {'(', ')'};


vector<string> reserved_words = {
                                "auto", "else", "long", "switch",
                                "break", "enum", "register", "typedef",
                                "case",	"extern", "return",	"union",
                                "char",	"float", "short", "unsigned",
                                "const", "for", "signed", "void",
                                "continue",	"goto",	"sizeof", "volatile",
                                "default", "if", "static", "while",
                                "do", "int", "struct", "_Packed",
                                "double", "printf", "scanf"
                                };

vector<string> states = {
    "number", "constant", "preprocessor directives", "comments",
    "reserved_words", "operators", "punctuations signs",
    "identifiers"
};

bool is_inside(const vector<string> list, const string word)
{
    auto it = std::find(list.begin(), list.end(), word);
    return it != list.end();
}

void print_with_colour(string &previous_state, string word, string space)
{
    if (is_inside(reserved_words, word))
        std::cout << BLUE << word << space;
    else if (previous_state == "RESET")
    {
        if (is_inside(preprocessor_directives, word))
        {
            std::cout << CYAN << word << space;
            previous_state = "preprocessor_directives";
        }
        else if (is_inside(reserved_words, word))
        {
            std::cout << BLUE << word << space;
            previous_state = "reserved_words";
        }
        else if (is_inside(operators, word))
        {
            std::cout << YELLOW << word << space;
            previous_state = "operators";
        }
        else if (is_inside(comments, word))
        {
            std::cout << GREEN << word << space;
            previous_state = "comments";
        }
        else if (is_inside(p_signs, word))
        {
            std::cout << RESET << word << space;
            previous_state = "p_signs";
        }
        else
        {
            std::cout << MAGENTA << word << space;
            previous_state = "else";
        }
    }
    else if (previous_state == "comments")
        std::cout << GREEN << word << space;
    else if (is_inside(p_signs, word))
    {
        std::cout << RESET << word << space;
        previous_state = "p_signs";
    }
    else if (is_inside(operators, word))
    {
        std::cout << YELLOW << word << space;
        previous_state = "operators";
    }
    else
    {
        std::cout << MAGENTA << word << space;
        previous_state = "else";
    }
}

void check_delimiter(string &previous_state, string word)
{
    int pos = -1;
    bool is_done = false;
    for (char c : word)
    {
        pos++;
        if (std::find(delimiters_char.begin(),delimiters_char.end(), c) != delimiters_char.end())
        {
            print_with_colour(previous_state, word.substr(0, pos), "");
            std::cout << RESET << word[pos];
            if (pos < word.length()-1)
                check_delimiter(previous_state, word.substr(pos+1, word.length()));
            is_done = true;
            break;
        }
    }
    if (!is_done)
    {
        print_with_colour(previous_state, word, " ");
    }
    // for (string symb : delimiters)
    // {
    //     std::istringstream iss(word);

    //     // Vector to store individual elements
    //     std::vector<std::string> elements;

    //     // Tokenize the string and store elements in the vector
    //     std::string token;
    //     while (std::getline(iss, token, ' '))
    //     {
    //         elements.push_back(token);
    //     }
    //     {
    //         print_with_colour(previous_state, word, " ");
    //         break;
    //     }
    // }
}

int main()
{
    // Open the C++ file for reading
    std::ifstream inputFile("example.c");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1; // Exit with an error code
    }

    // Read the file content line by line
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Tokenize the line into words
        std::istringstream iss(line);
        std::unordered_map<std::string, std::string> words;

        std::string word;
        std::string previous_state = "RESET";

        while (iss >> word) {
            check_delimiter(previous_state, word);
        }
        std::cout << std::endl;

    }

    // Close the file
    inputFile.close();

    std::cout << RED << "★" << RESET << " Red" << std::endl;
    std::cout << GREEN << "★" << RESET << " Green" << std::endl;
    std::cout << YELLOW << "★" << RESET << " Yellow" << std::endl;
    std::cout << BLUE << "★" << RESET << " Blue" << std::endl;

    return 0; // Exit successfully
}