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
private:
	std::array<Vertex*, 2> vertices;
};

