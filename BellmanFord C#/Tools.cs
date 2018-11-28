namespace Bellman_ford
{
    class Tools
    {
        public static int AddValues(int a, int b) //for safe adding
        {
            if (a == int.MaxValue || b == int.MaxValue)
            {
                return int.MaxValue;
            }
            else
            {
                return a + b;
            }
        }

        public static int CheckForInfinity(int number)
        {
            if (number == int.MaxValue)
            {
                return 0;
            }
            else
            {
                return number;
            }
        }
    }
}
