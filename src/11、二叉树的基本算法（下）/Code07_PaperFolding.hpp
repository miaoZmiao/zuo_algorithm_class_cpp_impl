#pragma once

#include "treeNode.hpp"

namespace Code07_PaperFolding {

	class PaperFolding {
	public:
		void printAllFolds(int N) {
			process(1, N, true);
			cout << endl;
		}

		void process(int i, int N, bool down) {
			if (i > N) {
				return;
			}
			process(i + 1, N, true);
			cout<<(down ? "°¼ " : "Í¹ ");
			process(i + 1, N, false);
		}
	};

	void test_main() {
		int N = 4;
		PaperFolding pf;
		pf.printAllFolds(N);
	}

}

void test_Code07_PaperFolding() {
	cout << "test_Code07_PaperFolding begin" << endl;
	Code07_PaperFolding::test_main();
	cout << "test_Code07_PaperFolding end" << endl;
}
