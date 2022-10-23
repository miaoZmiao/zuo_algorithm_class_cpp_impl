#include <iostream>
#include "Code02_Hanoi.hpp"
#include "Code03_PrintAllSubsquences.hpp"
#include "Code04_PrintAllPermutations.hpp"
#include "Code05_ReverseStackUsingRecursive.hpp"
using namespace std;

void test_hanoi1()
{
	cout << "test case : hanoi1 begin" << endl;
	hanoi1(3);
	cout << "test case : hanoi1 end" << endl;
}

void test_hanoi2()
{
	cout << "test case : hanoi2 begin" << endl;
	hanoi2(3);
	cout << "test case : hanoi2 end" << endl;
}

void test_hanoi3()
{
	cout << "test case : hanoi3 begin" << endl;
	hanoi3(3);
	cout << "test case : hanoi3 end" << endl;
}

void test_subs()
{
	string input = "abcd";
	vector<string> ret = PrintAllSubsquences::subs(input);
	for (auto & it : ret)
	{
		cout << it << endl;
	}
}

void test_subsNoRepeat()
{
	string input = "abbc";
	cout << "test_subsNoRepeat begin" << endl;
	vector<string> ret = PrintAllSubsquences::subsNoRepeat(input);
	for (auto & it : ret)
	{
		cout << it << endl;
	}
	cout << "test_subsNoRepeat end" << endl;
}


int main()
{
	
	test_hanoi1();
	test_hanoi2();
	test_hanoi3();
	test_subsNoRepeat();
	test_permutation();
	test_Code05_ReverseStackUsingRecursive();
	char c;
	cin >> c;
	return 0;
}