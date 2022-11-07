#pragma once
#include "HeapGreater.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct datamsg {
	int dataid;
	int nextpos;
};

struct datamsg_cmp {

	bool operator()(const datamsg &left, const datamsg &right) const {
		return left.nextpos > right.nextpos;
	}
};

template<>
struct std::hash<datamsg> {
	size_t operator()(const datamsg &o) const {
		return (size_t)o.dataid;
	}
};

namespace DBCache {

	class Solution {
	public:
		int getMinUse(int cachesize, const vector<int> & dataids) {


			HeapGreater<datamsg, datamsg_cmp> pq;
			pq.size();

			int maxdataid = 0;
			for (int i = 0; i < dataids.size(); i++) {
				maxdataid = std::max(maxdataid, dataids[i]);
			}
			vector<int> nextpos(dataids.size(), INT_MAX);
			vector<int> datapos(maxdataid + 1, INT_MAX);
			for (int i = dataids.size() - 1; i >= 0; i--) {
				nextpos[i] = datapos[dataids[i]];
				datapos[dataids[i]] = i;
			}
			int ans = 0;

			for (int i = 0; i < dataids.size(); i++) {

				int dataid = dataids[i];
				datamsg tmp;
				tmp.dataid = dataid;
				tmp.nextpos = nextpos[i];
				if (pq.contains(tmp)) {
					pq.resign(tmp, [&](datamsg & target) {
						target.nextpos = nextpos[i];
					});
				}
				else {
					if (pq.size() < cachesize) {
						pq.push(tmp);
					}
					else {
						datamsg po = pq.peek();
						pq.pop();
						pq.push(tmp);
					}
					ans++;
				}
			}
			return ans;
		}

	};

	void test_main() {
		
		int cachesize = 3;
		vector<int> dataids{1,2,3,4,5,6,7,8,2,7,8,1,7,7,8,2};
		Solution sln;
		int ans = sln.getMinUse(cachesize, dataids);
		cout << ans << endl;
		
	}

}

void test_DBCache(){
	DBCache::test_main();
}
