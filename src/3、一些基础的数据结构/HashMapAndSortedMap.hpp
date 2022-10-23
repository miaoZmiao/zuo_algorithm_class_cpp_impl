#pragma once
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;

namespace HashMapAndSortedMap {

	// C++ 如果要使用  自定义类型T 作为 unordered_map
	// 或者 unordered_set 类型的  KEY
	// 必须要定义 T 类型的 hash 运算
	// 可以在 std 命名空间 增加类型T的偏特化实现
	//
	//namespace std {
	//	
	//	template<>
	//	struct std::hash<T> {
	//		size_t operator()(const T & obj)
	//		{
	//			// write your own hash calculate
	//			result = 1023051;
	//			return size_t(result);
	//		}
	//	};
	//}
	// 实例化一个 以T类型作为Key 的 unordered_map 对象
	//  unordered_map<T, int>  umap1;
	// 实例化一个 以T类型作为Key 的 unordered_set 对象
	//  unordered_set<T>  uset1;
	// 如果要使用自定义类型作为 map set 的 KEY
	//  需要定义  类型T 的比较操作符，并在map set 的实例化中作为类型参数传入
	// 
	//struct MyCompare{
	//	
	//	bool operator()(const T & left, const T & right) const {
	//		// write you own campare calculate
	//		
	//		return left.value < right.value;
	//	}
	//};
	// 实例化 map 的时候传入 MyCompare 
	// map<T, int, MyCompare> map1;
	// 实例化 set 的时候传入 MyCompare
	// set<T, MyCompare> set1;
}