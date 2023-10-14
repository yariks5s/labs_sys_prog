#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>

/// Here we define colours that will be used for painting words
#define BLACK "\033[30m" 
#define RED "\033[31m" // numbers
#define GREEN "\033[32m" // comments, strings
#define YELLOW "\033[33m" // operators
#define BLUE "\033[34m" // reserved words
#define MAGENTA "\033[35m" // names
#define CYAN "\033[36m" // preprocessor directives
#define RESET "\033[0m" // white colour, for punctuation

using namespace std;

std::regex directivesRegex("#include|#define|#undef|#if|#ifdef|#ifndef|#else|#elif|#endif|#line|#error|#pragma");

std::regex reservedWordRegex("\\b(auto|else|long|switch|"
                                "break|enum|register|typedef|"
                                "case|extern|return|union|"
                                "char|float|short|unsigned|"
                                "const|for|signed|void|"
                                "continue|goto|sizeof|volatile|"
                                "default|if|static|while|"
                                "do|int|struct|_Packed|"
                                "double|printf|scanf)\\b", std::regex_constants::icase);

std::regex numbersRegex("\\b^[0-9]+$\\b", std::regex_constants::icase);

std::regex pSignsRegex(R"(\b(?:;|:|,|\(|\)|\{|\}|\[|\])\b)");

std::regex opRegex("[+\\-*/%=&|]{1,2}|==|!=|&&|\\|\\|");

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

// vector<string> operators = {"+", "-", "/", "*", "&&", "||", "%", "=", "==", "!=", "&"};

// vector<string> p_signs = {";", ":", ",", "(", ")", "{", "}", "[", "]"};

vector<string> delimiters = {"//", "+", "-", "/", "*", "&&", "||", "%", "=", "==", "!=", ";", ":", ",", "(", ")", "{", "}", "[", "]", "endpos"};

vector<char> delimiters_char = {'(', ')', ';', '-', '+', '=', '{', '}', '*', '/', '&', '%', ','};

vector<char> quotes = {'"', '\''};


// vector<string> reserved_words = {
//                                 "auto", "else", "long", "switch",
//                                 "break", "enum", "register", "typedef",
//                                 "case",	"extern", "return",	"union",
//                                 "char",	"float", "short", "unsigned",
//                                 "const", "for", "signed", "void",
//                                 "continue",	"goto",	"sizeof", "volatile",
//                                 "default", "if", "static", "while",
//                                 "do", "int", "struct", "_Packed",
//                                 "double", "printf", "scanf"
//                                 };

vector<string> states = {
    "numbers", "constant", "preprocessor directives", "comments",
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
    if (std::regex_search(word, reservedWordRegex))
        std::cout << BLUE << word << space;
    else if (previous_state == "RESET")
    {
        if (std::regex_search(word, directivesRegex))
        {
            std::cout << CYAN << word << space;
            previous_state = "preprocessor_directives";
        }
        else if (std::regex_search(word, reservedWordRegex))
        {
            std::cout << BLUE << word << space;
            previous_state = "reserved_words";
        }
        else if (std::regex_search(word, numbersRegex))
        {
            std::cout << RED << word << space;
            previous_state = "numbers";
        }
        else if (regex_search(word, opRegex))
        {
            std::cout << YELLOW << word << space;
            previous_state = "operators";
        }
        else if (is_inside(comments, word))
        {
            std::cout << GREEN << word << space;
            previous_state = "comments";
        }
        else if (std::regex_search(word, pSignsRegex))
        {
            std::cout << RESET << word << space;
            previous_state = "RESET";
        }
        else
        {
            std::cout << MAGENTA << word << space;
            previous_state = "else";
        }
    }
    else if (previous_state == "comments")
        std::cout << GREEN << word << space;
    else if (std::regex_search(word, pSignsRegex))
    {
        std::cout << RESET << word << space;
        previous_state = "RESET";
    }
    else if (regex_search(word, opRegex))
    {
        std::cout << YELLOW << word << space;
        previous_state = "operators";
    }
    else if (std::regex_search(word, numbersRegex))
    {
        std::cout << RED << word << space;
        previous_state = "numbers";
    }
    else
    {
        std::cout << MAGENTA << word << space;
        previous_state = "else";
    }
}

void check_delimiter(string &previous_state, string word, bool &isBeginOfStr)
{
    int pos = -1;
    bool is_done = false;
    if (isBeginOfStr)
    {
        for (char c : word)
        {
            pos++;
            if (std::find(quotes.begin(), quotes.end(), c) != quotes.end() && isBeginOfStr)
            {
                isBeginOfStr = false;
                std::cout << GREEN << word[pos];
                check_delimiter(previous_state, word.substr(pos+1, word.length()), isBeginOfStr);
                break;
            }
            std::cout << GREEN << word[pos];
        }
    }
    else
    {
        for (char c : word)
        {
            pos++;
            if (std::find(delimiters_char.begin(), delimiters_char.end(), c) != delimiters_char.end() && !isBeginOfStr)
            {
                print_with_colour(previous_state, word.substr(0, pos), "");
                std::cout << RESET << word[pos];
                if (pos < word.length()-1)
                    check_delimiter(previous_state, word.substr(pos+1, word.length()), isBeginOfStr);
                is_done = true;
                break;
            }
            else if (std::find(quotes.begin(), quotes.end(), c) != quotes.end() && isBeginOfStr)
            {
                isBeginOfStr = false;
                check_delimiter(previous_state, word.substr(pos+1, word.length()), isBeginOfStr);
            } 
            else if (std::find(quotes.begin(), quotes.end(), c) != quotes.end() || isBeginOfStr)
            {
                is_done = true;
                isBeginOfStr = true;
                std::cout << GREEN << word[pos];
                check_delimiter(previous_state, word.substr(pos+1, word.length()), isBeginOfStr);
                break;
            }
        }
        if (!is_done)
        {
            print_with_colour(previous_state, word, "");
        }
    }
}

int countOccurrences(const std::string& str, char target) {
    int count = 0;

    for (char ch : str) {
        if (ch == target) {
            count++;
        }
    }

    return count;
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
    int foundCurlyBraces = 0;
    int foundBraces = 0;
    int foundSquareBraces = 0;
    int foundQuotes = 0;
    int foundSingleQuotes = 0;
    bool isError = false;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.find('{') || line == "{")
            foundCurlyBraces += countOccurrences(line, '{');
        if (line.find('}') || line == "}")
            foundCurlyBraces -= countOccurrences(line, '}');
        if (line.find('(') || line == "(")
            foundBraces += countOccurrences(line, '(');
        if (line.find(')') || line == ")")
            foundBraces -= countOccurrences(line, ')');
        if (line.find('[') || line == "[")
            foundSquareBraces += countOccurrences(line, '[');
        if (line.find(']') || line == "]")
            foundSquareBraces -= countOccurrences(line, ']');
        if (line.find('"') || line == "\"")
            foundQuotes += countOccurrences(line, '"');
        if (line.find('\'') || line == "'")
            foundSingleQuotes += countOccurrences(line, '\'');
    }
    if (!(foundBraces == 0 && foundCurlyBraces == 0 && foundSquareBraces == 0 && foundQuotes % 2 == 0 && foundSingleQuotes % 2 == 0))
    {
        std::ifstream inputFile("example.c");
        while (std::getline(inputFile, line))
        {
            std::cout << RED;
            std::cout << line << std::endl;
            isError = true;
        }
    }
    if (!isError)
    {
        std::ifstream inputFile("example.c");
        while (std::getline(inputFile, line))
        {
            // Tokenize the line into words
            std::istringstream iss(line);
            bool isBeginOfStr = false;
            std::unordered_map<std::string, std::string> words;

            std::string word;
            std::string previous_state = "RESET";
            bool isDone = false;
            for (size_t i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ')
                    std::cout << " ";
                else if (line.substr(i, 2) == "//")
                {
                    std::cout << GREEN << line;
                    isDone = true;
                }
                else
                    break;
            }
            if (!isDone)
            {
                std::string temp_line = line;
                while (iss >> word)
                {
                    size_t found = temp_line.find(word);
                    if (found != std::string::npos && temp_line[found-1] == ' ')
                    {
                        std::cout << " ";
                        temp_line = line.substr(found + word.length(), line.length() - found - word.length());
                    }
                    check_delimiter(previous_state, word, isBeginOfStr);
                }
            }
            std::cout << std::endl;

        }
    }
    // Close the file
    inputFile.close();

    std::cout << RED << "★" << RESET << " Red" << std::endl;
    std::cout << GREEN << "★" << RESET << " Green" << std::endl;
    std::cout << YELLOW << "★" << RESET << " Yellow" << std::endl;
    std::cout << BLUE << "★" << RESET << " Blue" << std::endl;

    return 0; // Exit successfully
}