#pragma once
#include "Basics.hpp"
#include "Graph.hpp"

class GraphBuilder {
public:
	static std::unique_ptr<Graph> Path(Index n);
	static std::unique_ptr<Graph> Cycle(Index n);
	static std::unique_ptr<Graph> Complete(Index n);
	static std::unique_ptr<Graph> BipartiteComplete(Index k1, Index k2);
	static std::unique_ptr<Graph> Cube(Index dim);
	static std::unique_ptr<Graph> Cross(Index dim);
	static std::unique_ptr<Graph> Kneser(Index n, Index k);
	static std::unique_ptr<Graph> DisjointUnion(const Graph& G1, const Graph& G2);
};
