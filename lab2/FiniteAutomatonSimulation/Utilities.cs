using System;

namespace FiniteAutomatonSimulation
{
    public static class Utilities
    {
        public static char TranslateToChar(int number)
        {
            if (number >= 1 && number <= 26)
            {
                return (char)('a' + number - 1);
            }
            return '?';
        }

        public static int CharToInt(char digitChar)
        {
            return digitChar - '0';
        }

        public static List<char> SpecificElement(List<Tuple<char, char>> transitions, char target)
        {
            var result = new List<char>();
            foreach (var transition in transitions)
            {
                if (transition.Item1 == target)
                {
                    result.Add(transition.Item2);
                }
            }
            return result;
        }

        public static void CheckResult(List<bool> results)
        {
            if (results.Any(res => res))
            {
                Console.WriteLine("This string is accessible.");
            }
            else
            {
                Console.WriteLine("This string is not accessible.");
            }
            results.Clear();
        }
    }
}
