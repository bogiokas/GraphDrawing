#include "Edge.hpp"
#include "Vertex.hpp"

const std::array<Vertex*, 2>& Edge::GetVertices() const {
	return vertices;
}

const Segment2 Edge::GetSegment() const {
	return Segment2(vertices[0]->GetPt(), vertices[1]->GetPt());
}

const std::array<const LabelBase*, 2> Edge::GetLabels() const {
	std::array<const LabelBase*, 2> labels = { vertices[0]->GetLabel(), vertices[1]->GetLabel() };
	return labels;
}
