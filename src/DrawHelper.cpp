#include "DrawHelper.hpp"

#include<GL/gl.h>

#include<iostream>

namespace DrawHelper {
template<> void Draw(const Physics& node) {
	glEnable(GL_BLEND);
	const auto& pos = node.GetPos();
	const auto& vel = node.GetVel();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	pos.Draw();
	glEnd();

	glEnable(GL_BLEND);
	glBegin(GL_LINES);
	Segment2(pos, pos+(vel*10.0), BLUE).Draw();
	glEnd();
}

template<> void Draw(const std::vector<std::unique_ptr<Vertex>>& vertices) {
	glEnable(GL_BLEND);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for(const auto& v : vertices) {
		const auto& node = v->GetNode();
		const auto& pos = node.GetPos();
		pos.Draw();
	}
	glEnd();

	glEnable(GL_BLEND);
	glBegin(GL_LINES);
	for(const auto& v : vertices) {
		const auto& node = v->GetNode();
		const auto& pos = node.GetPos();
		const auto& vel = node.GetVel();
		Segment2(pos, pos+(vel*10.0), BLUE).Draw();
	}
	glEnd();
}

template<> void Draw(const std::vector<std::unique_ptr<Edge>>& edges) {
	glEnable(GL_BLEND);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for(const auto& e : edges) e->GetSeg().Draw();
	glEnd();
}

void PrintLine() {
	std::cout<<std::endl;
}

template<> void Print(const Point2& point) {
	const auto& pt = point.GetPt();
	std::cout<<"("<<pt[0]<<", "<<pt[1]<<")"<<std::flush;
}

template<> void Print(const Physics& node) {
	std::cout<<"Pos: ";
	Print(node.GetPos());
	std::cout<<", Vel: ";
	Print(node.GetVel());
	std::cout<<", Acc: ";
	Print(node.GetAcc());
	std::cout<<", Mass: "<<node.GetMass()<<std::endl;
}
} //namespace DrawHelper
