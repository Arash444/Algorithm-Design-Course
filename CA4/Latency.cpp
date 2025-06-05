#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <functional>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> vertice;
vector<vector<vertice>> createGraph(int num_of_links, int num_of_server)
{
	vertice input_vertice;
	vector<vector<vertice>> graph(num_of_server);
	for (int i = 0; i < num_of_links; i++)
	{
		int vertice1, vertice2, delay;
		cin >> vertice1 >> vertice2 >> delay;
		graph[vertice1 - 1].push_back(make_pair(vertice2 - 1, delay));
	}
	return graph;
}
void printTime(vector<int> distance, vector<bool> is_in_S)
{
	for (int i = 0; i < is_in_S.size(); i++)
	{
		if (!is_in_S[i])
		{
			cout << -1 << "\n";
			return;
		}
	}
	int time = *max_element(distance.begin(), distance.end());
	cout << time << "\n";
}
void findShortPaths(vector<vector<vertice>> graph, vector<int> distance, vector<bool> is_in_S, int num_of_server, int starting_server)
{
	priority_queue <vertice, vector<vertice>, greater<vertice> > shortest_edges;
	shortest_edges.push(make_pair(starting_server - 1, 0));
	while (!shortest_edges.empty())
	{
		int min_vertice = shortest_edges.top().first;
		shortest_edges.pop();
		is_in_S[min_vertice] = true;
		for (int j = 0; j < graph[min_vertice].size(); j++)
		{
			int second_vertice = graph[min_vertice][j].first;
			if (distance[min_vertice] + graph[min_vertice][j].second < distance[second_vertice])
			{
				distance[second_vertice] = distance[min_vertice] + graph[min_vertice][j].second;
				shortest_edges.push(make_pair(second_vertice, distance[min_vertice]));
			}
		}
	}
	printTime(distance, is_in_S);
}
int main()
{
	int num_of_server, num_of_links, starting_server;
	cin >> num_of_server >> num_of_links >> starting_server;
	vector<vector<vertice>> graph;
	vector<int> distance(num_of_server, numeric_limits<int>::max());
	vector<bool> is_in_S(num_of_server, false);
	distance[starting_server - 1] = 0;
	graph = createGraph(num_of_links, num_of_server);
	findShortPaths(graph, distance, is_in_S, num_of_server, starting_server);
	return 0;
}
