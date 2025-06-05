#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
long long findOnes(long long input_number, long long num_digits)
{
	long long count_one = 0, temp_count1 = 0, temp_count2 = 0;
	long long number_one = (pow(10, num_digits) - 1) / 9;
	while (input_number >= number_one)
	{
		input_number -= number_one;
		count_one += num_digits;
	}
	if (!input_number)
		return count_one;
	temp_count1 = count_one + findOnes(input_number, num_digits - 1);
	temp_count2 = count_one + findOnes(number_one - input_number, num_digits - 1) + num_digits;
	return min(temp_count1, temp_count2);
}
int main()
{
	long long input_number;
	long long count_one = 0;
	cin >> input_number;
	long long num_digits = floor(log10(input_number) + 1);
	count_one = findOnes(input_number, num_digits + 1);
	cout << count_one << "\n";
	return 0;
}
