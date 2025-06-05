#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <functional>
#include <algorithm>
#define NOT_APPLICABLE -1
using namespace std;
long long gcd(long long num1, long long num2)
{
	return num2 == 0 ? num1 : gcd(num2, num1 % num2);
}
long long minElement(long long first_element, long long last_element)
{
	if (last_element < first_element)
		return last_element;
	else
		return first_element;
}
vector<long long> getCosts(long long num_of_cables)
{
	vector<long long> cables(num_of_cables, 0);
	for (long long i = 0; i < num_of_cables; i++)
	{
		long long cost;
		cin >> cost;
		cables[i] = cost;
	}
	return cables;
}
vector<long long> createGraph(const vector<long long> &cables, long long num_of_cables, long long special_cable)
{
	vector<long long> connections(num_of_cables - 1, special_cable);
	for (long long i = 0; i < num_of_cables; i++)
	{
		long long current_min_cost = NOT_APPLICABLE;
		long long gcd_cost = cables[i], min_cost = cables[i];
		for (long long j = i + 1; j < num_of_cables; j++)
		{
			gcd_cost = gcd(gcd_cost, cables[j]);
			min_cost = minElement(min_cost, cables[j]);
			if (gcd_cost == min_cost)
			{
				current_min_cost = min_cost;
				if (j == num_of_cables - 1)
					for (long long k = i; k < j; k++)
						if (connections[k] > current_min_cost)
							connections[k] = current_min_cost;
				continue;
			}
			else if(current_min_cost != NOT_APPLICABLE)
				for (long long k = i; k < j - 1; k++)
					if (connections[k] > current_min_cost)
						connections[k] = current_min_cost;
			break;
		}
	}
	return connections;
}
void printMinCost(const vector<long long> &connections, long long num_of_cables)
{
	long long min_cost = 0;
	for (long long i = 0; i < num_of_cables - 1; i++)
			min_cost += connections[i];
	cout << min_cost << "\n";
}
int main()
{
	long long num_of_tests;
	cin >> num_of_tests;
	for (long long i = 0; i < num_of_tests; i++)
	{
		vector<long long> connections, cables;
		long long special_cable, num_of_cables;
		cin >> num_of_cables >> special_cable;
		cables = getCosts(num_of_cables);
		connections = createGraph(cables, num_of_cables, special_cable);
		printMinCost(connections, num_of_cables);
	}
	return 0;
}
