#include "Output/DrawHelper.hpp"

#ifdef _WIN32
#include<Windows.h>
#endif

#include<GL/gl.h>
template<> void DrawHelper::Draw(const VertexSet& vertices) {
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(7.0f);
	glBegin(GL_POINTS);
	for(const auto& v : vertices) {
		const auto& node = v->GetNode();
		const auto& pos = node.GetPos();
		pos.Draw();
	}
	glEnd();

#ifdef _DEBUG
	glEnable(GL_BLEND);
	glLineWidth(0.1f);
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
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	for(const auto& e : edges) e->GetSegment().Draw();
	glEnd();
}

