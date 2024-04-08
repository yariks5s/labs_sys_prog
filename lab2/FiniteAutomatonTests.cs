using NUnit.Framework;
using FiniteAutomatonSimulation;
using System.Collections.Generic;

namespace FiniteAutomatonTests
{
    [TestFixture]
    public class FiniteAutomatonTests
    {
        private FiniteAutomaton automaton;

        [SetUp]
        public void Setup()
        {
            // Створюємо автомат для тестування
            List<char> alphabet = new List<char> { 'a', 'b' };
            List<char> states = new List<char> { '1', '2' };
            var transitions = new Dictionary<char, List<System.Tuple<char, char>>>
            {
                { 'a', new List<System.Tuple<char, char>> { System.Tuple.Create('1', '2') } },
                { 'b', new List<System.Tuple<char, char>> { System.Tuple.Create('2', '1') } }
            };
            char startState = '1';
            List<char> finalStates = new List<char> { '2' };

            automaton = new FiniteAutomaton(alphabet, states, transitions, startState, finalStates);
        }

        [Test]
        public void Accepts_ValidString_ReturnsTrue()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "ab", results);

            // Перевіряємо, що серед результатів є хоча б один true
            Assert.Contains(true, results);
        }

        [Test]
        public void Accepts_InvalidString_ReturnsFalse()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "abc", results);

            // Перевіряємо, що серед результатів немає true
            Assert.IsFalse(results.Contains(true));
        }
    }
}
