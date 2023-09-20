#include <cstddef>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

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

    char acceptsImpl(char firstState, const string word, size_t pos)
    {
        pos ++;
        bool ok = false;
        for(auto states : transitions[word[pos]])
        {
            if (pos == word.length() - 1)
            {
                for (char elem : final_states)
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
        char state = start_state;
        return acceptsImpl(state, input, 0);
    }

private:
    vector<char> alphabet;
    vector<char> states;
    unordered_map<char, vector<tuple<char, char>>> transitions;
    char start_state;
    vector<char> final_states;
};

int main()
{
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
        for (auto elem : line)
        {
            if (elem != ' ')
            {
                if (i == 0)
                    alphabet.push_back(elem);
                if (i == 1)
                    states.push_back(elem);
                if (i == 2)
                {
                    for (int j = 4; j < line.size(); j=j+4)
                        transitions[line[0]].push_back(make_tuple(line[j-2], line[j]));
                    break;
                }
                if (i == 3)
                    start_state = elem;
                if (i == 4)
                    final_states.push_back(elem);
            }
        }
        if (i != 2 || line.empty())
            i++;
    }

    FiniteAutomation automaton(alphabet, states, transitions, start_state, final_states);

    cout << automaton.accepts("ab") << endl; // true
    cout << automaton.accepts("abb") << endl; // false

    return 0;
}
