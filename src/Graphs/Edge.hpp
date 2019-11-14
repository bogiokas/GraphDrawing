#pragma once
#include "Basics/Basics.hpp"
#include "Basics/Shapes.hpp"
#include "Graphs/Label.hpp"
#include "Graphs/Vertex.hpp"

class Edge {
public:
	Edge(Vertex* a, Vertex* b) : vertices{a, b} {}

	const std::array<Vertex*, 2>& GetVertices() const;
	const Segment2 GetSegment() const;
	const std::array<constLabel, 2> GetLabels() const;

	inline size_t Hash() const {
		return vertices[0]->Hash() ^ vertices[1]->Hash();
	}
	bool operator==(const Edge& other) const {
		const auto& otherVertices = other.GetVertices();
		return (*vertices[0] == *otherVertices[0] && *vertices[1] == *otherVertices[1])
			|| (*vertices[0] == *otherVertices[1] && *vertices[1] == *otherVertices[0]);
	}
private:
	std::array<Vertex*, 2> vertices;
};

