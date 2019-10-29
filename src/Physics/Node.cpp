#include "Node.hpp"

void Node::Update() {
	m_vel += m_acc * timestep;
	m_pos += m_vel * timestep;
	m_acc = Point2::Zero();
	RestrictInsideBoundary();
}

void Node::StayStill() {
	m_vel = Point2::Zero();
	m_acc = Point2::Zero();
}

void Node::SetPos(const Point2& pt) {
	m_pos = pt;
	RestrictInsideBoundary();
}

void Node::RestrictInsideBoundary() {
	if(m_pos[0] >= 1.0) {
		m_pos[0] = 1.0 - 5*EPS;
		m_vel[0] = -abs(m_vel[0]) / 2.0;
		m_acc[0] = -0.005*timestep;
	}
	else if(m_pos[0] <= -1.0) {
		m_pos[0] = -1.0 + 5*EPS;
		m_vel[0] = abs(m_vel[0]) / 2.0;
		m_acc[0] = 0.005*timestep;
	}
	if(m_pos[1] >= 1.0) {
		m_pos[1] = 1.0 - 5*EPS;
		m_vel[1] = -abs(m_vel[1]) / 2.0;
		m_acc[1] = -0.005*timestep;
	}
	else if(m_pos[1] <= -1.0) {
		m_pos[1] = -1.0 + 5*EPS;
		m_vel[1] = abs(m_vel[1]) / 2.0;
		m_acc[1] = 0.005*timestep;
	}
}

void Node::ApplyForce(const Force& force) {
	m_acc += force/m_mass;
}

