using System;
using System.Collections.Generic;
using System.Linq;

namespace FiniteAutomatonSimulation
{
    public class FiniteAutomaton
{
    private IUtilities _utilities;
    private IDataAccess _dataAccess;
    public Dictionary<char, List<Tuple<char, char>>> Transitions { get; private set; }

    public FiniteAutomaton(IUtilities utilities, IDataAccess dataAccess)
    {
        _utilities = utilities;
        _dataAccess = dataAccess;
        Transitions = _dataAccess.LoadTransitions();
    }

    public void Accepts(char firstState, string word, List<bool> results, bool first = true)
    {
        if (string.IsNullOrEmpty(word) && first)
            throw new ArgumentException("Input string cannot be empty.", nameof(word));

        if (word.Length == 0)
        {
            // Тут має бути логіка обробки порожнього рядка, а не виключення
            _utilities.CheckResult( results);
            return;
        }

        var thisOp = word[0];
        var remainingWord = word.Substring(1);
        var endStates = _utilities.SpecificElement(Transitions[thisOp], firstState);

        foreach (var state in endStates)
        {
            Accepts(state, remainingWord, results, false);
        }
    }
}


    // public class FiniteAutomaton
    // {
    //     public List<char> Alphabet { get; private set; }
    //     public List<char> States { get; private set; }
    //     public Dictionary<char, List<Tuple<char, char>>> Transitions { get; private set; }
    //     public char StartState { get; private set; }
    //     public List<char> FinalStates { get; private set; }

    //     public FiniteAutomaton(List<char> alphabet, List<char> states, Dictionary<char, List<Tuple<char, char>>> transitions, char startState, List<char> finalStates)
    //     {
    //         Alphabet = alphabet;
    //         States = states;
    //         Transitions = transitions;
    //         StartState = startState;
    //         FinalStates = finalStates;
    //     }

    //     public void Accepts(char firstState, string word, List<bool> results)
    //     {
    //         if (string.IsNullOrEmpty(word) && !IsInitialStateAcceptable(firstState))
    //         {// Initial
    //             throw new ArgumentException("Input string cannot be empty for the given initial state or there is an invalid symbol.", nameof(word));
    //         }

    //         if (word.Length == 0)
    //         {
    //             // Тут має бути логіка обробки порожнього рядка, а не виключення
    //             CheckAcceptance(new List<char> { firstState }, results);
    //             return;
    //         }

    //         var thisOp = word[0];
    //         var remainingWord = word.Substring(1);
    //         if (Transitions.ContainsKey(thisOp))
    //         {
    //             var endStates = Utilities.SpecificElement(Transitions[thisOp], firstState);
    //             foreach (var state in endStates)
    //             {
    //                 Accepts(state, remainingWord, results);
    //             }
    //         }
    //     }

    //     private bool IsInitialStateAcceptable(char state)
    //     {
    //         // Логіка, що визначає, чи є початковий стан таким, що може приймати порожній рядок
    //         return FinalStates.Contains(state);
    //     }

    //     private void CheckAcceptance(List<char> endStates, List<bool> results)
    //     {
    //         bool isAccepted = false;
    //         foreach (var state in endStates) {
    //             if (FinalStates.Contains(state)) {
    //                 isAccepted = true;
    //                 break; // Знаходимо хоча б один кінцевий стан і припиняємо перевірку
    //             }
    //         }
    //         results.Add(isAccepted);
    //     }

    //     // Other methods as necessary
    // }
}
