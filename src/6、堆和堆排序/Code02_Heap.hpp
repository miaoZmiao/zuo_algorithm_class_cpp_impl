#pragma once
#include "utility_func.hpp"


namespace Code02_Heap {


	class MyMaxHeap {

		vector<int> heap;
		int limit;
		int heapSize;
	public:
		MyMaxHeap(int limit) {
			heap.reserve(limit);
			this->limit = limit;
			heapSize = 0;
		}

		bool isEmpty() {
			return heapSize == 0;
		}

		bool isFull() {
			return heapSize == limit;
		}

		bool push(int value) {
			if (isFull())
			{
				return false;
			}
			heap[heapSize] = value;
			heapInsert(heap, heapSize++);
			return true;
		}
			
		int pop() {
			if (isEmpty())
			{
				return 0xFFFFFFFF;
			}
			int ans = heap[0];
			swap(heap, 0, --heapSize);
			heapify(heap, 0, heapSize);
			return ans;
		}

	private:
		// 新加进来的数，现在停在了index位置，请依次往上移动，
		// 移动到0位置，或者干不掉自己的父亲了，停！
		void heapInsert(vector<int> &arr, int index)
		{
			while (arr[index] > arr[(index-1) / 2])
			{
				swap(arr, index, (index - 1) / 2);
				index = (index - 1) / 2;
			}
		}

		// 从index位置，往下看，不断的下沉
		// 停：较大的孩子都不再比index位置的数大；已经没孩子了
		void heapify(vector<int> &arr, int index, int heapSize) {
			int left = index * 2 + 1;
			while (left < heapSize)
			{
				int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
				largest = arr[largest] > arr[index] ? largest : index;
				if (largest == index)
				{
					break;
				}
				swap(arr, index, largest);
				index = largest;
				left = index * 2 + 1;
			}

		}

	};


	class RightMaxHeap {
		vector<int> heap;
		int limit;
		int heapSize;
	public:
		RightMaxHeap(int limit) {
			heap.reserve(limit);
			this->limit = limit;
			heapSize = 0;
		}
		bool isEmpty() {
			return heapSize == 0;
		}

		bool isFull() {
			return heapSize == limit;
		}

		bool push(int value) {
			if (isFull())
			{
				return false;
			}
			heap[heapSize++] = value;
			return true;
		}

		int pop() {
			if (isEmpty())
			{
				return 0xFFFFFFFF;
			}
			int maxIndex = 0;
			for (int i = 1; i < heapSize; i++) {
				if (heap[i] > heap[maxIndex]) {
					maxIndex = i;
				}
			}
			int ans = heap[maxIndex];
			heap[maxIndex] = heap[--heapSize];
			return ans;
		}
	};


}

using Code02_Heap::MyMaxHeap;
using Code02_Heap::RightMaxHeap;

void  test_Code02_Heap() {

	int value = 1000;
	int limit = 100;
	int testTimes = 10000;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<> dist(0.0, 1.0);
	cout << "test_Code02_Heap begin" << endl;
	for (int i = 0; i < testTimes; i++) {
		int curLimit = (int)(dist(mt) * limit) + 1;
		MyMaxHeap my(curLimit);
		RightMaxHeap test(curLimit);
		
		int curOpTimes = (int)(dist(mt) * limit);
		for (int j = 0; j < curOpTimes; j++) {
			if (my.isEmpty() != test.isEmpty()) {
				cout << "Oops!" << endl;
			}
			if (my.isFull() != test.isFull()) {
				cout << "Oops!" << endl;
			}
			if (my.isEmpty()) {
				int curValue = (int)(dist(mt) * value);
				my.push(curValue);
				test.push(curValue);
			}
			else if (my.isFull()) {
				if (my.pop() != test.pop()) {
					cout << "Oops!" << endl;
				}
			}
			else {
				if (dist(mt) < 0.5) {
					int curValue = (int)(dist(mt) * value);
					my.push(curValue);
					test.push(curValue);
				}
				else {
					if (my.pop() != test.pop()) {
						cout << "Oops!" << endl;
					}
				}
			}

		}
	}
	cout << "test_Code02_Heap end" << endl;


}