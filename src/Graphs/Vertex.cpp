#include "Graphs/Vertex.hpp"

void Vertex::FixNodeToPosition(const Point2& pt) {
	m_node.StayStill();
	m_node.SetPos(pt);
}

void Vertex::ApplyForceToNode(const Force& force, double intensity) {
	m_node.ApplyForce(force * intensity);
}

void Vertex::UpdateNode() {
	m_node.Update();
}

