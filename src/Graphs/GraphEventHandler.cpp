#include "Graphs/GraphEventHandler.hpp"
#include "Graphs/Graph.hpp"

void GraphEventHandler::SelectVertex() {
	m_pSelectedVertex = m_pG->LocateVertexAt(m_pointerPos);
}

void GraphEventHandler::PointerPos(const Point2& pt) {
	m_pointerPos = pt;
}

void GraphEventHandler::DeselectVertex() {
	m_pSelectedVertex = nullptr;
}

std::optional<std::pair<Vertex*, Point2>> GraphEventHandler::GetLock() {
	if(m_pSelectedVertex == nullptr)
		return std::nullopt;
	return std::make_pair(m_pSelectedVertex, m_pointerPos);
}
