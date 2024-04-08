using System;
using System.Collections.Generic;
using System.IO;
using FiniteAutomatonSimulation;

class Program
{
    static void Main(string[] args)
    {
        // Приклад вхідних даних, які потрібно буде адаптувати під ваш випадок
        List<char> alphabet = new List<char> { 'a', 'b' };
        List<char> states = new List<char> { '1', '2' };
        var transitions = new Dictionary<char, List<Tuple<char, char>>>
        {
            { 'a', new List<Tuple<char, char>> { Tuple.Create('1', '2') } },
            { 'b', new List<Tuple<char, char>> { Tuple.Create('2', '1') } }
        };
        char startState = '1';
        List<char> finalStates = new List<char> { '2' };

        // Створення автомата
        FiniteAutomaton automaton = new FiniteAutomaton(alphabet, states, transitions, startState, finalStates);
        List<bool> results = new List<bool>();

        // Перевірка слів
        automaton.Accepts(startState, "ab", results);
        Utilities.CheckResult(results);

        automaton.Accepts(startState, "ba", results);
        Utilities.CheckResult(results);
        automaton.Accepts(startState, "a", results);
        Utilities.CheckResult(results);
    }
}
