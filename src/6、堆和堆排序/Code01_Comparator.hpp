#pragma once

#include <string>
#include "utility_func.hpp"
#include <algorithm>
#include <functional>
using namespace std;

namespace Code01_Comparator {

	struct  Student {
		 string name;
		 int id;
		 int age;

		 Student(string pname, int pid, int page) {
			this->name = pname;
			this->id = pid;
			this->age = page;
		 }
	};

	// compare方法里，遵循一个统一的规范：
	// id 从小到大
	// age 从大到小
	struct StudentCmp {
	
		bool operator()(const Student& left, const Student& right) const
		{
			if (left.id == right.id)
			{
				return left.age > right.age;
			}
			return left.id < right.id;
		}
	};

	void printStudents(vector<Student> & students) {
		for (int i = 0; i < students.size(); i++)
		{
			const auto & s = students[i];
			cout << s.name << "," << s.id << "," << s.age << endl;
		}
	}

	void test_(){
		vector<int> arr{  5, 4, 3, 2, 7, 9, 1, 0 }; 

		auto integer_cmp = [](int left, int right) {
			return left < right;
		};
		cout << "arr before sort" << endl;
		print(arr);
		cout << "arr after sort" << endl;
		std::sort(arr.begin(), arr.end(), integer_cmp);
		print(arr);
		cout << "===================" << endl;
		vector<Student> students{ 
			{"A", 4, 40},
			{"B", 4, 21}, {"C", 3, 12},{"D", 3, 62},
			{"E", 3, 42}
		}; 
		cout << "students before sort" << endl;
		printStudents(students);
		cout << "students after sort" << endl;
		std::sort(students.begin(), students.end(), StudentCmp());
		printStudents(students);


	}

}

void test_Code01_Comparator() {
	Code01_Comparator::test_();

}