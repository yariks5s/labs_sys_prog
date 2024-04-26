using System;

namespace FiniteAutomatonSimulation
{

    public interface IUtilities
    {
        char TranslateToChar(int number);
        int CharToInt(char digitChar);
        List<char> SpecificElement(List<Tuple<char, char>> transitions, char target);
        void CheckResult(List<bool> results);
    }

    public class Utilities : IUtilities
    {
        public virtual char TranslateToChar(int number)
        {
            if (number >= 1 && number <= 26)
                return (char)('a' + number - 1);
            return '?';
        }

        public virtual int CharToInt(char digitChar)
        {
            return digitChar - '0';
        }

        public virtual List<char> SpecificElement(List<Tuple<char, char>> transitions, char target)
        {
            return transitions.Where(t => t.Item1 == target).Select(t => t.Item2).ToList();
        }

        public virtual void CheckResult(List<bool> results)
        {
            Console.WriteLine(results.Any(r => r) ? "This string is accessible." : "This string is not accessible.");
            results.Clear();
        }
    }


}
