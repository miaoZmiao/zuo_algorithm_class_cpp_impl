#pragma once
#include "utility_func.hpp"
#include <algorithm>
#include <queue>
namespace Code01_CoverMax {

	class CoverMax {

	public:
		int maxCover1(vector<vector<int>> & lines)
		{
			int min = INT_MAX;
			int max = INT_MIN;
			for (int i = 0; i < lines.size(); i++) {
				min = std::min(min, lines[i][0]);
				max = std::max(max, lines[i][1]);
			}
			int cover = 0;
			for (double p = min + 0.5; p < max; p += 1) {
				int cur = 0;
				for (int i = 0; i < lines.size(); i++) {
					if (lines[i][0] < p && lines[i][1] > p) {
						cur++;
					}
				}
				cover = std::max(cover, cur);
			}
			return cover;
		}

		struct Line {
			int start;
			int end;
			Line(int s = 0, int e = 0) {
				start = s;
				end = e;
			}
		};

		int maxCover2(vector<vector<int>> & m) {
		
			vector<Line> lines(m.size());
			for (int i = 0; i < m.size(); i++) {
				lines[i].start = m[i][0];
				lines[i].end = m[i][1];
			}
			std::sort(lines.begin(), lines.end(), [] (const Line& left, const Line& right){
				return left.start < right.start;
			});

			std::priority_queue<int, vector<int>, std::greater<int>> pq;
			int max = 0;
			for (int i = 0; i < lines.size(); i++) {
				// lines[i] -> cur  在黑盒中，把<=cur.start 东西都弹出
				while (!pq.empty() && pq.top() <= lines[i].start) {
					pq.pop();
				}
				pq.push(lines[i].end);
				max = std::max((size_t)max, pq.size());
			}
			return max;

		}

		vector<vector<int>> generateLines(int N, int L, int R) {

			std::random_device  rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<> dist(0.0, 1.0);
			int size = (int)(dist(mt) * N) + 1;
			vector<vector<int>> ans(size, vector<int>(2));
			for (int i = 0; i < size; i++) {
				int a = L + (int)(dist(mt) * (R - L + 1));
				int b = L + (int)(dist(mt) * (R - L + 1));
				if (a == b) {
					b = a + 1;
				}
				ans[i][0] = std::min(a, b);
				ans[i][1] = std::max(a, b);
			}
			return ans;
		}

		void test_case() {
			
			int N = 100;
			int L = 0;
			int R = 200;
			int testTimes = 2000;
			for (int i = 0; i < testTimes; i++) {
				vector<vector<int>> lines = generateLines(N, L, R);
				int ans1 = maxCover1(lines);
				int ans2 = maxCover2(lines);
				if (ans1 != ans2) {
					cout<<"Oops!"<<endl;
					break;
				}
			}
			
		
		}

	};
}

using Code01_CoverMax::CoverMax;

void test_Code01_CoverMax()
{

	cout << "test_Code01_CoverMax begin" << endl;
	CoverMax cm;
	cm.test_case();
	cout << "test_Code01_CoverMax end" << endl;
}