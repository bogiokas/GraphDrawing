#pragma once
#include "Basics.hpp"
#include "Shapes.hpp"
#include "Physics.hpp"
#include "GraphEventHandler.hpp"

class Vertex {
public:
	Vertex(Index i, Index n);
	inline const Point2& GetPt() const { return node.GetPos(); }
	inline bool operator==(const Vertex& other) const {
		return name == other.GetName();
	}
	inline bool operator!=(const Vertex& other) const {
		return !(*this == other);
	}
	void FixNodeToPosition(const Point2& pt);
	void ApplyForceToNode(const Point2& force, double intensity);
	void UpdateNode();

	Index GetName() const { return name; }
	const Physics& GetNode() const { return node; }
private:
	Index name;
	Physics node;
};

class Edge {
public:
	Edge(Vertex* a, Vertex* b) : vertices{a, b} {}
	inline const Segment2 GetSeg() const { return Segment2(vertices[0]->GetPt(), vertices[1]->GetPt()); }
	const std::array<Vertex*, 2>& GetVertices() const {
		return vertices;
	}
	const std::array<Index, 2> GetName() const {
		return { vertices[0]->GetName(), vertices[1]->GetName() };
	}
private:
	std::array<Vertex*, 2> vertices;
};

class Graph {
	friend class GraphEventHandler;
public:
	Graph(Index n, const std::vector<std::array<Index, 2>>& vPairs);
	inline Index size() const { return V.size(); }
	void Update();
	void Draw() const;
	Vertex* LocateVertexAt(const Point2& pt) const;
	const std::vector<std::array<Index, 2>> GetEdgeNames() const;
	GraphEventHandler& GetEventHandler() {
		return eventHandler;
	}
private:
	void MakeVerticesRepelEachOther(double intensity);
	void MakeEdgesTryToKeepFixedDist(double dist, double intensity);
	void LockVertexIfNeeded();
	void UpdateAllNodes();
	std::vector<std::unique_ptr<Vertex>> V;
	std::vector<std::unique_ptr<Edge>> E;
	GraphEventHandler eventHandler;
};

