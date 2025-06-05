#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int> getLineInput(int range)
{
	vector<int> our_vector(range, 0);
	for (int i = 0; i < range; i++)
	{
		int element;
		cin >> element;
		our_vector[i] = element;
	}
	return our_vector;
}
bool check(int middle, vector<int> exam_period, vector<int> exam_prep)
{
	int days_remaining = -1;
	bool all_courses_done = true;
	queue <int> courses_remaining;
	vector<int> courses(exam_prep.size(), 0);
	for (int j = middle - 1; j >= 0; j--)
	{
		if (!exam_period[j])
		{
			days_remaining--;
			if (!days_remaining)
			{
				courses_remaining.pop();
				if (!courses_remaining.empty())
					days_remaining = exam_prep[courses_remaining.front() - 1];
				else
					days_remaining = -1;
			}
		}
		else
		{
			if (!courses[exam_period[j] - 1])
			{
				if (courses_remaining.empty())
					days_remaining = exam_prep[exam_period[j] - 1];
				courses_remaining.push(exam_period[j]);
				courses[exam_period[j] - 1] = 1;
			}
			else
			{
				days_remaining--;
				if (!days_remaining)
				{
					courses_remaining.pop();
					if (!courses_remaining.empty())
						days_remaining = exam_prep[courses_remaining.front() - 1];
					else
						days_remaining = -1;
				}
			}
		}
	}
	for (int i = 0; i < courses.size(); i++)
		if (!courses[i])
			all_courses_done = false;
	if (days_remaining < 0 && all_courses_done)
		return true;
	else
		return false;
}
void Schedule(vector<int> exam_period, vector<int> exam_prep)
{
	int low = 0, high = exam_period.size() + 1;
	while (high - low > 1)
	{
		int middle = (high + low) / 2;
		if (check(middle, exam_period, exam_prep))
			high = middle;
		else
			low = middle;
	}
	if (high == exam_period.size() + 1)
		cout << -1 << "\n";
	else 
		cout << high << "\n";
}
int main()
{
	int exam_period_duration, num_of_exams;
	vector<int> exam_period, exam_prep;
	cin >> exam_period_duration >> num_of_exams;
	exam_period = getLineInput(exam_period_duration);
	exam_prep = getLineInput(num_of_exams);
	Schedule(exam_period, exam_prep);
	return 0;
}
