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
	Graph(std::vector<std::unique_ptr<LabelBase>> V,
		std::vector<std::array<LabelBase*, 2>> E);
	Graph(Index n, const std::vector<std::array<Index, 2>>& indexPairs);

	inline Index size() const {
		return m_V.size();
	}
	inline GraphEventHandler& GetEventHandler() {
		return m_eventHandler;
	}

	void Update();
	void Draw() const;
	bool InsertVertex(std::unique_ptr<LabelBase> pLabel);
	bool InsertEdge(LabelBase* pLabel0, LabelBase* pLabel1);
	Vertex* LocateVertexAt(const Point2& pt) const;

	const std::vector<std::array<const LabelBase*, 2>> GetEdgeLabels() const;
private:
	void Init(std::vector<std::unique_ptr<LabelBase>> V,
			std::vector<std::array<LabelBase*, 2>> E);
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

