#pragma once
#ifndef __GRAPH_GENERATOR_HPP__
#define __GRAPH_GENERATOR_HPP__
#include "utility_func.hpp"
#include "graph.h"

Graph generate_Graph(int NodeNum, 
	int minweight, int maxweight, 
	int minvalue = 1, int maxvalue= 10)
{
	
	vector<vector<int>> matrix = generate_N_3_matrix(NodeNum, minweight, maxweight);
	
	printMatrix(matrix);
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(minvalue, maxvalue);
	Graph ret;
	
	auto make_node = [&](int id) -> Node*{
		Node * tmpNode = nullptr; 
		tmpNode = new Node;
		tmpNode->id = id;
		tmpNode->value = dist(gen);
		return tmpNode;
	};


	Node* tmpFromNode = nullptr;
	Node * tmpToNode = nullptr;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		int weight = matrix[i][0];
		int from = matrix[i][1];
		int to = matrix[i][2];
		if (ret.nodes.find(from) == ret.nodes.end())
		{
			tmpFromNode = make_node(from);
			ret.nodes.insert(std::make_pair(from, tmpFromNode));
		}
		if (ret.nodes.find(to) == ret.nodes.end())
		{
			tmpToNode = make_node(to);
			ret.nodes.insert(std::make_pair(to, tmpToNode));
		}	
		Edge tmpEdge(weight, from, to);
		ret.edges.insert(tmpEdge);
		
		tmpFromNode->out++;
		tmpToNode->in++;
		tmpFromNode->nexts.push_back(tmpToNode);
		tmpFromNode->edges.push_back(tmpEdge);
	}

	return ret;
}






#endif