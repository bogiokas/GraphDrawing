#include "GraphBuilder.hpp"

std::unique_ptr<Graph> GraphBuilder::IndependentVertices(Index n) {
	std::vector<std::array<Index, 2>> edgePairs;
	return std::make_unique<Graph>(n, edgePairs);
}
std::unique_ptr<Graph> GraphBuilder::Path(Index n) {
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < n; ++i) {
		edgePairs.push_back({i,i+1});
	}
	return std::make_unique<Graph>(n+1, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::Cycle(Index n) {
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < n-1; ++i) {
		edgePairs.push_back({i,i+1});
	}
	edgePairs.push_back({n-1,0});
	return std::make_unique<Graph>(n+1, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::Complete(Index n) {
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < n; ++i) {
		for(Index j = i+1; j < n; ++j) {
			edgePairs.push_back({i,j});
		}
	}
	return std::make_unique<Graph>(n, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::BipartiteComplete(Index k1, Index k2) {
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < k1; ++i) {
		for(Index j = k1; j < k1+k2; ++j) {
			edgePairs.push_back({i,j});
		}
	}
	return std::make_unique<Graph>(k1+k2, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::Cube(Index dim) {
	Index n = Math::powInd(2, dim);
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < n; ++i) {
		for(Index d = 0; d < dim; ++d) {
			if((i / Math::powInd(2,d)) % 2 == 0)
				edgePairs.push_back( {i,i+Math::powInd(2,d)} );
		}
	}
	return std::make_unique<Graph>(n, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::Cross(Index dim) {
	Index n = 2 * dim;
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < dim; ++i) {
		for(Index j = 0; j < 2*i; ++j) {
			edgePairs.push_back( {j,2*i} );
			edgePairs.push_back( {j,2*i+1} );
		}
	}
	return std::make_unique<Graph>(n, edgePairs);
}


std::unique_ptr<Graph> GraphBuilder::Kneser(Index n, Index k) {
	std::vector<std::array<Index, 2>> edgePairs;
	return std::make_unique<Graph>(n, edgePairs);
}



std::unique_ptr<Graph> GraphBuilder::Dual(const Graph& G) {
	Index n = G.size();
	auto edgePairsG = G.GetEdgeNames();
	std::vector<std::array<Index, 2>> edgePairs;
	for(Index i = 0; i < n; ++i) {
		for(Index j = i+1; j < n; ++j) {
			std::array<std::array<Index, 2>, 2> pairs;
			pairs[0] = {i,j};
			pairs[1] = {j,i};
			if(std::find_first_of(edgePairsG.begin(), edgePairsG.end(), pairs.begin(), pairs.end()) == edgePairsG.end())
				edgePairs.push_back({i,j});
		}
	}
	return std::make_unique<Graph>(n, edgePairs);
}

std::unique_ptr<Graph> GraphBuilder::DisjointUnion(const Graph& G1, const Graph& G2) {
	const std::vector<std::array<Index, 2>>& edgePairs1 = G1.GetEdgeNames();
	Index n1 = G1.size();
	const std::vector<std::array<Index, 2>>& edgePairs2 = G2.GetEdgeNames();
	Index n2 = G2.size();
	std::vector<std::array<Index, 2>> edgePairs = edgePairs1;
	for(const auto& edgePair : edgePairs2)
		edgePairs.push_back( { edgePair[0] + n1, edgePair[1] + n1 });
	return std::make_unique<Graph>(n1+n2, edgePairs);
}

