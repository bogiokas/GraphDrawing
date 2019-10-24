#pragma once
#include "Basics.hpp"
#include "Shapes.hpp"

class Graph;
class Vertex;

class GraphEventHandler {
public:
	GraphEventHandler(Graph* pG) : m_pG(pG), m_pSelectedVertex(nullptr), m_pointerPos(Point2::Zero()) {}
	void SelectVertex();
	void PointerPos(const Point2& pt);
	void DeselectVertex();

	//void CreateVertex(double x, double y) const;
	std::optional<std::pair<Vertex*, Point2>> GetLock();
private:
	Graph* m_pG;
	Vertex* m_pSelectedVertex;
	Point2 m_pointerPos;
};

