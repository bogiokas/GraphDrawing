#include "DrawHelper.hpp"

#ifdef _WIN32
#include<Windows.h>
#endif

#include<GL/gl.h>

template<> void DrawHelper::Draw(const Node& node) {
	const auto& pos = node.GetPos();
	glEnable(GL_BLEND);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	pos.Draw();
	glEnd();

#ifdef _DEBUG
	const auto& vel = node.GetVel();
	glEnable(GL_BLEND);
	glBegin(GL_LINES);
	Segment2(pos, pos+(vel*10.0), BLUE).Draw();
	glEnd();
#endif
}

template<> void DrawHelper::Draw(const VertexSet& vertices) {
	glEnable(GL_BLEND);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for(const auto& v : vertices) {
		const auto& node = v->GetNode();
		const auto& pos = node.GetPos();
		pos.Draw();
	}
	glEnd();

#ifdef _DEBUG
	glEnable(GL_BLEND);
	glBegin(GL_LINES);
	for(const auto& v : vertices) {
		const auto& node = v->GetNode();
		const auto& pos = node.GetPos();
		const auto& vel = node.GetVel();
		Segment2(pos, pos+(vel*10.0), BLUE).Draw();
	}
	glEnd();
#endif
}

template<> void DrawHelper::Draw(const EdgeSet& edges) {
	glEnable(GL_BLEND);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for(const auto& e : edges) e->GetSegment().Draw();
	glEnd();
}

