#pragma once

class Graph;

class GraphEventHandler {
public:
	GraphEventHandler(Graph* pG) : m_pG(pG) {}
	void CursorPos(double x, double y) const;
	void MouseButton() const;
	void Key() const;
private:
	Graph* m_pG;
};

