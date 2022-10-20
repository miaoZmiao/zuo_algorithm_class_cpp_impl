#pragma once
#ifndef Code01_AppleMinBags_HPP
#define Code01_AppleMinBags_HPP
#include <iostream>
using namespace std;
namespace Code01_AppleMinBags {
	/*	题目一
		小虎去买苹果，商店只提供两种类型的塑料袋，每种类型都有任意数量。
		1）能装下6个苹果的袋子
		2）能装下8个苹果的袋子
		小虎可以自由使用两种袋子来装苹果，但是小虎有强迫症，他要求自己使用的袋子数量必须最少，且使用的每个袋子必须装满。
		给定一个正整数N，返回至少使用多少袋子。如果N无法让使用的每个袋子必须装满，返回 - 1
	*/
	int minBags(int apple) {
		if (apple < 0) {
			return -1;
		}
		int bag8 = (apple >> 3);
		int rest = apple - (bag8 << 3);
		while (bag8 >= 0) {
			// rest 个
			if (rest % 6 == 0) {
				return bag8 + (rest / 6);
			}
			else {
				bag8--;
				rest += 8;
			}
		}
		return -1;
	}

	int minBagAwesome(int apple) {
		if ((apple & 1) != 0) { // 如果是奇数，返回-1
			return -1;
		}
		if (apple < 18) {
			return apple == 0 ? 0 : (apple == 6 || apple == 8) ? 1
				: (apple == 12 || apple == 14 || apple == 16) ? 2 : -1;
		}
		return (apple - 18) / 8 + 3;
	}

}

void test_Code01_AppleMinBags() {

	cout << "test Code01_AppleMinBags begin" << endl;
	for (int i = 0; i < 200; i++)
	{
		cout << i<<":" << Code01_AppleMinBags::minBags(i) << endl;
	}
	cout << "test Code01_AppleMinBags end" << endl;
}


#endif