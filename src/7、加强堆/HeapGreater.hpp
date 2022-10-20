#pragma once
#include <vector>
#include <unordered_map>


template <typename T>
struct HashKey_Trait {
	using Key_Type = size_t;
};



template <typename T>
struct KeyCompareLess {
	typedef typename HashKey_Trait<T>::Key_Type KeyT;
	bool operator()(const KeyT & left, const KeyT & right) const
	{
		return left < right;
	}
};

template <typename T>
struct KeyCompareBigger {
	typedef typename HashKey_Trait<T>::Key_Type KeyT;
	bool operator()(const KeyT & left, const KeyT & right) const
	{
		return left > right;
	}
};


template <typename T>
struct HashKeyGen {
	typedef typename HashKey_Trait<T>::Key_Type KeyT;

	static KeyT getKey(const T & obj) {
		KeyT result = std::hash<T>()(obj);
		return result;
	}
};


template <typename T, 
	typename Compare = KeyCompareLess<T>>
class HeapGreater {

	std::vector<T> heap;
	typedef typename HashKey_Trait<T>::Key_Type KeyT;
	std::unordered_map<KeyT, size_t> indexMap;
	int heapSize;
	Compare comp;
public:
	HeapGreater() {
		heapSize = 0;
	}

	bool isEmpty() {
		return heapSize == 0;
	}

	int size() {
		return heapSize;
	}

	bool  contains(const T &obj) {
		KeyT key = HashKeyGen<T>::getKey(obj);
		return indexMap.count(key) == 1;
	}

	T peek() {
		return heap[0];
	}

	void push(const T & obj) {
		heap.push_back(obj);
		KeyT key = HashKeyGen<T>::getKey(obj);
		indexMap.insert({ key, heapSize});
		heapInsert(heapSize++);
	}


	T pop() {
		T ans = heap[0];
		swap(0, heapSize - 1);
		KeyT key = HashKeyGen<T>::getKey(ans);
		indexMap.erase(key);
		heap.pop_back();
		--heapSize;
		heapify(0);
		return ans;
	}


	void remove(const T & obj) {
		T replace = heap.back();
		KeyT targetkey = HashKeyGen<T>::getKey(obj);
		KeyT replacekey = HashKeyGen<T>::getKey(replace);
		size_t targetindex = indexMap[targetkey];
		indexMap.erase(targetkey);
		heap.pop_back();
		--heapSize;
		if (targetkey != replacekey) {
			heap[targetindex]= replace;
			indexMap.insert_or_assign(replacekey, targetindex);
			resign(replace);
		}
	}

	void resign(const T & obj, std::function<void(T & target)> doas) {
		KeyT targetkey = HashKeyGen<T>::getKey(obj);
		size_t realidx = indexMap[targetkey];
		doas(heap[realidx]);
		heapInsert(indexMap[targetkey]);
		heapify(indexMap[targetkey]);
	}

	void resign(const T & obj) {
		KeyT targetkey = HashKeyGen<T>::getKey(obj);
		heapInsert(indexMap[targetkey]);
		heapify(indexMap[targetkey]);
	}


	void heapInsert(size_t index) {
		while (index > 0 && comp(heap[index], heap[(index - 1) / 2])) {
			swap(index, (index - 1) / 2);
			index = (index - 1) / 2;
		}
	}

	void heapify(size_t index) {
		size_t left = index * 2 + 1;
		while (left < heapSize) {
			size_t best = left + 1 < heapSize && comp(heap[(left + 1)], heap[left]) ? (left + 1) : left;
			best = comp(heap[best], heap[index])  ? best : index;
			if (best == index) {
				break;
			}
			swap(best, index);
			index = best;
			left = index * 2 + 1;
		}
	}

	void swap(size_t i, size_t j) {
		if (i == j)
		{
			return;
		}
		T o1 = heap[i];
		T o2 = heap[j];
		heap[i] = o2;
		heap[j] = o1;
		KeyT o2key = HashKeyGen<T>::getKey(o2);
		KeyT o1key = HashKeyGen<T>::getKey(o1);
		indexMap.insert_or_assign(o2key, i);
		indexMap.insert_or_assign(o1key, j);
	}


	vector<T> getAllElements() {
		vector<T> ans(heap.size());
		size_t idx = 0;
		for (T & c : heap) {
			ans[idx++] = c;
		}
		return ans;
	}
};