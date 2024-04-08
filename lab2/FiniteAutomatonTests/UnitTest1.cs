using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace FiniteAutomatonSimulation.Tests
{
    [TestFixture]
    public class FiniteAutomatonTests
    {
        private FiniteAutomaton automaton;

        [OneTimeSetUp]
        public void SetupOnce()
        {
            // Виконується один раз перед усіма тестами
        }

        [SetUp]
        public void Setup()
        {
            // Виконується перед кожним тестом
            List<char> alphabet = new List<char> { 'a', 'b' };
            List<char> states = new List<char> { '1', '2' };
            var transitions = new Dictionary<char, List<Tuple<char, char>>>
            {
                { 'a', new List<Tuple<char, char>> { Tuple.Create('1', '2') } },
                { 'b', new List<Tuple<char, char>> { Tuple.Create('2', '1') } }
            };
            char startState = '1';
            List<char> finalStates = new List<char> { '2' };

            automaton = new FiniteAutomaton(alphabet, states, transitions, startState, finalStates);
        }

        [Test]
        public void Accepts_ValidString_ReturnsTrue()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "aba", results);
            Assert.Contains(true, results); // Assert вираз
        }
        [Test]
        public void Accepts_ValidString_ReturnsTrue2()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "a", results);
            Assert.Contains(true, results); // Assert вираз
        }

        [Test]
        public void Accepts_InvalidString_ReturnsFalse()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "abc", results);
            Assert.IsFalse(results.Contains(true)); // Assert вираз
        }

        [Test]
        public void Result_IsNotEmpty()
        {
            var results = new List<bool>();
            automaton.Accepts('1', "a", results);
            Assert.IsNotEmpty(results); // Складний метчер
        }

        [Test]
        public void Accepts_EmptyString_ThrowsException()
        {
            var results = new List<bool>();
            Assert.Throws<ArgumentException>(() => automaton.Accepts('1', "", results)); // Тестує виключення
        }

        [TestCase('1', "a", ExpectedResult = true)]
        [TestCase('1', "abc", ExpectedResult = false)]
        public bool Accepts_ParameterizedTests(char startState, string word)
        {
            var results = new List<bool>();
            automaton.Accepts(startState, word, results);
            return results.Contains(true);
        }

        [Test]
        public void Accepts_MultipleInputs_CorrectResults()
        {
            var results = new List<bool>();
            var tempResults = new List<bool>(); // Тимчасовий список для кожного результату

            automaton.Accepts('1', "a", tempResults);
            results.Add(tempResults.LastOrDefault());
            tempResults.Clear();

            automaton.Accepts('1', "abc", tempResults);
            results.Add(tempResults.LastOrDefault());
            tempResults.Clear();

            automaton.Accepts('1', "aba", tempResults);
            results.Add(tempResults.LastOrDefault());
            tempResults.Clear();

            automaton.Accepts('1', "b", tempResults);
            results.Add(tempResults.LastOrDefault());
            tempResults.Clear();

            var expectedResults = new List<bool> { true, false, true, false };

            try
            {
                CollectionAssert.AreEqual(expectedResults, results);
            }
            catch (AssertionException ex)
            {
                throw new AssertionException(
                    $"{ex.Message} Actual results: [{string.Join(", ", results.Select(r => r.ToString()))}]", ex);
            }
        }
    }
}
