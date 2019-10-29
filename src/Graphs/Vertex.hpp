#pragma once
#include "Basics/Basics.hpp"
#include "Basics/Shapes.hpp"
#include "Physics/Node.hpp"
#include "Physics/Force.hpp"
#include "Label.hpp"

class Vertex {
public:
	Vertex(std::unique_ptr<LabelBase> pLabel)
		: m_pLabel(std::move(pLabel)), m_node() {}

	void FixNodeToPosition(const Point2& pt);
	void ApplyForceToNode(const Force& force, double intensity);
	void UpdateNode();

	inline const Node& GetNode() const { return m_node; }
	inline const Point2& GetPt() const { return m_node.GetPos(); }
	inline const LabelBase* GetLabel() const { return m_pLabel.get(); }

	inline bool operator==(const Vertex& other) const {
		return GetLabel() == other.GetLabel();
	}
	inline bool operator!=(const Vertex& other) const {
		return !(*this == other);
	}
private:
	std::unique_ptr<LabelBase> m_pLabel;
	Node m_node;
};

