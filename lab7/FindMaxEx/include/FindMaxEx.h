#ifndef FINDMAXEX_FINDMAXEX_H
#define FINDMAXEX_FINDMAXEX_H

#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less) {
	if (arr.empty()) {
		return false;
	}

	auto tempMaxValue = arr[0];
	for (const auto& elem : arr) {
		if (less(tempMaxValue, elem)) {
			tempMaxValue = elem;
		}
	}

	maxValue = tempMaxValue;

	return true;
}

#endif // FINDMAXEX_FINDMAXEX_H
