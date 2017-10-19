#include <iostream>
#include <queue>
#include <vector>

void priority_queue_test();

int main()
{
	priority_queue_test();

	char ch;
	std::cin >> ch;
}

void priority_queue_test()
{
	struct Path
	{
		int					 path_cost = 0;
		int					 actual_row;
		int					 actual_column;
		std::vector<int>	 actions;
	};
	auto cmp = [](Path& left, Path& right) { return left.path_cost > right.path_cost; };

	std::priority_queue<Path, std::deque<Path>, decltype(cmp)>	paths(cmp);

	Path p1;
	p1.path_cost = 0;
	Path p2;
	p2.path_cost = 3;
	Path p3;
	p3.path_cost = 9;
	Path p4;
	p4.path_cost = 2;

	paths.push(p1);
	paths.push(p2);
	paths.push(p3);
	paths.push(p4);

	while (!paths.empty())
	{
		std::cout << paths.top().path_cost << " ";
		paths.pop();
	}

}

