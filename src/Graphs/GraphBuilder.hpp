#pragma once
#include "Basics/Basics.hpp"
#include "Graphs/Graph.hpp"

class GraphBuilder {
public:
	static std::unique_ptr<Graph> IndependentVertices(Index n);
	static std::unique_ptr<Graph> Path(Index n);
	static std::unique_ptr<Graph> Cycle(Index n);
	static std::unique_ptr<Graph> Star(Index n);
	static std::unique_ptr<Graph> Complete(Index n);
	static std::unique_ptr<Graph> BipartiteComplete(Index k1, Index k2);
	static std::unique_ptr<Graph> Cube(Index dim);
	static std::unique_ptr<Graph> Cross(Index dim);
	static std::unique_ptr<Graph> Kneser(Index n, Index k);

	static std::unique_ptr<Graph> Dual(const Graph& G);
	static std::unique_ptr<Graph> Union(const Graph& G1, const Graph& G2);
	static std::unique_ptr<Graph> DisjointUnion(const Graph& G1, const Graph& G2);
};
