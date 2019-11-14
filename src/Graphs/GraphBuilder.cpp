#include "Graphs/GraphBuilder.hpp"
#include "Basics/Math.hpp"
#include "Graphs/LabelBuilder.hpp"

template<class Name> using binRelation = std::function<bool(const Name&, const Name&)>;
template<class Name, typename F> binRelation<Name> makeRelation(F f) { return static_cast<binRelation<Name>>(f); }

std::unique_ptr<Graph> GraphBuilder::IndependentVertices(Index n) {
	return std::make_unique<Graph>(n, [](const auto&, const auto&) { return false; });
}


std::unique_ptr<Graph> GraphBuilder::Path(Index n) {
	return std::make_unique<Graph>(n+1, [](const auto& i, const auto& j) { return i+1 == j; });
}


std::unique_ptr<Graph> GraphBuilder::Cycle(Index n) {
	return std::make_unique<Graph>(n, [n](const auto& i, const auto& j) { return (i+1) % n == j % n; });
}


std::unique_ptr<Graph> GraphBuilder::Star(Index n) {
	return std::make_unique<Graph>(n+1, [](const auto& i, const auto& j) { return i == 0 && j != i; });
}


std::unique_ptr<Graph> GraphBuilder::Complete(Index n) {
	return std::make_unique<Graph>(n, [](const auto& i, const auto& j) { return i < j; });
}


std::unique_ptr<Graph> GraphBuilder::BipartiteComplete(Index k1, Index k2) {
	using Name = std::pair<Index, Index>;
	std::vector<Name> labels;
	labels.reserve(k1 + k2);
	for(Index i = 0; i < k1; ++i)
		labels.push_back(std::make_pair(0, i));
	for(Index i = 0; i < k2; ++i)
		labels.push_back(std::make_pair(1, i));
	return std::make_unique<Graph>(labels, makeRelation<Name>([](const auto& i, const auto& j) { return i.first < j.first; }));
}


std::unique_ptr<Graph> GraphBuilder::Cube(Index dim) {
	return std::make_unique<Graph>(Math::powOf2(dim), [](const auto& i, const auto& j) { return i<j && Math::isPowOf2( j ^ i );});
}


std::unique_ptr<Graph> GraphBuilder::Cross(Index dim) {
	using Name = std::pair<bool, Index>;
	std::vector<Name> labels;
	labels.reserve(2 * dim);
	for(Index i = 0; i < dim; ++i) {
		labels.push_back(std::make_pair(true, i));
		labels.push_back(std::make_pair(false, i));
	}
	return std::make_unique<Graph>(labels, makeRelation<Name>([](const auto& i, const auto& j) { return i.second < j.second; }));
}


//std::unique_ptr<Graph> GraphBuilder::Kneser(Index n, Index k) {
//}


std::unique_ptr<Graph> GraphBuilder::Dual(const Graph& G) {
	return std::make_unique<Graph>(G.GetVertexLabels(), [&G](const auto& label0, const auto& label1) {
		return !label0->IsEqual(label1) && !G.IsEdge( {label0, label1} );
	});
}

std::unique_ptr<Graph> GraphBuilder::Union(const Graph& G1, const Graph& G2) {
	const auto labels1 = G1.GetVertexLabels();
	const auto labels2 = G2.GetVertexLabels();
	std::vector<constLabel> labels;
	labels.reserve(labels1.size() + labels2.size());
	labels.insert(labels.end(), labels1.begin(), labels1.end());
	labels.insert(labels.end(), labels2.begin(), labels2.end());
	return std::make_unique<Graph>(labels, [&G1, &G2](const auto& label0, const auto& label1) {
		return G1.IsEdge( {label0, label1} ) || G2.IsEdge( {label0, label1} );
	});
}

std::unique_ptr<Graph> GraphBuilder::DisjointUnion(const Graph& G1, const Graph& G2) {
	const auto labels1 = G1.GetVertexLabels();
	const auto labels2 = G2.GetVertexLabels();
	std::vector<std::unique_ptr<LabelBase>> labels;
	labels.reserve(labels1.size() + labels2.size());
	for(const auto& label : labels1) {
		labels.push_back(std::move(label->cloneAndAddExtraInfo(0)));
		//labels.push_back(std::move(LabelBuilder::CloneLabelAndAddInfo(*label, 0)));
	}
//	for(const auto& label : labels1) {
//		labels.push_back(std::move(LabelBuilder::CloneLabelAndAddInfo(*label, 1)));
//	}
	return std::make_unique<Graph>(std::move(labels), [&G1, &G2](const auto& label0, const auto& label1) {
		return G1.IsEdge( {label0, label1} ) || G2.IsEdge( {label0, label1} );
	});
}

//std::unique_ptr<Graph> GraphBuilder::DisjointUnion(const Graph& G1, const Graph& G2) {
//	const std::vector<std::array<Index, 2>>& labelPairs1 = G1.GetEdgeLabels();
//	Index n1 = G1.size();
//	const std::vector<std::array<Index, 2>>& labelPairs2 = G2.GetEdgeLabels();
//	Index n2 = G2.size();
//	std::vector<std::array<Index, 2>> labelPairs = labelPairs1;
//	for(const auto& edgePair : labelPairs2)
//		labelPairs.push_back( { edgePair[0] + n1, edgePair[1] + n1 });
//	return std::make_unique<Graph>(n1+n2, labelPairs);
//}

