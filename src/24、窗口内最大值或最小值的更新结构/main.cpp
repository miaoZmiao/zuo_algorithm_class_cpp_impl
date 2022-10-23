#include <iostream>
#include "Code01_SlidingWindowMaxArray.hpp"
#include "Code02_AllLessNumSubArray.hpp"
#include "Code03_GasStation.hpp"
#include "Code04_MinCoinsOnePaper.hpp"
using namespace std;

int main()
{
	test_Code01_SlidingWindowMaxArray();
	test_Code02_AllLessNumSubArray();
	test_Code03_GasStation();
	test_Code04_MinCoinsOnePaper();
	char c;
	cin >> c;
	return 0;
}