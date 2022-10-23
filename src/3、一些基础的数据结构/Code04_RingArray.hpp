#pragma once
#include "utility_func.hpp"
namespace Code04_RingArray {
	class MyQueue {
		vector<int> arr;
		int pushi;// end
		int polli;// begin
		int size;
		int limit;
	public:
		MyQueue(int limit) {
			pushi = 0;
			polli = 0;
			size = 0;
			limit = limit;
		}

		void push(int value) {
			if (size == limit) {
				throw  std::runtime_error("队列满了，不能再加了");
			}
			size++;
			arr[pushi] = value;
			pushi = nextIndex(pushi);
		}

		int pop() {
			if (size == 0) {
				throw std::runtime_error("队列空了，不能再拿了");
			}
			size--;
			int ans = arr[polli];
			polli = nextIndex(polli);
			return ans;
		}

		bool isEmpty() {
			return size == 0;
		}

		// 如果现在的下标是i，返回下一个位置
		int nextIndex(int i) {
			return i < limit - 1 ? i + 1 : 0;
		}

	};
	
}