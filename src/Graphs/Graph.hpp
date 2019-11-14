#pragma once
#include "Basics/Basics.hpp"
#include "Basics/PtrUnorderedSet.hpp"

#include "Basics/Shapes.hpp"
#include "Graphs/Vertex.hpp"
#include "Graphs/Edge.hpp"
#include "Graphs/GraphEventHandler.hpp"

using VertexSet = PtrUnorderedSet<Vertex>;
using EdgeSet = PtrUnorderedSet<Edge>;

class Graph {
public:
	Graph(const std::vector<constLabel>& labels, const std::vector<std::array<constLabel, 2>>& labelPairs);
	template<class Name> Graph(const std::vector<Name>& rawLabels, const std::vector<std::array<Name, 2>>& rawLabelPairs)
			: m_V(), m_E(), m_eventHandler(this) {
		m_V.reserve(rawLabels.size());
		for(const auto& rawLabel : rawLabels) {
			auto oLabel = Label<Name>(rawLabel);
			assert(InsertVertex(&oLabel));
		}
		ArrangeVerticesAtCircle();
		m_E.reserve(rawLabelPairs.size());
		for(const auto& rawLabelPair : rawLabelPairs) {
			auto oLabel0 = Label<Name>(rawLabelPair[0]);
			auto oLabel1 = Label<Name>(rawLabelPair[1]);
			assert(InsertEdge({ &oLabel0, &oLabel1 }));
		}
	}
	Graph(Index n, const std::vector<std::array<Index, 2>>& rawLabelPairs);

	Graph(const std::vector<std::unique_ptr<LabelBase>> labels, const std::function<bool(constLabel, constLabel)> binRelation);
	Graph(const std::vector<constLabel>& labels, const std::function<bool(constLabel, constLabel)> binRelation);
	template<class Name> Graph(const std::vector<Name>& rawLabels, const std::function<bool(const Name&, const Name&)> rawBinRelation)
			: m_V(), m_E(), m_eventHandler(this) {
		m_V.reserve(rawLabels.size());
		for(const auto& rawLabel : rawLabels) {
			auto oLabel = Label<Name>(rawLabel);
			assert(InsertVertex(&oLabel));
		}
		ArrangeVerticesAtCircle();
		for(const auto& rawLabel0 : rawLabels) {
			for(const auto& rawLabel1 : rawLabels) {
				if(rawBinRelation(rawLabel0, rawLabel1)) {
					auto oLabel0 = Label<Name>(rawLabel0);
					auto oLabel1 = Label<Name>(rawLabel1);
					assert(InsertEdge({ &oLabel0, &oLabel1 }));
				}
			}
		}
	}
	Graph(Index n, const std::function<bool(Index, Index)> rawBinRelation);

	inline Index size() const { return m_V.size(); }
	inline GraphEventHandler& GetEventHandler() { return m_eventHandler; }

	double Density() {
		return 2 * m_E.size() / (size() * (size() - 1));
	}

	void Update();
	void Draw() const;

	bool IsVertex(constLabel label) const;
	bool IsEdge(const std::array<constLabel, 2> labelPair) const;

	const std::vector<constLabel> GetVertexLabels() const;
	const std::vector<std::array<constLabel, 2>> GetEdgeLabels() const;

	Vertex* LocateVertexAt(const Point2& pt) const;
private:
	bool InsertVertex(constLabel rawLabel);
	bool InsertEdge(const std::array<constLabel, 2>& rawLabelPair);

	std::optional<Vertex*> FindVertex(constLabel rawLabel) const;

	void ArrangeVerticesAtCircle(double r=0.5);
	void MakeVerticesRepelEachOther(double intensity);
	void MakeEdgesTryToKeepFixedDist(double dist, double intensity);
	void MakeVerticesBeRepelledFromBoundary(double intensity);
	void MakeVerticesBeDamped(double intensity);
	void LockVertexIfNeeded();
	void UpdateAllNodes();

	VertexSet m_V;
	EdgeSet m_E;
	GraphEventHandler m_eventHandler;
};

