#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#define MAX_BIT 17
#define NA "-1"
using namespace std;
typedef string bits;
vector<bits> getLineInput(long long number_of_input)
{
	vector<bits> input(number_of_input, " ");
	for (long long i = 0; i < number_of_input; i++)
	{
		long long element;
		cin >> element;
		bits binary_element = bitset<MAX_BIT>(element).to_string();
		input[i] = binary_element;
	}
	return input;
}
bits bigger_binary(bits binary1, bits binary2)
{
	long long temp1, temp2;
	temp1 = stoi(binary1, nullptr, 2);
	temp2 = stoi(binary2, nullptr, 2);
	if (temp1 > temp2)
		return binary1;
	else 
		return binary2;
}
bits maxXOR(vector<bits> guards, bits min_max)
{
	bits max_XOR = "00000000000000000";
	for (unsigned long long i = 0; i < guards.size(); i++)
	{
		bits temp_XOR = "00000000000000000";
		for (unsigned long long j = 0; j < MAX_BIT; j++)
		{
			if (guards[i][j] != min_max[j])
				temp_XOR[j] = '1';
		}
		max_XOR = bigger_binary(max_XOR, temp_XOR);
	}
	return max_XOR;
}

void findMinMax(vector<bits> guards, bits min_max, long long &result, long long current_position = 0, bits previous_bit = NA)
{
	if (current_position == MAX_BIT - 1)
	{
		bits temp_bits = maxXOR(guards, min_max);
		long long temp_result = stoi(temp_bits, nullptr, 2);
		if (temp_result < result)
			result = temp_result;
		return;
	}
	bool all_one = true, all_zero = true;
	if (previous_bit != NA)
	{
		for (unsigned long long i = 0; i < guards.size(); i++)
		{
			if (guards[i][current_position - 1] == previous_bit[0])
				guards.erase(guards.begin() + i);
		}
	}
	for (unsigned long long i = 0; i < guards.size(); i++)
	{
		if (all_one && guards[i][current_position] == '0')
			all_one = false;
		if (all_zero && guards[i][current_position] == '1')
			all_zero = false;
	}
	if (all_one)
	{
		min_max[current_position] = '1';
		findMinMax(guards, min_max, result, current_position + 1);
	}
	else if (all_zero)
	{
		min_max[current_position] = '0';
		findMinMax(guards, min_max, result, current_position + 1);
	}
	else
	{
		min_max[current_position] = '1';
		findMinMax(guards, min_max, result, current_position + 1, "1");
		min_max[current_position] = '0';
		findMinMax(guards, min_max, result, current_position + 1, "0");
	}
}
int main()
{
	vector<bits> guards;
	bits max_min = "00000000000000000";
	long long num_guards,result = 10000LL;
	cin >> num_guards;
	guards = getLineInput(num_guards);
	findMinMax(guards, max_min, result);
	cout << result << '\n';
	return 0;
}
