#pragma once
#ifndef __EDGE_H__
#define __EDGE_H__



struct Edge
{
public:
	Edge() {}
	Edge(int w, int f, int t):
		weight(w),
		from(f),
		to(t)
	{
	
	}
	int from = 0;
	int to = 0;
	int weight = 0;

	bool operator==(const Edge & other) const
	{
		if (this->from == other.from)
		{
			return this->to == other.to;
		}
		return false;
	}

};


#endif