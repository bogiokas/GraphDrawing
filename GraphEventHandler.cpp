#include "GraphEventHandler.hpp"
#include "Graph.hpp"

void GraphEventHandler::StartMovingVertex(const Point2& pt) {
	m_pSelectedVertex = m_pG->LocateVertexAt(pt);
	if(m_pSelectedVertex != nullptr)
		m_pSelectedVertex->MouseLock();
}

void GraphEventHandler::MoveVertex(const Point2& pt) const {
	if(m_pSelectedVertex != nullptr)
		m_pSelectedVertex->SetNodePos(pt);
}

void GraphEventHandler::EndMovingVertex() {
	if(m_pSelectedVertex != nullptr)
		m_pSelectedVertex->MouseRelease();
	m_pSelectedVertex = nullptr;
}

