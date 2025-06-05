#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 300005
using namespace std;
typedef long long LL;
int main()
{
	LL num_of_requests;
	cin >> num_of_requests;
	for (int i = 0; i < num_of_requests; i++)
	{
		LL min_cost, num_of_assistants;
		cin >> num_of_assistants;
		vector<LL> wall_height(MAX, 0), cost(MAX, 0);
		vector<vector<LL>> dp(MAX, vector<long long>(5, 0));
		for (int j = 1; j <= num_of_assistants; j++)
			cin >> wall_height[j] >> cost[j];
		for (int j = 1; j <= num_of_assistants; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				dp[j][k] = 1e18 - 1LL;
				for (int l = 0; l < 3; l++)
				{
					if (wall_height[j - 1] + l == wall_height[j] + k)
						continue;
					dp[j][k] = min(dp[j][k], dp[j - 1][l] + k*cost[j]);
				}
			}
		}
		min_cost = min(dp[num_of_assistants][1], min(dp[num_of_assistants][0], dp[num_of_assistants][2]));
		cout << min_cost;
	}
	return 0;
}
