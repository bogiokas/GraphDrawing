#pragma once
#include "Shapes.hpp"

class Graph;
class Vertex;

class GraphEventHandler {
public:
	GraphEventHandler(Graph* pG) : m_pG(pG), m_pSelectedVertex(nullptr) {}
	void StartMovingVertex(const Point2& pt);
	void MoveVertex(const Point2& pt) const;
	void EndMovingVertex();

	//void CreateVertex(double x, double y) const;
private:
	Graph* m_pG;
	Vertex* m_pSelectedVertex;
};

