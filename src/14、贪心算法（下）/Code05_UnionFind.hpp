#pragma once
#include "utility_func.hpp"
#include <unordered_map>
#include <stack>
namespace Code05_UnionFind {

	// mei you shi yong guo 
	// buz zhi dao shen me qing kuang 
	template < typename T, typename THash = std::hash<T>>
	class UnionFind {
		std::unordered_map<size_t, T> nodes;
		std::unordered_map<size_t, size_t> parents;
		std::unordered_map<size_t, int> sizeMap;
		typename THash thashfunc;
	public:

		UnionFind(const vector<T> &values) {

			for (V & cur : values) {
				size_t hashValue = thashfunc(cur);
				T node = cur;
				nodes.insert({ hashValue, node });
				parents.insert({ hashValue, hashValue });
				sizeMap.insert({ hashValue, 1 });
			}
		}

		// 给你一个节点，请你往上到不能再往上，把代表返回
		T findFather(const T & cur) {
			std::stack<size_t> path;
			size_t curhashValue = thashfunc(cur);
			while (curhashValue != parents[curhashValue]) {
				path.push(curhashValue);
				curhashValue = parents[curhashValue];
			}
			while (!path.isEmpty()) {
				parents.put(path.pop(), curhashValue);
			}
			return  nodes[curhashValue];
		}

		bool isSameSet(const T & a, const T & b) {
			size_t ahash = thashfunc(findFather(nodes.get(a)));
			size_t bhash = thashfunc(findFather(nodes.get(b)));
			return  ahash == bhash;
		}

		void union_merge(const T & a, const T & b) {
			T aHead = findFather(a);
			T bHead = findFather(b);
			size_t ahash = thashfunc(aHead);
			size_t bhash = thashfunc(bHead);
			if (ahash != bhash) {
				int aSetSize = sizeMap[ahash];
				int bSetSize = sizeMap[bhash];
				T big = aSetSize >= bSetSize ? aHead : bHead;
				T small = big == aHead ? bHead : aHead;
				size_t bighash = thashfunc(big);
				size_t smallhash = thashfunc(small);
				parents.insert_or_assign({ smallhash, bighash });
				sizeMap.insert_or_assign({ bighash, aSetSize + bSetSize });
				sizeMap.remove(smallhash);
			}
		}

		int sets() {
			return sizeMap.size();
		}

	};

}