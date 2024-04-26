using Moq;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;

using FiniteAutomatonSimulation;


namespace FiniteAutomatonTests
{
    [TestFixture]
    public class FiniteAutomatonTests
    {
        private FiniteAutomaton _automaton;
        private Mock<IUtilities> _mockUtilities;
        private Mock<IDataAccess> _mockDataAccess;

        [SetUp]
        public void Setup()
        {
            // Мок ініціалізація
            _mockUtilities = new Mock<IUtilities>();
            _mockDataAccess = new Mock<IDataAccess>();

            _mockDataAccess.Setup(m => m.LoadTransitions()).Returns(new Dictionary<char, List<Tuple<char, char>>>
            {
                {'a', new List<Tuple<char, char>> { Tuple.Create('1', '2') }},
                {'b', new List<Tuple<char, char>> { Tuple.Create('2', '1') }}
            });

            // Створення об'єкту з мок-залежностями
            _automaton = new FiniteAutomaton(_mockUtilities.Object, _mockDataAccess.Object);
            // Додайте цей рядок для налаштування поведінки методу SpecificElement
            _mockUtilities.Setup(u => u.SpecificElement(It.IsAny<List<Tuple<char, char>>>(), It.IsAny<char>()))
                        .Returns(new List<char> { '2' }); // Забезпечте, що метод завжди повертає валідний результат
        }


        [Test]
        public void Accepts_ValidInput_CallsSpecificElement()
        {
            var results = new List<bool>();
            string input = "ab"; // Переконайтеся, що цей рядок не порожній
            _automaton.Accepts('1', input, results);
            _mockUtilities.Verify(m => m.SpecificElement(It.IsAny<List<Tuple<char, char>>>(), '1'), Times.Once);
        }

        [Test]
        public void Accepts_WhenThrowsException_HandlesException()
        {
            var results = new List<bool>();
            _mockUtilities.Setup(u => u.SpecificElement(It.IsAny<List<Tuple<char, char>>>(), '1'))
                          .Throws(new InvalidOperationException("Test Exception"));

            string input = "ab";

            Assert.Throws<InvalidOperationException>(() => _automaton.Accepts('1', input, results));
        }

        [Test]
        public void SpecificElement_CalledMultipleTimes_VerifiesMultipleCalls()
        {
            var results = new List<bool>();
            _mockUtilities.Setup(u => u.SpecificElement(It.IsAny<List<Tuple<char, char>>>(), It.IsAny<char>()))
                          .Returns(new List<char> { '2' });
            string input1 = "aaa";
            string input2 = "aab";

            _automaton.Accepts('1', input1, results);
            _automaton.Accepts('1', input2, results);

            _mockUtilities.Verify(m => m.SpecificElement(It.IsAny<List<Tuple<char, char>>>(), It.IsAny<char>()), Times.Exactly(6));
        }
    }
    [TestFixture]
    public class UtilitiesTests
    {
        private Mock<Utilities> _mockUtilities;

        [SetUp]
        public void Setup()
        {
            _mockUtilities = new Mock<Utilities>() { CallBase = true };  // CallBase дозволяє викликати реальні методи
            _mockUtilities.Setup(u => u.TranslateToChar(It.IsAny<int>())).Returns('f'); // Замоканий метод
        }

        [Test]
        public void TranslateToChar_ReturnsMockedValue()
        {
            char result = _mockUtilities.Object.TranslateToChar(1);
            Assert.AreEqual('f', result); // Перевірка замоканого методу
        }

        [Test]
        public void CharToInt_ReturnsRealValue()
        {
            int result = _mockUtilities.Object.CharToInt('3');
            Assert.AreEqual(3, result); // Перевірка реального методу
        }
    }
}
