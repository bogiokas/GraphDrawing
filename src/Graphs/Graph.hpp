#pragma once
#include "Basics/Basics.hpp"

#include "Basics/Shapes.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Graphs/GraphEventHandler.hpp"

class Graph {
public:
	Graph(const std::vector<std::unique_ptr<LabelBase>> V,
		const std::vector<std::array<std::unique_ptr<LabelBase>, 2>> E);
	Graph(Index n, const std::vector<std::array<Index, 2>>& E);

	inline Index size() const {
		return m_V.size();
	}
	inline GraphEventHandler& GetEventHandler() {
		return m_eventHandler;
	}

	void Update();
	void Draw() const;
	Vertex* LocateVertexAt(const Point2& pt) const;

	const std::vector<std::array<const LabelBase*, 2>> GetEdgeLabels() const;
private:
	void MakeVerticesRepelEachOther(double intensity);
	void MakeEdgesTryToKeepFixedDist(double dist, double intensity);
	void LockVertexIfNeeded();
	void UpdateAllNodes();

	std::vector<std::unique_ptr<Vertex>> m_V;
	std::vector<std::unique_ptr<Edge>> m_E;
	GraphEventHandler m_eventHandler;
};

