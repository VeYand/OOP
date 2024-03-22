#include "include/VectorOperations.h"
#include <iomanip>
#include <iostream>
#include <vector>

DoubleTypeNumbersVector ReadNumbers()
{
	DoubleTypeNumbersVector nums;

	double num;
	while (!std::cin.eof())
	{
		if (!(std::cin >> num))
		{
			break;
		}

		nums.push_back(num);
	}

	return nums;
}

void PrintNumbers(const DoubleTypeNumbersVector& nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		std::cout << std::fixed << std::setprecision(3) << nums[i];
		if (i != nums.size() - 1)
		{
			std::cout << ' ';
		}
	}
	std::cout << std::endl;
}

int main()
{
	auto vec = ReadNumbers();
	MultiplyNegativeNumsToMaxAndMinNum(vec);
	Sort(vec);
	PrintNumbers(vec);

	return 0;
}
