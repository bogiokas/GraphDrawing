#pragma once
#include "Basics/Basics.hpp"
#include "Basics/Shapes.hpp"
#include "Label.hpp"

class Vertex;

class Edge {
public:
	Edge(Vertex* a, Vertex* b) : vertices{a, b} {}

	const std::array<Vertex*, 2>& GetVertices() const;
	const Segment2 GetSegment() const;
	const std::array<const LabelBase*, 2> GetLabels() const;

	bool operator==(const Edge& other) const {
		const auto& labels1 = GetLabels();
		const auto& labels2 = other.GetLabels();
		return (labels1[0] == labels2[0] && labels1[1] == labels2[1])
			|| (labels1[0] == labels2[1] && labels1[1] == labels2[0]);
	}
private:
	std::array<Vertex*, 2> vertices;
};

