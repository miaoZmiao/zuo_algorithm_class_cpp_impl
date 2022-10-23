#include <iostream>
#include "Code01_SplitSumClosed.hpp"
#include "Code02_SplitSumClosedSizeHalf.hpp"
#include "Code03_NQueens.hpp"
#include "fruits_taocans.hpp"
using namespace  std;;
int main()
{
	test_Code01_SplitSumClosed();
	test_Code02_SplitSumClosedSizeHalf();
	test_Code03_NQueens();
	test_FRUITS_TAOCAN();
	char c;
	cin >> c;
	return 0;
}