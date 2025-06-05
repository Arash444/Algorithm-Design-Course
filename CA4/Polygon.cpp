#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>
#define NOT_IN_ANY_DISTRICT -1
#define NO_PATH "INF"
using namespace std;
typedef pair<double, double> vertice;
vector<vector<int>> createGraph(int num_of_links, int num_of_districts)
{
	vector<vector<int>> graph(num_of_districts, vector<int>(num_of_districts, numeric_limits<int>::max()));
	for (int i = 0; i < num_of_districts; i++)
		graph[i][i] = 0;
	for (int i = 0; i < num_of_links; i++)
	{
		int vertice1, vertice2, delay;
		cin >> vertice1 >> vertice2 >> delay;
		graph[vertice1][vertice2] = delay;
	}
	return graph;
}
vector<vector<vertice>> createDistricts(int num_of_districts, vector<vertice> &min_points, vector<vertice> &max_points)
{
	vector<vector<vertice>> districts(num_of_districts);
	for (int i = 0; i < num_of_districts; i++)
	{
		int num_of_edges;
		cin >> num_of_edges;
		for (int j = 0; j < num_of_edges; j++)
		{
			double latitude, longitude;
			cin >> latitude >> longitude;
			districts[i].push_back(make_pair(latitude, longitude));
			if (latitude < min_points[i].first)
				min_points[i].first = latitude;
			if (longitude < min_points[i].second)
				min_points[i].second = longitude;
			if (latitude > max_points[i].first)
				max_points[i].first = latitude;
			if (longitude > max_points[i].second)
				max_points[i].second = longitude;
		}
	}
	return districts;
}
vector<vector<int>> findShortPaths(vector<vector<int>> graph, vector<vector<vertice>> districts, int num_of_districts)
{
	for (int k = 0; k < num_of_districts; k++)
		for (int i = 0; i < num_of_districts; i++)
			for (int j = 0; j < num_of_districts; j++)
			{
				int infinity = numeric_limits<int>::max();
				if (graph[i][k] != infinity && graph[k][j] != infinity)
					graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
	return graph;
}
bool onSegment(vertice point1, vertice point2, vertice point3)
{
	if (point2.second <= max(point1.second, point3.second) && point2.second >= min(point1.second, point3.second) 
		&& point2.first <= max(point1.first, point3.first) && point2.first >= min(point1.first, point3.first))
		return true;
	return false;
}
int orientation(vertice point1, vertice point2, vertice point3)
{
	double value = (((point2.first - point1.first) * (point3.second - point2.second)) - ((point2.second - point1.second) * (point3.first - point2.first)));
	if (value == 0)
		return 0;
	else if (value > 0)
		return 1;
	else
		return 2;
}
bool doIntersect(vertice point11, vertice point12, vertice point21, vertice point22)
{
	int orientation1 = orientation(point11, point12, point21), orientation2 = orientation(point11, point12, point22);
	int orientation3 = orientation(point21, point22, point11), orientation4 = orientation(point21, point22, point12);
	if (orientation1 != orientation2 && orientation3 != orientation4)
		return true;
	if (orientation1 == 0 && onSegment(point11, point12, point21)) 
		return true;
	if (orientation2 == 0 && onSegment(point11, point22, point21))
		return true;
	if (orientation3 == 0 && onSegment(point12, point11, point22))
		return true;
	if (orientation4 == 0 && onSegment(point12, point11, point22))
		return true;
	return false; 
}
int findDistrict(vector<vector<vertice>> districts, vertice point, int num_of_districts, vector<vertice> min_points, vector<vertice> max_points)
{
	int our_district = NOT_IN_ANY_DISTRICT, count = 0;
	for (int i = 0; i < num_of_districts; i++)
	{
		if (point.first < min_points[i].first || point.second < min_points[i].second ||
			point.first > max_points[i].first || point.second > max_points[i].second)
			continue;
		vertice half_line = make_pair(point.second, numeric_limits<int>::max());
		int j = 0, num_of_edges = districts[i].size();
		do
		{
			int next = (j + 1) % num_of_edges;
			if (doIntersect(districts[i][j], districts[i][next], point, half_line))
			{
				if (!orientation(districts[i][j], point, districts[i][next]))
					return onSegment(districts[i][j], point, districts[i][next]);
				count++;
			}
			j = next;
		} while (j != 0);
		if (count % 2)
			return our_district = i;
	}
	return our_district;
}
vector<vertice> getPoints(int num_of_requests)
{
	int num_of_points;
	cin >> num_of_points;
	vector<vertice> points(num_of_points, make_pair(0, 0));
	for (int i = 0; i < num_of_points; i++)
	{
		double latitude, longitude;
		cin >> latitude >> longitude;
		points[i] = make_pair(latitude, longitude);
	}
	return points;
}
void answerRequests(vector<vector<int>> graph, vector<vector<vertice>> districts, int num_of_districts, int num_of_requests, vector<vertice> min_points, vector<vertice> max_points)
{
	for (int i = 0; i < num_of_requests; i++)
	{
		vector<vertice> points;
		points = getPoints(num_of_requests);
		for (int j = 0; j < points.size() - 1; j++)
		{
			int district_id1, district_id2;
			district_id1 = findDistrict(districts, points[j], num_of_districts, min_points, max_points);
			district_id2 = findDistrict(districts, points[j + 1], num_of_districts, min_points, max_points);
			if (district_id1 == NOT_IN_ANY_DISTRICT || district_id2 == NOT_IN_ANY_DISTRICT)
				cout << NOT_IN_ANY_DISTRICT << "\n";
			else if(graph[district_id1][district_id2] == numeric_limits<int>::max())
				cout << NO_PATH << "\n";
			else
				cout << graph[district_id1][district_id2] << "\n";
		}
	}
}
int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<vector<vertice>> districts;
	vector<vector<int>> graph;
	int num_of_districts, num_of_links, num_of_requests;
	cin >> num_of_districts >> num_of_links;
	vector<vertice> min_points(num_of_districts, make_pair(numeric_limits<int>::max(), numeric_limits<int>::max()));
	vector<vertice> max_points(num_of_districts, make_pair(0.0, 0.0));
	districts = createDistricts(num_of_districts, min_points, max_points);
	graph = createGraph(num_of_links, num_of_districts);
	graph = findShortPaths(graph, districts, num_of_districts);
	cin >> num_of_requests;
	answerRequests(graph, districts, num_of_districts, num_of_requests, min_points, max_points);
	return 0;
}
