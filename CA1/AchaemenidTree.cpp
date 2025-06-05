#include <iostream>
#include <vector>
using namespace std;
vector<int> getLineInput(int number_of_input)
{
	vector<int> input(number_of_input, 0);
	for (int i = 0; i < number_of_input; i++)
	{
		int element;
		cin >> element;
		input[i] = element;
	}
	return input;
}
void printVector(vector<int> input)
{
	for (unsigned int i = 0; i < input.size(); i++)
		cout << input[i] << " ";
	cout << "\n";
}
vector<int> findMax(vector<int> rulers, vector<int> result, int diff, int end, int start = 0, int current_height = 0)
{
	int max = 0, index_max = -1;
	if (start > end)
		return result;
	for (int i = start; end >= i; i++)
	{
		if (rulers[i] > max)
		{
			max = rulers[i];
			index_max = i;
		}
	}
	if (current_height <= diff)
	{
		current_height++;
		result[index_max] = max;
		result = findMax(rulers, result, diff, index_max - 1, start, current_height);
		result = findMax(rulers, result, diff, end, index_max + 1, current_height);
	}
	return result;
}
void getCommand(int num_of_sets)
{
	for (int i = 0; i < num_of_sets; i++)
	{
		vector<int> rulers;
		int num_of_rulers, diff;
		cin >> num_of_rulers;
		vector<int> result(num_of_rulers, 0);
		cin >> diff;
		rulers = getLineInput(num_of_rulers);
		result = findMax(rulers, result, diff, num_of_rulers - 1);
		printVector(result);
	}
}
int main()
{
	int num_of_sets;
	cin >> num_of_sets;
	getCommand(num_of_sets);
	return 0;
}
