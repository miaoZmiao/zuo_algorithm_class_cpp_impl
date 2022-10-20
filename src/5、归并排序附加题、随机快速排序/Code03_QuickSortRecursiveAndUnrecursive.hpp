#pragma once
#include "utility_func.hpp"
#include <stack>
namespace Code03_QuickSortRecursiveAndUnrecursive {


	// arr[L...R] 玩荷兰国旗问题的划分，以arr[R]做划分值
// <arr[R] ==arr[R] > arr[R]
	vector<int> netherlandsFlag(vector<int>& arr, int L, int R) {
		if (L > R) { // L...R L>R
			return { -1, -1 };
		}
		if (L == R) {
			return  { L, R };
		}
		int less = L - 1; // < 区 右边界
		int more = R; // > 区 左边界
		int index = L;
		while (index < more) { // 当前位置，不能和 >区的左边界撞上
			if (arr[index] == arr[R]) {
				index++;
			}
			else if (arr[index] < arr[R]) {
				//				swap(arr, less + 1, index);
				//				less++;
				//				index++;						
				swap(arr, index++, ++less);
			}
			else { // >
				swap(arr, index, --more);
			}
		}
		swap(arr, more, R); // <[R]   =[R]   >[R]
		return { less + 1, more };
	}

	void process1(vector<int>& arr, int L, int R) {
		if (L >= R) {
			return;
		}
		// [ equalArea[0]  ,  equalArea[0]]
		vector<int> equalArea = netherlandsFlag(arr, L, R);
		process1(arr, L, equalArea[0] - 1);
		process1(arr, equalArea[1] + 1, R);
	}

	void quickSort1(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		process1(arr, 0, arr.size() - 1);
	}

	struct Op {
		int l;
		int r;

		Op(int left, int right) {
			l = left;
			r = right;
		}

	};


	void quickSort2(vector<int>& arr) {
		if (arr.size() < 2) {
			return;
		}
		int N = arr.size();

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<>  dist(0.0, 1.0);
		swap(arr, (int)(dist(mt)*N), N - 1);
		vector<int> equalArea = netherlandsFlag(arr, 0, N - 1);
		int el = equalArea[0];
		int er = equalArea[1];
		std::stack<Op> st;
		st.push( Op(0, el - 1));
		st.push( Op(er + 1, N - 1));
		while (!st.empty()) {
			Op op = st.top(); // op.l  ... op.r
			st.pop();
			if (op.l < op.r) {
				swap(arr, op.l + (int)(dist(mt) * (op.r - op.l + 1)), op.r);
				equalArea = netherlandsFlag(arr, op.l, op.r);
				el = equalArea[0];
				er = equalArea[1];
				st.push( Op(op.l, el - 1));
				st.push( Op(er + 1, op.r));
			}
		}
	}


}


void test_Code03_QuickSortRecursiveAndUnrecursive() {
	int testTime = 1000;
	int maxSize = 100;
	int maxValue = 100;
	cout << "test_Code03_QuickSortRecursiveAndUnrecursive begin" << endl;
	for (int i = 0; i < testTime; i++) {
		vector<int> arr = generateRandomArray(maxSize, maxValue);
		vector<int> arr1 = arr;
		vector<int> arr2 = arr;
		 Code03_QuickSortRecursiveAndUnrecursive::quickSort1(arr1);
		 Code03_QuickSortRecursiveAndUnrecursive::quickSort2(arr2);
		if (!vector_equal(arr1, arr2)) {
			print(arr);
			print(arr1);
			print(arr2);
			break;
		}
	}
	cout << "test_Code03_QuickSortRecursiveAndUnrecursive end" << endl;

}