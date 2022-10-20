#pragma once
#ifndef Code02_ConvertToLetterString_HPP
#define Code02_ConvertToLetterString_HPP
#include <string>
#include <iostream>
#include "utility_func.hpp"
using namespace std;

namespace Code02_ConvertToLetterString  {

	int process(string & arr, int index);
	 // str只含有数字字符0~9
     // 返回多少种转化方案
	 int number(string & str) {
		if (str.size() == 0) {
			return 0;
		}
		return process(str, 0);
	 }
	 int process(string & arr, int index) {
		 if (index == arr.size())
		 {
			 return 1;
		 }
		 if (arr[index] == '0')
		 {
			 return 0;
		 }
		 int ways = process(arr, index + 1);
		 if (index + 1 < arr.size() &&
			 ((arr[index] - '0') * 10 + arr[index + 1] - '0') < 27
			 )
		 {
			 ways += process(arr, index + 2);
		 }
		 return ways;
	 }

	 int dpnumber(string & arr)
	 {
		 size_t N = arr.size();
		 vector<int> dp(N+1, 0);
		 dp[N] = 1;

		 for (int index = N - 1; index >= 0; index--)
		 {
			 if (arr[index] == '0')
			 {
				 dp[index] = 0;
			 }
			 else
			 {
				 int ways = dp[index + 1];
				 if (index + 1 < N &&
					 ((arr[index] - '0') * 10 + arr[index + 1] - '0') < 27
					 )
				 {
					 ways += dp[index + 2];
				 }
				 dp[index] = ways;
			 }
			
		 }
		 return dp[0];
	 }
	 // 倒着来
	 int process1(string & str, int index)
	 {
		 if (index == 0)
		 {
			 return 1;
		 }
		 // 如果 index 位置 = '0'
		 //int ways;
		 if (str[index] == '0')
		 {
			 // 找 index -1 的位置看能不能凑成有效的数字
			 if (index - 1 >= 0 && (str[index - 1] != '0')
				 &&((str[index - 1] - '0') * 10 < 27))
			 {
				 // 可以凑成有效数字
				 if (index - 2 >= 0)
				 {
					 return process1(str,index-2);
				 }
				 else
				 {
					 return 1;
				 }
			 }
			 else {
				 return 0;
			 }
			
		 }
		 else // str[index] != '0'
		 {
			 int ways = 0;
			 ways += process1(str, index-1);
			 // 找 index -1 的位置看能不能凑成有效的数字
			 if (index - 1 >= 0 && (str[index - 1] != '0')
				 && (((str[index - 1] - '0') * 10 + 
					 str[index]-'0') < 27))
			 {
				 if (index - 2 >= 0)
				 {
					 ways += process1(str, index - 2);
				 }
				 else // index-2<0 index = [0,1]
				 {
					 return ways + 1;
				 }
			 }
			 return ways;

		 }
	 }

	 int number1(string & str) {
		 if (str.size() == 0 || str[0] == '0') {
			 return 0;
		 }
		 return process1(str, str.size() -1);
	 }

}


void test_Code02_ConvertToLetterString()
{
	cout << "test Code02_ConvertToLetterString" << endl;
	int N = 5;
	char minchar = '0';
	char maxchar = '9';
	int test_loop = 15;
	while (test_loop > 0)
	{
		test_loop--;
		string res = generatestr(N, minchar, maxchar);
		//string res = "148";//"21";
		cout << "input : " << res << endl;
		//int num = Code02_ConvertToLetterString::number(res);
		int dpnum = Code02_ConvertToLetterString::dpnumber(res);
		int num1 = Code02_ConvertToLetterString::number1(res);
		//cout << "number:" <<num << endl;
		cout << "db number:" << dpnum << endl;
		cout << "num1:" << num1 << endl;
		if (num1 != dpnum)
		{
			cout << "fail to compute" << endl;
			cout << "str input : " << res << endl;
		}

	}
	
	
}



#endif