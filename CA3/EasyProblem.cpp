#include <iostream>
#include <vector>
using namespace std;
void printVector(vector<int> input)
{
	for (unsigned int i = 0; i < input.size(); i++)
		cout << input[i] << " ";
	cout << "\n";
}
vector<int> findSequence(int sum)
{
	vector<int> sequence;
	int current_sum = 0;
	for (int i = 1; current_sum + i < sum; i++)
	{
		current_sum += i;
		sequence.push_back(i);
	}
	return sequence;
}
void eatMeat(int total_day1, int total_day2, vector<int> meat_packages, vector<int> &day1_packages, vector<int> &day2_packages)
{
	int num_packages = meat_packages.size();
	for (int i = num_packages - 1; i >= 0; i--)
	{
		int meat = meat_packages[i];
		if (total_day1 >= meat)
		{
			total_day1 -= meat;
			day1_packages.push_back(meat);
		}
		else
		{
			total_day2 -= meat_packages[meat];
			day2_packages.push_back(meat);
		}
	}
}
int main()
{
	vector<int> meat_packages, day1_packages, day2_packages;
	int total_day1, total_day2, sum;
	cin >> total_day1 >> total_day2;
	sum = total_day1 + total_day2; 
	meat_packages = findSequence(sum);
	eatMeat(total_day1, total_day2, meat_packages, day1_packages, day2_packages);
	cout << day1_packages.size() << "\n";
	printVector(day1_packages);
	cout << day2_packages.size() << "\n";
	printVector(day2_packages);
	return 0;
}
