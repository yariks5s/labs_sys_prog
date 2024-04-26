public interface IDataAccess
{
    Dictionary<char, List<Tuple<char, char>>> LoadTransitions();
}
