#pragma once
#ifndef Code03_StickersToSpellWord_HPP
#define Code03_StickersToSpellWord_HPP
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
using namespace  std;

namespace Code03_StickersToSpellWord {

	int process1(vector<vector<int>> & stickers_wf,
		vector<int> &  target_wf);

	vector<int> pre_process(const std::string & str)
	{
		vector<int> wf(26, 0);
		for (auto & c : str)
		{
			wf[c-'a']++;
		}
		return wf;
	}
	
	int minStickers1(vector<string>& stickers, string target) {

		// 把 target 和 sticker 全转换成 词频表数组形式
		vector<int> target_wf = pre_process(target);
		
		vector<vector<int>> stickers_wf(stickers.size());

		for (int i=0;i< stickers.size();i++)
		{
			stickers_wf[i] = pre_process(stickers[i]);
		}
		int ans = process1(stickers_wf, target_wf);
		return ans == INT_MAX ? -1 : ans;
	}
	// 通过词频判断是否为空
	bool judge_empty_wf(vector<int> &  target_wf);

	// 通过词频表判断连个字符串是否有交集
	bool judge_same_char(vector<int> sticker_wf,
		vector<int> & target_wf);

	// 所有贴纸stickers，每一种贴纸都有无穷张
	// target
	// 最少张数
	int process1(vector<vector<int>> & stickers_wf, 
		vector<int> &  target_wf) 
	{
		// base case
		if (judge_empty_wf(target_wf))
		{
			return 0;
		}
		int ways = INT_MAX;
		for (int i = 0; i < stickers_wf.size(); i++)
		{
			vector<int> current_target_wf = target_wf;
			if (false == judge_same_char(
				stickers_wf[i], current_target_wf))
			{
				continue;
			}
			// substract 
			for (int c = 0; c < 26; c++)
			{
				if (current_target_wf[c] != 0 && stickers_wf[i][c] != 0)
				{
					if (stickers_wf[i][c] > current_target_wf[c])
					{
						current_target_wf[c] = 0;
					}
					else
					{
						current_target_wf[c] =
							current_target_wf[c] - stickers_wf[i][c];
					}
				}
			}
			ways = std::min(ways, process1(stickers_wf,current_target_wf));
		}
		return ((ways == INT_MAX )? INT_MAX : ways + 1);
	}

	bool judge_empty_wf(vector<int> &  target_wf)
	{
		for (int i = 0; i < target_wf.size(); i++)
		{
			if (target_wf[i] != 0)
			{
				return false;
			}
		}
		return true;
	}

	bool judge_same_char(vector<int> sticker_wf,  
		vector<int> & target_wf) 
	{
		for (int i = 0; i < 26; i++)
		{
			if (target_wf[i] != 0 && sticker_wf[i] != 0)
			{
				return true;
			}
		}
		return false;
	}


	std::string mins(vector<int> & sticker_wf, vector<int> & target_wf);

	// 暴力递归没法用，那么只能想办法用傻缓存

	int dpways(vector<vector<int>> & stickers_wf, const string & target, map<string, int> & dp)
	{
		if (target.empty())
		{
			return 0;
		}
		// !target.empty()
		auto itFind = dp.find(target);
		if (itFind != dp.end())
		{
			return itFind->second;
		}
		int ways = INT_MAX;
		
		vector<int> target_wf = pre_process(target);
		for (int i = 0; i < stickers_wf.size(); i++)
		{
			
			if (stickers_wf[i][target[0] - 'a'] > 0)
			{
				string nexttarget = mins(stickers_wf[i], target_wf);

				ways = std::min(ways, dpways(stickers_wf, nexttarget, dp));

			}
		}
		ways = (ways == INT_MAX ? INT_MAX : ways + 1);
		dp[target] = ways;
		return ways;
	}

	std::string mins(vector<int> & sticker_wf, vector<int> & target_wf)
	{
		string res;
		for (int i = 0; i < 26; i++)
		{
			if (sticker_wf[i] >= target_wf[i])
			{
				continue;
			}
			else // sticker_wf[i] < target_wf[i]
			{
				int n = target_wf[i] - sticker_wf[i];
				while (n > 0)
				{
					res.push_back('a' + i);
					n--;
				}
			}
		}
		return res;
	}

	int minStickers2(vector<string>& stickers, string target) {

		// 把 target 和 sticker 全转换成 词频表数组形式
		//vector<int> target_wf = pre_process(target);

		vector<vector<int>> stickers_wf(stickers.size());

		for (int i = 0; i < stickers.size(); i++)
		{
			stickers_wf[i] = pre_process(stickers[i]);
		}
		map<string, int> dp;

		int ans = dpways(stickers_wf, target, dp);
		return ans == INT_MAX ? -1 : ans;
	}

}

// 本题测试链接：
// https://leetcode.com/problems/stickers-to-spell-word


void test_Code03_StickersToSpellWord()
{
	//["summer", "sky", "cent", "bright", "kill", "forest", "neighbor", "capital", "tall"]
	//"originalchair"
	vector<string> stickers{ "summer", 
		"sky", "cent", "bright", "kill", "forest", "neighbor", "capital", "tall" };
	string target = "originalchair";
	// minStickers1 leetcode  测试超时
	int ret1 = Code03_StickersToSpellWord::minStickers1(stickers, target);
	// minStickers2  leetcode 测试通过
	int ret2 = Code03_StickersToSpellWord::minStickers2(stickers, target);

}


#endif