#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class FiniteAutomaton
{
public:
    FiniteAutomaton(vector<char> alphabet_,
                vector<int> states_,
                unordered_map<char, tuple<int, int>> transitions_,
                int start_state_,
                vector<int> final_states_)
    {
        alphabet = alphabet_;
        states = states_;
        transitions = transitions_;
        start_state = start_state_;
        final_states = final_states_;
    }

  bool accepts(const string& input)
  {
    int state = start_state;
    for (char c : input)
    {
        size_t i = 0;
        bool found = false;
        for (i; i < alphabet.size(); ++i)
        {
            if (alphabet[i] == c) 
            {
                found = true;
                break;
            }
        }
        if (!found)
            throw exception();
        if (state == get<0>(transitions[c])) /// TODO: Implement here for vectors
            state = get<1>(transitions[c]);
        else
            return 0;
    }
    return find(final_states.begin(), final_states.end(), state) != final_states.end();
  }

private:
    vector<char> alphabet;
    vector<int> states;
    unordered_map<char, tuple<int, int>> transitions;
    int start_state;
    vector<int> final_states;
};

int main_finite()
{
    vector<char> alphabet = {'a', 'b'};
    vector<int> states = {0, 1};
    unordered_map<char, tuple<int, int>> transitions = {
        {'a', make_tuple(0, 1)}, {'b', make_tuple(1, 0)},
    };
    int start_state = 0;
    vector<int> final_states = {1};

    FiniteAutomaton automaton(alphabet, states, transitions, start_state, final_states);

    cout << automaton.accepts("ab") << endl; // true
    cout << automaton.accepts("aba") << endl; // false

    return 0;
}
