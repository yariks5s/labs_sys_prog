#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    char* alphabet;
    int* states;
    int start_state;
    int* final_states;
    int num_states;
    int num_alphabet_symbols;
    // A hash table mapping (state, alphabet symbol) to next state.
    int** transitions_table;
} FiniteAutomation;

FiniteAutomation* FiniteAutomation_create(char* alphabet, int num_alphabet_symbols, int* states, int num_states, int** transitions, int start_state, int* final_states, int num_final_states) {
    FiniteAutomation* automaton = malloc(sizeof(FiniteAutomation));
    automaton->alphabet = alphabet;
    automaton->states = states;
    automaton->start_state = start_state;
    automaton->final_states = final_states;
    automaton->num_states = num_states;
    automaton->num_alphabet_symbols = num_alphabet_symbols;

    // Create the transitions hash table.
    automaton->transitions_table = malloc(num_states * sizeof(int*));
    for (int i = 0; i < num_states; i++) {
        automaton->transitions_table[i] = malloc(num_alphabet_symbols * sizeof(int));
        for (int j = 0; j < num_alphabet_symbols; j++) {
            automaton->transitions_table[i][j] = -1;
        }
    }

    // Fill in the transitions hash table.
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_alphabet_symbols; j++) {
            if (transitions[i][j] != -1) {
                automaton->transitions_table[i][j] = transitions[i][j];
            }
        }
    }

    return automaton;
}

void FiniteAutomation_free(FiniteAutomation* automaton) {
    free(automaton->alphabet);
    free(automaton->states);
    for (int i = 0; i < automaton->num_states; i++) {
        free(automaton->transitions_table[i]);
    }
    free(automaton->transitions_table);
    free(automaton->final_states);
    free(automaton);
}

bool FiniteAutomation_accepts(FiniteAutomation* automaton, char* word) {
    int state = automaton->start_state;
    int i = 0;
    while (i < strlen(word)) {
        int next_state = automaton->transitions_table[state][word[i] - 'a'];
        if (next_state == -1) {
            return false;
        }
        state = next_state;
        i++;
    }

    for (int j = 0; j < automaton->num_states; j++) {
        if (state == automaton->final_states[j]) {
            return true;
        }
    }

    return false;
}

int main() {
    char* alphabet = "ab";
    int states[] = {0, 1};
    int transitions[][2] = {{1, 0}, {0, 1}};
    int start_state = 0;
    int final_states[] = {0};

    FiniteAutomation* automaton = FiniteAutomation_create(alphabet, 2, states, 2, transitions, start_state, final_states, 1);

    printf("%d\n", FiniteAutomation_accepts(automaton, "aa")); // true
    printf("%d\n", FiniteAutomation_accepts(automaton, "aba")); // false

    FiniteAutomation_free(automaton);

    return 0;
}
