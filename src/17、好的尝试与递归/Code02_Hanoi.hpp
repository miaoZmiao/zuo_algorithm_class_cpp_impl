#pragma once
#ifndef Code02_Hanoi_HPP
#define Code02_Hanoi_HPP
#include <iostream>
#include <string>
#include <stack>
using namespace  std;

void LeftToRight(int n);
void LeftToMid(int n);
void MidToRight(int n);
void MidToLeft(int n);
void RightToMid(int n);
void RightToLeft(int n);


void hanoi1(int n)
{
	LeftToRight(n);
	
}

// 请把1~N层圆盘 从左 -> 右
void LeftToRight(int n)
{
	if (n == 1)
	{
		cout << "move 1 from left to right" << endl;
		return;
	}
	LeftToMid(n - 1);
	cout << "move "<<n<<" from left to right" << endl;
	MidToRight(n - 1);
}

// 请把1~N层圆盘 从左 -> 中
void LeftToMid(int n)
{
	if (1 == n)
	{
		cout << "move 1 from left to mid" << endl;
		return;
	}
	LeftToRight(n - 1);
	cout << "move " << n << " from left to mid" << endl;
	RightToMid(n - 1);
}


void RightToMid(int n)
{
	if (1 == n)
	{
		cout << "move 1 from right to mid" << endl;
		return;
	}
	RightToLeft(n-1);
	cout << "move " << n << "from right to mid" << endl;
	LeftToMid(n-1);
}

void MidToRight(int n)
{
	if (n == 1)
	{
		cout << "move 1 from mid to right" << endl;
		return;
	}
	MidToLeft(n-1);
	cout << "move " << n << " from mid to right" << endl;
	LeftToRight(n-1);
}

void MidToLeft(int n) 
{
	if (n == 1)
	{
		cout << "move 1 from mid to left" << endl;
		return;
	}
	MidToRight(n - 1);
	cout << "move " << n << " from mid to left" << endl;
	RightToMid(n - 1);
}

void RightToLeft(int n)
{
	if (n == 1)
	{
		cout << "move 1 from right to left" << endl;
		return;
	}
	RightToMid(n - 1);
	cout << "move " << n << " from right to left" << endl;
	MidToLeft(n - 1);
}

void func(int N,
	const string & from, const string & mid, const string & to)
{
	if (N == 1)
	{
		cout << "move 1 from " << from << " to " << to << endl;
		return;
	}
	func(N - 1, from, to, mid);
	cout << "move " << N << " from " << from << " to " << to << endl;
	func(N - 1, mid, from, to);

}

void hanoi2(int N)
{
	func(N, "left", "mid", "right");
}

struct Record
{
	Record(int n, int s = 0) {
		N = n;
		Stage = s;
	}
	int Stage;
	int N;
	std::string from;
	std::string mid;
	std::string to;
};


// 此方法和老师讲的不一样
// 是自己总结出来的递归套路之一
// 用此思想，可以实现二叉树的非递归遍历
void hanoi3(int N)
{
	std::stack<Record> st;
	Record rec(N);
	rec.from = "left";
	rec.mid = "mid";
	rec.to = "right";
	st.push(rec);
	while (!st.empty())
	{
		Record cur = st.top();

		if (cur.N == 1)
		{
			cout << "move 1 from " << cur.from << " to " << cur.to << endl;
			st.pop();
			continue;
		}
		// cur.N > 1
		if (cur.Stage == 0)
		{
			// push
			Record tmpRec(cur.N -1);
			tmpRec.from = cur.from;
			tmpRec.to = cur.mid;
			tmpRec.mid = cur.to;
			st.top().Stage = 1;
			st.push(tmpRec);
		}
		else if (cur.Stage == 1)
		{
			cout << "move " << cur.N << " from " << cur.from << 
				" to " << cur.to << endl;
			st.top().Stage = 2;
		}
		else if (cur.Stage == 2)
		{
			// push
			Record tmpRec(cur.N - 1);
			tmpRec.from = cur.mid;
			tmpRec.mid = cur.from;
			tmpRec.to = cur.to;
			st.top().Stage = 3;
			st.push(tmpRec);
		}
		else if (st.top().Stage == 3)
		{
			st.pop();
		}
	}
	return;

}




#endif