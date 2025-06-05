#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
typedef vector<int> TA;
void getCommand(int num_of_TA, int num_of_course, vector<TA> &TA_org, vector<int> &course_size)
{
	for (int i = 0; i < num_of_TA; i++)
	{
		int course, expertise;
		cin >> course >> expertise;
		TA_org[course - 1].push_back(expertise);
		course_size[course - 1]++;
	}
}
void findMax(vector<TA> &TA_org, int num_of_course, vector<int> &course_size)
{
	for (int i = 0; i < num_of_course; i++)
	{
		int size = TA_org[i].size() - 1;
		sort(TA_org[i].begin(), TA_org[i].end(), greater<int>());
		for (int j = 0; j < size; j++)
			TA_org[i][j + 1] += TA_org[i][j];
	}
	int largest_size = *max_element(course_size.begin(), course_size.end());
	vector<int> max_exp(largest_size, 0);
	for (int i = 0; i < largest_size; i++)
	{
		for (int j = 0; j < num_of_course; j++)
		{
			int size = TA_org[j].size() - 1;
			if (size >= i && TA_org[j][i] > 0)
				max_exp[i] += TA_org[j][i];
		}
	}
	int max_sum = *max_element(max_exp.begin(), max_exp.end());
	if (max_sum > 0)
		cout << max_sum << "\n";
	else
		cout << 0 << "\n";
}
int main()
{
	int num_of_TA, num_of_course;
	cin >> num_of_TA >> num_of_course;
	vector<TA> TA_org(num_of_course);
	vector<int> course_size(num_of_course, 0);
	getCommand(num_of_TA, num_of_course, TA_org, course_size);
	findMax(TA_org, num_of_course, course_size);
	return 0;
}
