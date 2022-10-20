#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "edge.h"
#include "node.h"
#include "anytype_hash_generate.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


struct EdgeHash
{
	size_t  operator()(const Edge & e) const 
	{
		return pair_hash()(std::make_pair(e.from, e.to));
	}

};

struct EdgeCompare
{

	bool operator()(const Edge & e1, const Edge & e2) const
	{
		if (e1.from == e2.from)
		{
			return e1.to < e2.to;
		}
		return e1.from < e2.from;
	}

};

struct EdgeEqual
{
	bool operator()(const Edge & e1, const Edge & e2) const
	{
		return e1 == e2;
	}

};



class Graph
{
	
public:
	unordered_map<int, Node*> nodes;
	unordered_set<Edge, EdgeHash, EdgeEqual> edges;


	void release() {
		for (auto & it : nodes)
		{
			delete it.second;
			it.second = nullptr;
		}
	
	}

};



#endif