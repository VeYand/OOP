#include "include/Athlete.h"
#include "include/FindMaxEx.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<Athlete> athletes = {
		{ "Bob Johnson", 180, 75 },
		{ "Carey Mulligan", 170, 60 },
		{ "Ryan Gosling", 190, 85 },
		{ "Christina Hendricks", 175, 65 }
	};

	Athlete tallest;
	Athlete heaviest;

	if (FindMaxEx(athletes, tallest, [](const Athlete& a, const Athlete& b) {
			return a.height < b.height;
		}))
	{
		std::cout << "Tallest athlete: " << tallest.name << " with height " << tallest.height << "\n";
	}
	else
	{
		std::cout << "No athletes found.\n";
	}

	if (FindMaxEx(athletes, heaviest, [](const Athlete& a, const Athlete& b) {
			return a.weight < b.weight;
		}))
	{
		std::cout << "Heaviest athlete: " << heaviest.name << " with weight " << heaviest.weight << "\n";
	}
	else
	{
		std::cout << "No athletes found.\n";
	}

	return 0;
}
