using System;
using System.Collections.Generic;

namespace Bellman_ford
{
    class BellmanFordAlgorithm
    {
        private List<Edge> _edges = new List<Edge>();
        private List<int> _weights = new List<int>();
        private int _testCount;
        private int _verticesCount;

        public void StartAlgorithm()
        {
            string consoleLine = Console.ReadLine();
            _testCount = int.Parse(consoleLine);

            for (int i = 0; i < _testCount; i++)
            {
                consoleLine = Console.ReadLine();
                _verticesCount = int.Parse(consoleLine);

                string[][] graph = new string[_verticesCount][];
                for (int j = 0; j < _verticesCount; j++)
                {
                    graph[j] = new string[_verticesCount];
                }


                for (int j = 0; j < _verticesCount; j++)
                {
                    consoleLine = Console.ReadLine();
                    graph[j] = consoleLine.Split(' ');
                }

                LoadData(graph);
                Algorithm();
                Console.WriteLine();
            }
        }

        private void LoadData(string[][] wholeGraph)
        {
            _edges.Clear();
            _weights.Clear();

            for (int i = 0; i < _verticesCount; i++)
            {
                for (int j = 0; j < _verticesCount; j++)
                {
                    int weight = int.Parse(wholeGraph[i][j]);
                    if (weight != 0)
                    {
                        _edges.Add(new Edge(i, j, weight));
                    }
                }
            }

            for (int i = 0; i < _verticesCount; i++)
            {
                _weights.Add(int.MaxValue);
            }

            _weights[0] = 0;
        }

        private void Algorithm()
        {
            for (int i = 1; i < _verticesCount; i++)
            {
                foreach (Edge edge in _edges)
                {
                    Relax(edge);
                }

                PrintOutput();
            }
        }

        private void Relax(Edge edge)
        {
            int newWeight = Tools.AddValues(_weights[edge.StartPoint], edge.Weight);

            if (_weights[edge.EndPoint] > newWeight)
            {
                _weights[edge.EndPoint] = newWeight;
            }
        }

        private void PrintOutput()
        {
            string line = Tools.CheckForInfinity(_weights[0]).ToString();

            for (int i = 1; i < _verticesCount; i++)
            {
                line = string.Format("{0} {1}", line, Tools.CheckForInfinity(_weights[i]));
            }

            Console.WriteLine(string.Format("{0} ", line));
        }
    }
}
