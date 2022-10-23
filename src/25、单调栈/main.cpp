#include <iostream>
#include "Code01_MonotonousStack.hpp"
#include "Code02_AllTimesMinToMax.hpp"
#include "Code03_LargestRectangleInHistogram.hpp"
#include "Code04_MaximalRectangle.hpp"
#include "Code05_CountSubmatricesWithAllOnes.hpp"
using namespace std;

int main()
{
	test_Code01_MonotonousStack();
	test_Code02_AllTimesMinToMax();
	test_Code03_LargestRectangleInHistogram();
	test_Code04_MaximalRectangle();
	test_Code05_CountSubmatricesWithAllOnes();
	char c;
	cin >> c;
	return 0;
}