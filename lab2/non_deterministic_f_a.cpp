#include <cstddef>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

vector<char> specificElement(const std::vector<std::tuple<char, char>>& endStates, char target)
{
    vector<char> result;
    for (const auto& myTuple : endStates) {
        if (std::get<0>(myTuple) == target) {
            result.push_back(std::get<1>(myTuple));  // Found the specific element as the first element
        }
    }
    return result;  // Specific element not found as the first element in any tuple
}

class FiniteAutomation
{
public:
    FiniteAutomation(vector<char> alphabet_,
                vector<char> states_,
                unordered_map<char, vector<tuple<char, char>>> transitions_,
                char start_state_,
                vector<char> final_states_)
    {
        alphabet = alphabet_;
        states = states_;
        transitions = transitions_;
        start_state = start_state_;
        final_states = final_states_;
    }
    
    void accepts_(char firstState, string word, vector<bool> &results)
    {
        char thisOp = word[0];
        vector<char> endStates = specificElement(transitions[thisOp], firstState);
        if (word.length() == 1)
        {
            checkAcceptance(endStates, results);
            return;
        }
        word = word.substr(1, word.length() - 1);
        if (!endStates.empty())
        {
            for (auto& state : endStates)
                accepts_(state, word, results);
        }
    }

    void checkAcceptance(vector<char> endStates, vector<bool> &results)
    {
        for (auto state : endStates)
        {
            for (auto fin_states : final_states)
            {
                if (state == fin_states)
                    results.push_back(true);
                else
                    results.push_back(0);
            }
        }
    }

private:
    vector<char> alphabet;
    vector<char> states;
    unordered_map<char, vector<tuple<char, char>>> transitions;
    char start_state;
    vector<char> final_states;
};

char translateToChar(int number) {
    // Assuming the input is between 1 and 26
    if (number >= 1 && number <= 26) {
        return static_cast<char>('a' + number - 1);
    } else {
        // Handle out-of-range case
        return '?';
    }
}

int charToInt(char digitChar) {
    return digitChar - '0';
}

void checkResult(vector<bool> &results)
{
    if (results.empty())
    {
        std::cout << "This string is not accessible." << std::endl;
        results.clear();
        return;
    }
    for (bool res : results)
        if (res)
        {
            std::cout << "This string is accessible." << std::endl;
            results.clear();
            return;
        }
    results.clear();
    std::cout << "This string is not accessible." << std::endl;
}

int main()
{
    vector<bool> results;
    ifstream myfile("task.txt");
    if (!myfile.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Declare a string variable to store the current line.
    string line;

    // Read the current line from the file.
    int i = 0;
    vector<char> alphabet;
    vector<char> states;
    unordered_map<char, vector<tuple<char, char>>> transitions;
    char start_state;
    vector<char> final_states;
    while (getline(myfile, line))
    {
        if (i == 3)
        {
            std::istringstream iss(line);
            char number;
            iss >> number;
            while (iss >> number)
                final_states.push_back(number);
        }
        if (i >= 4)
        {
            std::istringstream iss(line);
            char elem, state1, state2;
            iss >> state1;
            iss >> elem;
            iss >> state2;
            transitions[elem].push_back(make_tuple(state1, state2));
        }
        for (auto elem : line)
        {
            if (elem != ' ')
            {
                if (i == 0)
                {
                    for (int i = 1; i <= charToInt(elem); ++i)
                        alphabet.push_back(translateToChar(i));
                }
                if (i == 1)
                {
                    for (int i = 1; i <= charToInt(elem); ++i)
                        states.push_back(i);
                }
                if (i == 2)
                    start_state = elem;
            }
        }
        i++;
    }

    FiniteAutomation automaton(alphabet, states, transitions, start_state, final_states);

    automaton.accepts_(start_state, "ab", results);
    checkResult(results);
    automaton.accepts_(start_state, "cc", results);
    checkResult(results);

    return 0;
}
