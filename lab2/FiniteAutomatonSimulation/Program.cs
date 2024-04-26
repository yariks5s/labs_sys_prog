using System;
using System.Collections.Generic;
using System.IO;
using FiniteAutomatonSimulation;

namespace FiniteAutomatonSimulation
{

public class MockDataAccess : IDataAccess
{
    private Dictionary<char, List<Tuple<char, char>>> _transitions;

    public MockDataAccess(Dictionary<char, List<Tuple<char, char>>> transitions)
    {
        _transitions = transitions;
    }

    public Dictionary<char, List<Tuple<char, char>>> LoadTransitions()
    {
        return _transitions;
    }
}

public class FileDataAccess : IDataAccess
{
    private string _filePath;

    public FileDataAccess(string filePath)
    {
        _filePath = filePath;
    }

    public Dictionary<char, List<Tuple<char, char>>> LoadTransitions()
    {
        // Завантажте дані з файлу та поверніть їх як словарь
        // Сюди можна додати логіку зчитування файлу
        return new Dictionary<char, List<Tuple<char, char>>>();
    }
}


class Program
{
    static void Main(string[] args)
    {
        var utilities = new Utilities();
        IDataAccess dataAccess = new MockDataAccess(new Dictionary<char, List<Tuple<char, char>>>
        {
            { 'a', new List<Tuple<char, char>> { Tuple.Create('1', '2') } },
            { 'b', new List<Tuple<char, char>> { Tuple.Create('2', '1') } }
        });

        FiniteAutomaton automaton = new FiniteAutomaton(utilities, dataAccess);

        List<bool> results = new List<bool>();
        automaton.Accepts('1', "ab", results);
        utilities.CheckResult(results);
        automaton.Accepts('1', "ba", results);
        utilities.CheckResult(results);
        automaton.Accepts('1', "a", results);
        utilities.CheckResult(results);
    }
}

}
