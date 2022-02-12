#include "Node.hpp"

void Node::Update() {
	m_vel += m_acc * timestep;
	m_pos += m_vel * timestep;
	m_acc = Point2::Zero();
	RestrictVelocity(0.1);
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

void Node::RestrictVelocity(double cap) {
	if (m_vel.Norm() > cap) {
		m_vel.Normalize();
		m_vel *= cap;
	}
}

void Node::RestrictInsideBoundary() {
	for (Index i = 0; i < m_pos.GetPt().size(); ++i) {
		bool restricted = true;
		if (m_pos[i] >= 1.0) m_pos[i] = 1.0 - 5 * EPS;
		else if (m_pos[i] <= -1.0) m_pos[i] = -1.0 + 5 * EPS;
		else restricted = false;
		if (restricted) {
			m_vel[i] = -m_vel[i] / 2.0;
			m_acc[i] = 0.0;
		}
	}
}

void Node::ApplyForce(const Force& force) {
	m_acc += force / m_mass;
	if (m_acc.Norm() > 1.0) {
		m_acc.Normalize();
	}
}

