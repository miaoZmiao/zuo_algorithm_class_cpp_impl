#pragma once
#ifndef __NODE_H__
#define __NODE_H__
#include "edge.h"
#include <vector>

using namespace std;

class Node
{
public:
	int id;
	int value;
	int in = 0;
	int out = 0;
	std::vector<Node*> nexts;
	std::vector<Edge> edges;
};



#endif