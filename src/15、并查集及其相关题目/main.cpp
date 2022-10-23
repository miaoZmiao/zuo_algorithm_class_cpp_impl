#include "utility_func.hpp"
#include "Code01_FriendCircles.hpp"
#include "Code02_NumberOfIslands.hpp"
#include "Code03_NumberOfIslandsII.hpp"
void test_FriendCircles()
{
	cout << "test_FriendCircles begin" << endl;
	int N = 20;
	int minvalue = 0;
	int maxvalue = 1;
	int diag = 1;
	auto matrix = generate_symmetric_matrix(N, minvalue, maxvalue, diag);
	printMatrix(matrix);
	Solution sln;

	int ret_set = sln.findCircleNum(matrix);

	cout << "set_num = "<< ret_set << endl;
	cout << "test_FriendCircles end" << endl;
}

void test_NumberOfIslands()
{
	cout << "test_NumberOfIslands begin" << endl;
	int N = 4;
	char minvalue = '0';
	char maxvalue = '1';
	int diag = 1;
	auto matrix = generate_char_matrix(N, minvalue, maxvalue, diag);
	printMatrix(matrix);

	Solution2 sln;
	int ret_set = sln.numIslands(matrix);
	cout << "set_num = " << ret_set << endl;
	cout << "test_NumberOfIslands end" << endl;

}


void test_NumberOfIslandsII()
{
	cout << "test_NumberOfIslandsII begin" << endl;
	int N = 5;
	int M = 5;
	char minvalue = '0';
	char maxvalue = '1';
	int diag = 1;
	auto matrix = generate_char_matrix(N, minvalue, maxvalue, diag);
	/*vector<vector<char>> matrix = {
		{'1','1','1','1'},
		{'1','1','0','0'},
		{'0','0','1','1'},
		{'1','1','1','1'} };*/


	printMatrix(matrix);

	vector<vector<int>> positions;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int col = 0; col < matrix[0].size(); col++)
		{
			if (matrix[row][col] == '1')
			{
				vector<int> p{ row , col};
				positions.push_back(p);
			}
		}
	}

	Solution3 sln;
	auto retvec = sln.numIslands2(M, N, positions);

	print(retvec);
	cout << "test_NumberOfIslandsII end" << endl;
}





int main()
{
	test_FriendCircles();
	test_NumberOfIslands();

	test_NumberOfIslandsII();

	char c;
	cin >> c;
	return 0;

}

