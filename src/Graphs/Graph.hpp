#pragma once
#include "Basics/Basics.hpp"

#include "Basics/Shapes.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Graphs/GraphEventHandler.hpp"

using VertexSet = std::unordered_set<
			std::unique_ptr<Vertex>,
			std::hash<std::unique_ptr<Vertex>>,
			Unique_Ptr_Eq<Vertex>>;

using EdgeSet = std::unordered_set<
			std::unique_ptr<Edge>,
			std::hash<std::unique_ptr<Edge>>,
			Unique_Ptr_Eq<Edge>>;

class Graph {
public:
	Graph(const std::vector<constLabel>& labels, const std::vector<std::array<constLabel, 2>>& labelPairs);
	template<class Name> Graph(const std::vector<Name>& rawLabels, const std::vector<std::array<Name, 2>>& rawLabelPairs);
	Graph(Index n, const std::vector<std::array<Index, 2>>& rawLabelPairs);

	Graph(const std::vector<constLabel>& labels, const std::function<bool(constLabel, constLabel)> binRelation);
	template<class Name> Graph(const std::vector<Name>& rawLabels, const std::function<bool(const Name&, const Name&)> rawBinRelation);
	Graph(Index n, const std::function<bool(Index, Index)> rawBinRelation);

	inline Index size() const { return m_V.size(); }
	inline GraphEventHandler& GetEventHandler() { return m_eventHandler; }

	double Density() {
		return 2 * m_E.size() / (size() * (size() - 1));
	}

	void Update();
	void Draw() const;

	bool IsVertex(constLabel label);
	bool IsEdge(const std::array<constLabel, 2> labelPair);

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

