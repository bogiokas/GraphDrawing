#pragma once
#include "Basics/Basics.hpp"
#include "Basics/Shapes.hpp"
#include "Physics/Node.hpp"
#include "Physics/Force.hpp"
#include "Graphs/Label.hpp"

class Vertex {
public:
	Vertex(Label label) : m_label(label), m_node() {}

	void FixNodeToPosition(const Point2& pt);
	void ApplyForceToNode(const Force& force, double intensity);
	void UpdateNode();

	inline const Node& GetNode() const { return m_node; }
	inline const Point2& GetPt() const { return m_node.GetPos(); }
	inline Label GetLabel() const { return m_label; }

	inline size_t Hash() const {
		return m_label.Hash();
	}
	inline bool operator==(const Vertex& other) const {
		return m_label == other.m_label;
	}
	inline bool operator!=(const Vertex& other) const {
		return !(*this == other);
	}
private:
	Label m_label;
	Node m_node;
};

