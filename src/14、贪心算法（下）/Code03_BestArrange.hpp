#pragma once
#include "utility_func.hpp"

namespace Code03_BestArrange {

	struct Program {
		int start;
		int end;

		Program(int s=0, int e=0) {
			start = s;
			end = e;
		}	
	};

	class BestArrange {
	public:
		// 暴力！所有情况都尝试！
		int bestArrange1(const vector<Program>& programs) {
			if (programs.size() == 0) {
				return 0;
			}
			return process(programs, 0, 0);
		}

		// 还剩下的会议都放在programs里
		// done之前已经安排了多少会议的数量
		// timeLine目前来到的时间点是什么

		// 目前来到timeLine的时间点，已经安排了done多的会议，剩下的会议programs可以自由安排
		// 返回能安排的最多会议数量
		int process(const vector<Program>& programs, int done, int timeLine) {
			if (programs.size() == 0) {
				return done;
			}
			// 还剩下会议
			int max = done;
			// 当前安排的会议是什么会，每一个都枚举
			for (int i = 0; i < programs.size(); i++) {
				if (programs[i].start >= timeLine) {
					vector<Program> next = copyButExcept(programs, i);
					max =std::max(max, process(next, done + 1, programs[i].end));
				}
			}
			return max;
		}

		vector<Program> copyButExcept(const vector<Program> &programs, int i) {
			vector<Program> ans(programs.size() - 1);
			int index = 0;
			for (int k = 0; k < programs.size(); k++) {
				if (k != i) {
					ans[index++] = programs[k];
				}
			}
			return ans;
		}

		struct ProgramComparator {
			bool operator()(const Program & o1, const Program & o2) const {
				return o1.end < o2.end;
			}
		};

		// 会议的开始时间和结束时间，都是数值，不会 < 0
		int bestArrange2(vector<Program>& programs) {
			std::sort(programs.begin(),programs.end(), ProgramComparator());
			int timeLine = 0;
			int result = 0;
			// 依次遍历每一个会议，结束时间早的会议先遍历
			for (int i = 0; i < programs.size(); i++) {
				if (timeLine <= programs[i].start) {
					result++;
					timeLine = programs[i].end;
				}
			}
			return result;
		}

	};

	// for test
	vector<Program> generatePrograms(int programSize, int timeMax) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0.0, 1.0);
		vector<Program> ans((int)(dist(mt) * (programSize + 1)));
		for (int i = 0; i < ans.size(); i++) {
			int r1 = (int)(dist(mt) * (timeMax + 1));
			int r2 = (int)(dist(mt) * (timeMax + 1));
			if (r1 == r2) {
				ans[i] = Program(r1, r1 + 1);
			}
			else {
				ans[i] = Program(std::min(r1, r2), std::max(r1, r2));
			}
		}
		return ans;
	}

	void test_main() {
		int programSize = 12;
		int timeMax = 20;
		int timeTimes = 1000;
		BestArrange ba;
		for (int i = 0; i < timeTimes; i++) {
			vector<Program> programs1 = generatePrograms(programSize, timeMax);
			vector<Program> programs2 = programs1;
			if (ba.bestArrange1(programs1) != ba.bestArrange2(programs2)) {
				cout << "Oops!" << endl;
				break;
			}
		}

	}

}

void test_Code03_BestArrange() {

	cout << "test_Code03_BestArrange begin" << endl;
	Code03_BestArrange::test_main();
	cout << "test_Code03_BestArrange end" << endl;

}