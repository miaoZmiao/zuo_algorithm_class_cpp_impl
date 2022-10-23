#pragma once
#ifndef Code01_LastSubstringInLexicographicalOrder_HPP
#define Code01_LastSubstringInLexicographicalOrder_HPP
#include <string>
#include "utility_func.hpp"
// ≤‚ ‘¡¥Ω”: https://leetcode.com/problems/last-substring-in-lexicographical-order/
namespace Code01_LastSubstringInLexicographicalOrder {


	class DC3 {
	public:
		vector<int> nums_;
		vector<int> sa_;
		vector<int> rank_;

		DC3() {}
		void reset(vector<int> & arr, int maxnum) {

			int N = arr.size();
			nums_.resize(N + 3, 0);
			for (int i = 0; i < N; i++)
			{
				nums_[i] = arr[i];
			}
			sa_ = skew(nums_, N, maxnum);
			rank_ = rank();
		}


		vector<int> skew(vector<int> & nums, int n, int maxnum) {

			int n0 = (n + 2) / 3;
			int n1 = (n + 1) / 3;
			int n2 = (n) / 3;
			int n02 = n0 + n2;
			vector<int> s12(n02 + 3, 0);
			vector<int> sa12(n02 + 3, 0);
			for (int i = 0, j = 0; i < n + (n0 - n1); i++)
			{
				if (i % 3 != 0)
				{
					s12[j++] = i;
				}
			}
			// s12  [1,2,4,5,7,8,10......]

			radixsort(nums, s12, sa12, 2, n02, maxnum);
			radixsort(nums, sa12, s12, 1, n02, maxnum);
			radixsort(nums, s12, sa12, 0, n02, maxnum);

			int name = 0;
			int c0 = -1, c1 = -1, c2 = -1;
			for (int i = 0; i < n02; i++)
			{
				int index = sa12[i];
				if (nums[index] != c0 || nums[index + 1] != c1 || nums[index + 2] != c2)
				{
					name++;
					c0 = nums[index];
					c1 = nums[index + 1];
					c2 = nums[index + 2];
				}
				if (index % 3 == 1)
				{
					s12[index / 3] = name;
				}
				else
				{
					s12[index / 3 + n0] = name;
				}
			}

			if (name < n02)
			{

				sa12 = skew(s12, n02, name);
				for (int i = 0; i < n02; i++)
				{
					s12[sa12[i]] = i + 1;
				}

			}
			else
			{
				// construct 1,4,7,10.....   
				//			 2,5,8,11....
				for (int i = 0; i < n02; i++)
				{
					sa12[s12[i] - 1] = i;
				}
			}

			// ◊º±∏ s0
			vector<int> s0(n0, 0);
			vector<int> sa0(n0, 0);
			for (int i = 0, k = 0; i < n02; i++)
			{
				if (sa12[i] < n0)
				{
					s0[k++] = 3 * sa12[i];
				}
			}
			radixsort(nums, s0, sa0, 0, n0, maxnum);

			vector<int> ans(n, 0);
			for (int s0_index = 0, s12_index = n0 - n1, k = 0; k < n; k++)
			{
				int i = sa12[s12_index] < n0 ? 3 * sa12[s12_index] + 1 :
					3 * (sa12[s12_index] - n0) + 2;
				int j = sa0[s0_index];

				if (sa12[s12_index] < n0 ?
					leq(nums[i], s12[sa12[s12_index] + n0], nums[j], s12[j / 3]) :
					leq(nums[i], nums[i + 1], s12[sa12[s12_index] - n0 + 1],
						nums[j], nums[j + 1], s12[j / 3 + n0])
					) 
				{
					ans[k] = i;
					s12_index++;
					if (s12_index == n02)
					{
						for (k++; k < n; k++)
						{
							ans[k] = sa0[s0_index++];
						}
					}


				}
				else
				{
					ans[k] = j;
					s0_index++;
					if (s0_index == n0)
					{
						for (k++; k < n; k++)
						{
							if (sa12[s12_index] < n0)
							{
								ans[k] = 3 * sa12[s12_index] + 1;
							}
							else
							{
								ans[k] = 3 * (sa12[s12_index]-n0) + 2;
							}
							s12_index++;
						}
					}
				}
			}

			return ans;
		}


		void radixsort(vector<int> & nums,
			vector<int> & input, vector<int>& output, int offset, int n, int maxNum)
		{
			vector<int> counts(maxNum + 1, 0);

			for (int i = 0; i < n; i++)
			{
				counts[nums[input[i] + offset]]++;
			}

			// count sum
			for (int i = 0, tmpsum = 0; i < maxNum + 1; i++)
			{
				int tmp = counts[i];
				counts[i] = tmpsum;
				tmpsum += tmp;
			}

			for (int i = 0; i < n; i++)
			{
				output[counts[nums[input[i] + offset]]++] = input[i];
			}
		}

		bool  leq(int a1, int a2, int b1, int b2)
		{
			if (a1 != b1)
			{
				return a1 < b1;
			}
			return a2 < b2;
		}
		
		bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
		{
			if (a1 != b1)
			{
				return a1 < b1;
			}
			return leq(a2, a3, b2, b3);
		}

		vector<int> rank() {
			
			int N = sa_.size();
			vector<int> ans(N, 0);
			for (int i = 0; i < N; i++)
			{
				ans[sa_[i]] = i;
			}
			return ans;
		}
	};


	class Solution {
	public:
		string lastSubstring(string s)
		{
			// converto char int
			int N = s.size();
			vector<int> nums(N, 0);

			// pre process
			int maxnum = INT_MIN;
			int minnum = INT_MAX;
			for (int i = 0; i < N; i++)
			{
				nums[i] = s[i];
				maxnum = std::max(maxnum, nums[i]);
				minnum = std::min(minnum, nums[i]);
			}

			for (int i = 0; i < N; i++)
			{
				nums[i] = nums[i] - minnum + 1;
			}
			DC3 dc3;
			dc3.reset(nums, maxnum - minnum + 1);
			int last = dc3.sa_[N-1];
			
			return s.substr(last);
		}
	};


}

void test_Code01_LastSubstringInLexicographicalOrder() {

	cout << "test_Code01_LastSubstringInLexicographicalOrder begin" << endl;
	Code01_LastSubstringInLexicographicalOrder::Solution sln;
	string input = "jlidhumidloagrlvvxdqscegbeaybfhhyaeilzxdpyvvxixrjytdalknkospradmumysbkizziltzjwsxkteykblcvkfivzmtvnsyrfgvojhyzkouscymixrdfmehiwijntzqptqaxgalygtzvwxnsgcnygbjzeqmbactgmckvssvkentpxcnznrbbnkttnzpvlzfmdvvsozaiycumzlizbfxvyucyagclrifczcvzvrkiqiajindjjyxgxflnjcgckruujsbppxtwgwvrrxgniqplynvboqyvrsxnmbjhgoybqophbxmjhhrznezstujjuucvrrvofktxldxfaioyijoayggmvjmgzjflzxmkwxmxnyizampdcfntdfkxxprgfxjduiwrmgdfuprpljgnbzbedqbzhqsbmohbhlszvdzcgbimfurmkwqaignxbeevevonmdgupugcjxvqglqkwqzrlqequliwmfrvidtpprodcbhgkt";
	//string input = "mississippi";// Mississippi
	string ans = sln.lastSubstring(input);
	cout << ans << endl;
	cout << "test_Code01_LastSubstringInLexicographicalOrder end" << endl;
}

#endif