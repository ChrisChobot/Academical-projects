namespace Bellman_ford
{
    struct Edge
    {
        public int StartPoint;
        public int EndPoint;
        public int Weight;

        public Edge(int startPoint, int endPoint, int weight)
        {
            StartPoint = startPoint;
            EndPoint = endPoint;
            Weight = weight;
        }
    }
}
