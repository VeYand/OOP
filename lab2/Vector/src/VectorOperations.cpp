#include "../include/VectorOperations.h"
#include <algorithm>
#include <limits>

void MultiplyNegativeNumsToMaxAndMinNum(DoubleTypeNumbersVector& nums)
{
	if (nums.empty())
	{
		return;
	}

	const auto [minIt, maxIt] = std::minmax_element(nums.begin(), nums.end());

	auto product = *maxIt * *minIt;

	for (auto& num : nums)
	{
		if (num < 0)
		{
			num *= product;
		}
	}
}

void Sort(DoubleTypeNumbersVector& nums)
{
	std::sort(nums.begin(), nums.end());
}